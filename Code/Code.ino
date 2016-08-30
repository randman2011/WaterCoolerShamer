int failCount = 0;
int pinADC1 = 1;
int pinADC2 = 2;
int pinADC3 = 3;

int sensor1Val = 1023;
int sensor2Val = 1023;
int sensor3Val = 1023;

int currentWeight;

int WEIGHT_THRESHOLD = 2048;
int FAIL_THRESHOLD = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int currentWeight = getWeightValue();
  checkWeightThreshold(currentWeight);

  
  // Compare fail count to thresholds
  while (failCount > FAIL_THRESHOLD)
  {
	  
  }
}

int getWeightValue()
{
  // Check ADC
  sensor1Val = analogRead(pinADC1);
  sensor2Val = analogRead(pinADC2);
  sensor3Val = analogRead(pinADC3);
  
  // Sum raw values
  return sensor1Val + sensor2Val + sensor3Val;
}

void checkWeightThreshold(value)
{
  if (value > WEIGHT_THRESHOLD)
  {
    if (failCount != 0)
    {
      failCount--;
    }
  }
  else
  {
    if (failCount != 1023)
    {
      failCount++;
    }
  }
}

