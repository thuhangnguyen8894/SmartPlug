#include <Time.h>
#include <SPI.h>
#include <Ethernet.h>
#include <utility/w5100.h>
#include <EthernetUdp.h>

#include "BH1750.h"

byte mac[] =
{
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED  
};

/*!
 * Server's IP
 */
IPAddress server(192, 168, 1, 106);

/*!
 * Server's port
 */
int serverPort = 8787;

/*!
 * Ethernet Shield's IP
 */
IPAddress ip(192, 168, 1, 177);

/*!
 * Ethernet Shield's port
 */
int internalPort = 5600;

/*!
 * Received buffer
 */
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

/*!
 * Using UDP Protocol
 */
EthernetUDP udp;

/*!
 * Light Intensity sensor
 */
BH1750 lightMeter;

/*!
 * The last moment when I got the light intensity and sent it to server.
 */
unsigned long lastMoment = 0; 

/*!
 * Delay time
 */
const unsigned long delayInterval = 600L;

void setup()
{
    /*!
     * Serial is used for debug
     */
    Serial.begin(9600);

    /*!
     * Setup Ethernet Shield
     */
    Ethernet.begin(mac, ip);

    udp.begin(internalPort);
}


void loop()
{
    int packetSize = udp.parsePacket();

    /*!
     * Handle the message from Server.
     * Execute the command line of 
     */
    if (packetSize)
    {
        /*!
         * Print the information of Sender for debug
         */
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

        /*!
         * Reading the message
         */
        udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

        /*
         * Print the content of message for debugging
         */
        Serial.println("Contents:");
        Serial.println(packetBuffer);
        
        /*!
         * Do a action
         */
    }
    else
    {
        /*!
         * Reading the signal from Sensor
         * Send the data to server
         */
        if ((millis() - lastMoment) > delayInterval)
        {
            sendLightIntensity();
        }
    }
}

void sendLightIntensity()
{
    uint16_t lux = lightMeter.readLightLevel();
    uint16_t time = now();

    /*!
     * Print data to Serial for debugging
     */
    Serial.print(lux);
    Serial.print(";");
    Serial.println(time);

    /*!
     * Convert the lux's value to char
     */
    char first = lux & 0x00FF;
    char second = lux >> 8;

    /*!
     * Create the message
     */
    char message[] = {'L', first, second};

    /*!
     * Send the message
     */
    udp.beginPacket(server, serverPort);
    udp.write(message, sizeof(message));
    udp.endPacket();

    /*!
     * Update the lastMoment value
     */
    lastMoment = millis();
}