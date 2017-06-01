  /*
   * @file Arduino_Module_Plus.ino
   * @brief Handle send and receive analog.
   *
   * Copyright (c) 2017 Trang Tran
   *
   * @detail
   *
   * Modified History
   * ---------------
   * 2017-Jan-05 Created  tn-trang.tran@outlook.com
   * 2017-Jan-11 Modified tn-trang.tran@outlook.com
   * 2017-Feb-10 Modified tn-trang.tran@outlook.com
   * 2017-Mar-07 Modified tn-trang.tran@outlook.com
   */

#include <Time.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define RELAY 8
#define CURRENT_SENSOR A0

#define MESSAGE_TYPE "SMART_DEVICE_STATUS_VALUE"
#define ID_DEVICE "SD001"
#define ID_ROOM "R0001"
#define SEMICOLON_SPLITTER ";"
#define COLON_SPLITTER ":"
#define STATUS_RELAY_ACTIVE "ACTIVE"
#define STATUS_RELAY_UNACTIVE "UNACTIVE"
#define STATUS_ELECTRIC_ON "ON"
#define STATUS_ELECTRIC_OFF "OFF"


byte mac[] =
{
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED  
};

/*!
 * Server's IP
 */
IPAddress server(192, 168, 0, 104);

/*!
 * Server's port
 */
int serverPort = 8787;

/*!
 * Ethernet Shield's IP
 */
IPAddress ip(192, 168, 0, 103);

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
 * The last moment when I got the light intensity and sent it to server.
 */
unsigned long lastMoment = 0;

/*!
 * Delay time
 */
const unsigned long delayInterval = 1000L;

/*!
 * Paremeters measure current electric
 */
int mVperAmp = 185;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

/*!
 * Paremeters analog electric when use or don't use
 */
float minOffElectric = 0.0514;
float maxOffElectric = 0.3214;
float minOnElectric = 0.0714;

/*!
 * Paremeters quality control current electric when send message
 * status_before: status of device was previous time.
 * status_after: status of device is current time.
 */
boolean status_before = false;
boolean status_after = false;

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

    pinMode(RELAY,OUTPUT);

    udp.begin(internalPort);
}


void loop()
{
    /*!
     * Turn on power of jackRelay
     */
    digitalWrite(RELAY,HIGH);
    
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
         if (strcmp(packetBuffer, "ACTIVEVE"))
         {
             digitalWrite(RELAY, HIGHT);
         }

         else if (strcmp(packetBuffer, "UNACTIVE"))
         {
             digitalWrite(RELAY, LOW);
         }
    }
    else
    {
        /*!
         * Reading the signal from Sensor
         * Send the data to server
         */
       if (millis() - delayInterval > delayInterval)
       {
            sendSmartPlugStatus();
       }

       delay(200);
    }
}

void sendSmartPlugStatus()
{
    
    uint16_t moment = now();

    /*!
     * Print data to Serial for debugging
     */
    Serial.println(moment);

    /*!
     * Get value of current electric from getAmpsRMS() function
     */ 
    double currentElectric = getAmpsRMS();
    
    /*!
     * Create the message
     */    
    char* msg = new char[500];
    memset(msg, 0, 500 * sizeof(char));

    /*!
     * Determine the category of message
     *
     *****************************************
     *!
     * Read value 
     * Hasn't electric: from 0.0514 to 0.0714
     * Has electric: from 0.3714 to 1.9914 
     */  
    if(currentElectric <= maxOffElectric)
    {
      status_after = false;
    }
    else if(currentElectric > maxOffElectric)
    {
      status_after = true;
    }
    else
    {
      status_after = false;
    }

    /*!
     * Handle send message when status_before and status_after different 
     *
     *******************************************************************
     *!
      * Format message type 
      */
    strcat(msg, MESSAGE_TYPE);
    strcat(msg, SEMICOLON_SPLITTER);
    strcat(msg, ID_DEVICE);
    strcat(msg, COLON_SPLITTER);

    /*!
     * Define variable contain status of Relay
     */
    int statusRelay = digitalRead(RELAY);
    
    if (statusRelay == HIGH)
    {
      if (status_before != status_after)
      {
        if (status_after == true)
        {
          strcat(msg, STATUS_ELECTRIC_ON);
          strcat(msg, COLON_SPLITTER);
          strcat(msg, STATUS_RELAY_ACTIVE);
        }
        else
        {
          strcat(msg, STATUS_ELECTRIC_OFF);
          strcat(msg, COLON_SPLITTER);
          strcat(msg, STATUS_RELAY_ACTIVE);
        }

        strcat(msg, COLON_SPLITTER);
        strcat(msg, ID_ROOM);

        Serial.println(msg);

        /*!
         * Send the message
         */
        udp.beginPacket(server, serverPort);
        udp.write(msg, strlen(msg) * sizeof(msg));
        udp.endPacket();
      }

      /*!
       *  Update the status_before
       */
      status_before = status_after;
    }
    
    else if (statusRelay == LOW)
    {
      if (status_before != status_after)
      {
        if (status_after == true)
        {
          strcat(msg, STATUS_ELECTRIC_ON);
          strcat(msg, COLON_SPLITTER);
          strcat(msg, STATUS_RELAY_UNACTIVE);
        }
        else
        {
          strcat(msg, STATUS_ELECTRIC_OFF);
          strcat(msg, COLON_SPLITTER);
          strcat(msg, STATUS_RELAY_UNACTIVE);
        }

        strcat(msg, COLON_SPLITTER);
        strcat(msg, ID_ROOM);

        Serial.println(msg);

        /*!
         * Send the message
         */
        udp.beginPacket(server, serverPort);
        udp.write(msg, strlen(msg) * sizeof(msg));
        udp.endPacket();
      }

      /*!
       *  Update the status_before
       */
      status_before = status_after;
    }

    /*!
     * Update the lastMoment value
     */
    lastMoment = millis();

    if (msg != NULL)
    {
        delete msg;
    }
}

/*!
 * Function get AmpsRMS
 */
float getVPP()
{
  float result;

  int readValue;
  int maxValue = 0;
  int minValue = 1024;

  uint32_t start_time = millis();
  while((millis() - start_time) < 1000)
  {
    readValue = analogRead(CURRENT_SENSOR);

    if(readValue > maxValue)
    {
      maxValue = readValue;
    }
    if(readValue < minValue)
    {
      minValue = readValue;
    }
  }
  result = ((maxValue - minValue) * 5.0) / 1024.0;

  return result;
}

/*!
 * Function get AmpsRMS
 */
double getAmpsRMS()
{
  Voltage = getVPP();
  int value = analogRead(CURRENT_SENSOR);

  VRMS = (Voltage/2.0) * 0.707;
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  return AmpsRMS;
  delay(20);
}
