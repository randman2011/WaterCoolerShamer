int failCount = 0;
int pinADC1 = 1;
int pinADC2 = 2;
int pinADC3 = 3;

int sensor1Val = 1023;
int sensor2Val = 1023;
int sensor3Val = 1023;

int currentWeight;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // Check ADC
  sensor1Val = analogRead(pinADC1);
  sensor2Val = analogRead(pinADC2);
  sensor3Val = analogRead(pinADC3);
  
  // Compare to thresholds
  currentWeight = sensor1Val + sensor2Val + sensor3Val;
  
  if (currentWeight > emptyThreshold)
  {
	if (failCount != 0)
	{
		failCount--;
	}
	delay(1000);
  }
  else
  {
	if (failCount != 1023)
	{
		failCount++;
	}
	delay(1000);
  }
  
  // Compare fail count to thresholds
  if (failCount > FAIL_THRESHOLD)
  {
	
  }
}
