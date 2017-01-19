int relay = 8;
int acs712 = A0;
int mVperAmp = 185;

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay,HIGH);

  Voltage = getVPP();

  int value = analogRead(acs712);
  Serial.println(acs712);
  VRMS = (Voltage/2.0) * 0.707;
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  
  Serial.println("Amps RMS: ");
  Serial.print(AmpsRMS);
  
  delay(200);
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

