import json
import socket
import pickle

from django.shortcuts import render
from django.http import JsonResponse

ARDUINO_IP = "192.168.0.10"
ARDUINO_PORT = 5600

MESSAGE_RECEIVER_IP = "192.168.0.100"
MESSAGE_RECEIVER_PORT = 8787
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create your views here.
def arduino(request):
    return render(request, "arduino.html", {})

def controlSmartPlug(request):
    cmd = request.GET['cmd']

    # json_dict = {"a" : 1, "b" : "dummy_data"}
    # if cmd == 'ON' or cmd == 'OFF':
    #     # sock.sendto(cmd.encode(), (ARDUINO_IP, ARDUINO_PORT))
    #     sock.sendto(cmd.encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
    # sock.sendto(json.dumps(json_dict).encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))
    sock.sendto("SMART_DEVICE_STATUS_VALUE;SD001:DEVICE_LIGHT:OFF:UNACTIVE:R0001".encode(), (MESSAGE_RECEIVER_IP, MESSAGE_RECEIVER_PORT))

    return JsonResponse({'SPState':cmd})
