  /*
   * @file test_relay_acs712.ino
   * @brief test relay.
   *
   * Copyright (c) 2017 Trang Tran
   *
   * @detail
   *
   * Modified History
   * ---------------
   * 2017-Feb-10 Modified tn-trang.tran@outlook.com
   * 2017-Mar-07 Modified tn-trang.tran@outlook.com
   */

#define RELAY 8
#define CURRENT_SENSOR A0

int mVperAmp = 185;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup() {
  /*!
   * put your setup code here, to run once:
   */
  Serial.begin(9600);
  pinMode(RELAY,OUTPUT);
}

void loop() {
  /*!
   * put your main code here, to run repeatedly:
   */
  digitalWrite(RELAY,HIGH);

  Voltage = getVPP();

  int value = analogRead(CURRENT_SENSOR);
  Serial.println(CURRENT_SENSOR);
  VRMS = (Voltage/2.0) * 0.70711;
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  
  Serial.println("Amps RMS: ");
  Serial.print(AmpsRMS);
  
  delay(1000);
}

float getVPP()
{
  float result;

  int readValue;
  int maxValue = 0;
  int minValue = 1023;

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
  result = ((maxValue - minValue) * 5.0) / 1023.0;

  return result;
}