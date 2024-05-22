import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient
import json

# Configurações do MQTT
mqtt_broker = "35.199.93.123"
mqtt_topic = "ifpe/esp-8266"

# Configurações do InfluxDB
influx_host = '35.199.93.123'
influx_port = 8086
influx_database = 'mqtt_data'

# Função de callback para receber mensagens MQTT
def on_message(client, userdata, msg):
    print(f"Recebido: {msg.topic} {msg.payload.decode()}")  # Decode bytes para string

    try:
        # Parse a mensagem JSON
        data = json.loads(msg.payload.decode())
        distancia = float(data['distancia'])
        porcentagem = float(data['porcentagem'])
        litros = float(data['litros'])

        # Enviar a mensagem para o InfluxDB
        json_body = [
            {
                "measurement": "reservatorio",
                "fields": {
                    "distancia": distancia,
                    "porcentagem": porcentagem,
                    "litros": litros
                }
            }
        ]
        influx_client.write_points(json_body, database='mqtt_data')
        print(f"Dados armazenados no InfluxDB: {json_body}")
    except Exception as e:
        print(f"Erro ao processar mensagem: {e}")

# Conectar ao InfluxDB
influx_client = InfluxDBClient(host=influx_host, port=influx_port)
influx_client.create_database(influx_database)

# Configurar o cliente MQTT com a versão mais recente da API de callback
mqtt_client = mqtt.Client()
mqtt_client.on_message = on_message

# Conectar ao broker MQTT e inscrever-se ao tópico
mqtt_client.connect(mqtt_broker, 1883, 60)
mqtt_client.subscribe(mqtt_topic)

# Manter a conexão MQTT ativa
mqtt_client.loop_forever()
