import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 6203
BUFFER_SIZE = 256

recvSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
recvSocket.bind((TCP_IP, TCP_PORT))
recvSocket.listen(200)

conn, addr = recvSocket.accept()
print('Connection address: ', addr)

while True:
    data = conn.recv(BUFFER_SIZE)
    if data: 
        print("Received data: ", data)
    conn.send(data)
    
conn.close()
