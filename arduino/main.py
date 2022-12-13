import paho.mqtt.client as mqtt_client
import random
import serial

broker = "broker.emqx.io"

client = mqtt_client.Client(f"lab_{random.randint(10000, 99999)}")
client.connect(broker)
ser = serial.Serial("COM8", timeout=1)
while True:
    if ser.in_waiting > 0:
        data = ser.read(1)
        client.publish("lab/dungeon/cv9t", data.decode("utf-8"))
client.disconnect()
