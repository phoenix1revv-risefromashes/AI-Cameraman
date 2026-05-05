import serial
import time

communication = serial.Serial('/dev/serial0', 115200, timeout=2)

time.sleep(1)

communication.write(b'ping\n')

response = communication.readline()

print(response)

communication.close()
