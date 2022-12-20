import paho.mqtt.client as mqtt_client
import random
import time
import serial

broker = "broker.emqx.io"

client = mqtt_client.Client(f"lab_{random.randint(10000, 99999)}")
client.connect(broker)
ser = serial.Serial("COM10", timeout=1)
print("Open connection")


maxBright = 0

while True:
  if ser.in_waiting > 0:
    try:
      data = ser.readline()
      state = chr(data[0])
      number = int(str(data[1:])[:-5][2:])
      
      if (state == 'B'):
        client.publish("lab/donAndBass/bright", number)
#         if (maxBright < number):
#             maxBright = number
#         if (number < maxBright / 2):
#           client.publish("lab/donAndBass/bright", "1")
#         else:
#           client.publish("lab/donAndBass/bright", "0")
      else:
       client.publish("lab/donAndBass/sonic", number)
#         if (number < 20):
#           client.publish("lab/donAndBass/sonic", "1")
#         else:
#           client.publish("lab/donAndBass/sonic", "0")


    
    except:
        pass
      
client.disconnect()

