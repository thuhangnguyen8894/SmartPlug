#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 1, 177);

unsigned int localPort = 8789;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

EthernetUDP udp;

void setup()
{
    Ethernet.begin(mac, ip);
    udp.begin(localPort);

    Serial.begin(9600);
}

void loop()
{
    int packetSize = udp.parsePacket();
    if (packetSize)
    {
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = udp.remoteIP();
        for (int i = 0; i < 4; i++)
        {
            Serial.print(remote[i], DEC);
            if (i < 3)
            {
                Serial.print(".");
            }
        }
        Serial.print(", port ");
        Serial.println(udp.remotePort());

        udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        Serial.println("Contents:");
        Serial.println(packetBuffer);
    }

    delay(1000);
}

