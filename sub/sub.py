import paho.mqtt.client as mqtt_client
import random
import time
import serial

ser = serial.Serial("COM3", timeout=1)

def on_message(client, user_data, message):
    data = message.payload.decode("utf-8")
    ser.write(data.encode())



broker = "broker.emqx.io"

client = mqtt_client.Client(f"lab_{random.randint(10000, 99999)}")
client.on_message = on_message

try:
    client.connect(broker)
except Exception:
    print("Failed to connect broker. Check network")
    exit()

client.loop_start()
print("Subscribing")
client.subscribe("lab/donAndBass")
time.sleep(600)
client.disconnect()
client.loop_stop()
print("Stop communication")