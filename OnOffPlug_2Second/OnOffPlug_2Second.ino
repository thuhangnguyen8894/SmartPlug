#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] =
{
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 1, 177);

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char ReplyBuffer[] = "acknowledge";

EthernetUDP udp;
IPAddress server(192, 168, 1, 155);

int port = 8787;

int power = 10;

void setup() {
  Ethernet.begin(mac, ip);
  udp.begin(port);
  
  pinMode(power,OUTPUT);
}

void loop() {
  
  udp.beginPacket(server, port); 
  
  digitalWrite(power, HIGH);
  delay(5000);
  udp.write("Tat");
  udp.endPacket();
                              
  udp.beginPacket(server, port);
  digitalWrite(power, LOW);
  delay(5000);
  udp.write("Bat");                        
  udp.endPacket();
}
