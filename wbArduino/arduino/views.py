import json
import socket

from django.shortcuts import render
from django.http import JsonResponse

ARDUINO_IP = "192.168.0.10"
ARDUINO_PORT = 5600
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create your views here.
def arduino(request):
	return render(request, "arduino.html", {})

def controlSmartPlug(request):
	cmd = request.GET['cmd']

	if cmd == 'ON' or cmd == 'OFF':
		sock.sendto(cmd.encode(), (ARDUINO_IP, ARDUINO_PORT))

	return JsonResponse({'SPState':cmd})