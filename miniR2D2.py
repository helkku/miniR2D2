import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev

#Setup
GPIO.setmode(GPIO.BCM)

#addressess for the chip
#[[tx pipe],[tr pipe]]
pipes = [[0xE8,0xE8,0xF0,0xF0,0xE1],[0xF0,0xF0,0xF0,0xF0,0xE1]]

#create radio object whiut GPIO and spidev
radio = NRF24(GPIO,spidev.SpiDev())
radio.begin(0,17)

#settings
radio.setPayloadSize(32)
radio.setChannel(0x76)
#possible rates BR_1MBPS, BR_2MBPS, BR_250KBPS
radio.setDataRate(NRF24.BR_1MBPS)
#possible leveles "PA_MIN", "PA_LOW", "PA_MED", "PA_HIGH"
radio.setPALevel(NRF24.PA_LOW)

#set ack to true
radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openReadingPipe(1,pipes[1])
radio.printDetails()

radio.startListening()
#GPIO.cleanup()

while True:
	while not radio.available(0):
		time.sleep(1/100)
	receivedMessage = []
	radio.read(receivedMessage,radio.getDynamicPayloadSize())
	print("got {}".format(receivedMessage))
	
	print("translating unicode")
	string = ""
	for n in receivedMessage:
		if (n >= 32 and n <= 126):
			string += chr(n)
	print("string: {}".format(string))
