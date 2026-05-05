import serial
import time

communication = serial.Serial('/dev/ttyUSB0', 115200, timeout=2)
# If USB0 does not work, try:
# communication = serial.Serial('/dev/ttyACM0', 115200, timeout=2)

time.sleep(2)

communication.write(b'ping\n')

response = communication.readline()

print(response)

communication.close()
