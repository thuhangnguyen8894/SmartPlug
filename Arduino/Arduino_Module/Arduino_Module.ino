#include <Time.h>
#include <SPI.h>
#include <Ethernet.h>
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
const unsigned long delayInterval = 1000L;

/*!
 * Power pin Relay
 */
int power = 8;

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

    pinMode(power,OUTPUT);

    udp.begin(internalPort);
    lightMeter.begin();
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
       if (millis() - delayInterval > delayInterval)
       {
            sendLightIntensity();
       }

       delay(500);
    }
}

void convertInt16ToHexStr(uint16_t value, char* msg)
{
    uint16_t tmp = 0;
    char message[256];
    memset(message, 0, sizeof(message));

    while (value > 0)
    {
        tmp = value % 16;
        switch (tmp)
        {
        case 0:
            strcat(message, "0");
            break;
        case 1:
            strcat(message, "1");
            break;
        case 2:
            strcat(message, "2");
            break;
        case 3:
            strcat(message, "3");
            break;
        case 4:
            strcat(message, "4");
            break;
        case 5:
            strcat(message, "5");
            break;
        case 6:
            strcat(message, "6");
            break;
        case 7:
            strcat(message, "7");
            break;
        case 8:
            strcat(message, "8");
            break;
        case 9:
            strcat(message, "9");
            break;
        case 10:
            strcat(message, "A");
            break;
        case 11:
            strcat(message, "B");
            break;
        case 12:
            strcat(message, "C");
            break;
        case 13:
            strcat(message, "D");
            break;
        case 14:
            strcat(message, "E");
            break;
        case 15:
            strcat(message, "F");
            break;
        }
        value = value / 16;
    }
    strcat(message, '\0');
    strcat(msg, message);
}

void sendLightIntensity()
{
    uint16_t lux = lightMeter.readLightLevel();
    uint16_t moment = now();

    /*!
     * Print data to Serial for debugging
     */
    Serial.print(lux);
    Serial.print(";");
    Serial.println(moment);
    
    /*!
     * Create the message
     */    
    char* msg = new char[10];
    memset(msg, 0, 10 * sizeof(char));

    /*!
     * Determine the category of message
     */
    strcat(msg, "L");
    
    /*!
     * Convert message to array of digit of hex numbers.
     */
    convertInt16ToHexStr(lux, msg);
    Serial.println(msg);
    /*!
     * Send the message
     */
    udp.beginPacket(server, serverPort);
    udp.write(msg, strlen(msg) * sizeof(msg));
    udp.endPacket();

    /*!
     * Update the lastMoment value
     */
    lastMoment = millis();

    if (msg != NULL)
    {
        delete msg;
    }
}


