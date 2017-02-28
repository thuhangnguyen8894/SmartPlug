  /*
 * @file Arduino_Module.ino
 * @brief Handle send and receive analog.
 *
 * Copyright (c) 2017 Tien Anh Nguyen
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tien.nguyenan94@gmail.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Feb-10 Modified tn-trang.tran@outlook.com
 */

#include <Time.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


byte mac[] =
{
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED  
};

/*!
 * Server's IP
 */
IPAddress server(192, 168, 0, 100);

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
 * Power pin Relay
 */
int jackRelay = 8;

/*!
 * Power pin ACS712
 */
int acs712 = A0;

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
float maxOffElectric = 0.0714;
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

    pinMode(jackRelay,OUTPUT);

    udp.begin(internalPort);
}


void loop()
{
    /*!
     * Turn on power of jackRelay
     */
    digitalWrite(jackRelay,HIGH);
    
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
     * get value of current electric from getAmpsRMS() function
     */ 
    double currentElectric = getAmpsRMS();
    
    /*!
     * Create the message
     */    
    char* msg = new char[500];
    memset(msg, 0, 50 * sizeof(char));

    /*!
     * Converse type jackRelay into char
     * purpose: send jack relay for message
     */
     char* jackRelayPoint = new char[2];
     jackRelayPoint = getValueRelay(jackRelay);

    /*!
     * Determine the category of message
     *
     *****************************************
     *!
     * Read value 
     * Hasn't electric: from 0.0514 to 0.0714
     * Has electric: from 0.3714 to 1.9914 
     */  
    if(currentElectric >= minOffElectric && currentElectric <= maxOffElectric)
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
    strcat(msg, "SMART_DEVICE_STATUS_VALUE");
    strcat(msg, ";");
    strcat(msg, "SD001");
    strcat(msg, ":");

    /*!
     * declare variable contain status of Relay
     */
    int statusRelay = digitalRead(jackRelay);
    
    if (statusRelay == HIGH)
    {
      if (status_before != status_after)
      {
        if (status_after == true)
        {
          strcat(msg, "ON");
          strcat(msg, ":");
          strcat(msg, "ACTIVE");
          strcat(msg, ":");
          strcat(msg, jackRelayPoint);
        }
        else
        {
          strcat(msg, "OFF");
          strcat(msg, ":");
          strcat(msg, "ACTIVE");
          strcat(msg, ":");
          strcat(msg, jackRelayPoint);
        }

        strcat(msg, ":");
        strcat(msg, "R0001");

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
          strcat(msg, "ON");
          strcat(msg, ":");
          strcat(msg, "UNACTIVE");
          strcat(msg, ":");
          strcat(msg, jackRelayPoint);
        }
        else
        {
          strcat(msg, "OFF");
          strcat(msg, ":");
          strcat(msg, "UNACTIVE");
          strcat(msg, ":");
          strcat(msg, jackRelayPoint);
        }

        strcat(msg, ":");
        strcat(msg, "R0001");

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

/*
 * get jack relay
 */
char* getValueRelay(int jackRelay)
{
  char* valueJackRelay = new char[2];
  if (jackRelay == 9)
  {
    strcpy(valueJackRelay, "9");
  }
  else if (jackRelay == 8)
  {
    strcpy(valueJackRelay, "8");
  }
  else if (jackRelay == 7)
  {
    strcpy(valueJackRelay, "7");
  }
  else if (jackRelay == 6)
  {
    strcpy(valueJackRelay, "6");
  }
  else if (jackRelay == 5)
  {
    strcpy(valueJackRelay, "5");
  }
  else if (jackRelay == 4)
  {
    strcpy(valueJackRelay, "4");
  }
  
  return valueJackRelay;
}

/*!
 * function get AmpsRMS
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
    readValue = analogRead(acs712);

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
 * function get AmpsRMS
 */
double getAmpsRMS()
{
  Voltage = getVPP();
  int value = analogRead(acs712);

  VRMS = (Voltage/2.0) * 0.707;
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  return AmpsRMS;
  delay(20);
}
