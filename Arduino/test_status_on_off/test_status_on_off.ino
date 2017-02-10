int relay = 8;
int acs712 = A0;
int mVperAmp = 185;

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

float minOffElectric = 0.0514;
float maxOffElectric = 0.0714;
float minOnElectric = 0.0714;

boolean status_before = false;
boolean status_after = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay,HIGH);

  double currentElectric = getAmpsRMS();
  
  if (currentElectric >= minOffElectric && currentElectric <= maxOffElectric)
  {
    status_after = false;
  }
  else if (currentElectric > maxOffElectric)
  {
    status_after = true;
  }
  else
  {
    status_after = false;
  }


  if (status_before != status_after)
  {
    if (status_after == true)
    {
      Serial.println("Send ON");
    }
    else
    {
      Serial.println("Send OFF");
    }

    status_before = status_after;
  }
}

double getAmpsRMS()
{
  Voltage = getVPP();
  int value = analogRead(acs712);

  VRMS = (Voltage/2.0) * 0.707;
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  return AmpsRMS;
  delay(20);
}

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

