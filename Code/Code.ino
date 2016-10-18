#include <RFM69.h>
#include <RFM69registers.h>
#include <RFM69_ATC.h>

#include <RFM69.h>
#include <SPI.h>           //comes with Arduino
#include <string.h>

//*****************************************************************************************************************************
// ADJUST THE SETTINGS BELOW DEPENDING ON YOUR HARDWARE/TRANSCEIVER SETTINGS/REQUIREMENTS
//*****************************************************************************************************************************
#define GATEWAYID   1
#define NODEID      22
#define NETWORKID   100
#define FREQUENCY       RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define ENCRYPTKEY    "AkinsLovesDuinos" //exactly the same 16 characters/bytes on all nodes!
#define IS_RFM69HW    //uncomment only for RFM69HW! Leave out if you have RFM69W!
#define SEND_LOOPS   15 //send data this many sleep loops (15 loops of 8sec cycles = 120sec ~ 2 minutes)
//*********************************************************************************************

#define pinADC1 1
#define pinADC2 2
#define pinADC3 3

#define NO_BOTTLE_THESHOLD 2000
#define EMPTY_THRESHOLD    2048
#define FAIL_THRESHOLD 5

int failCount = 0;
int sensor1Val = 1023;
int sensor2Val = 1023;
int sensor3Val = 1023;
int currentWeight;

RFM69 radio;
//char Pstr[10];
char buffer[50];
byte sendLen;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinADC1, INPUT);
  pinMode(pinADC2, INPUT);
  pinMode(pinADC3, INPUT);
  
  // Init radio HW
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
#ifdef IS_RFM69HW
  radio.setHighPower(); //uncomment only for RFM69HW!
#endif
  radio.encrypt(ENCRYPTKEY);
  radio.sendWithRetry(GATEWAYID, "START", 6);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  radio.sendWithRetry(GATEWAYID, "RSTtest", 6);

  int currentWeight = getWeightValue();
  checkWeightThreshold(currentWeight);

  
  // Compare fail count to thresholds
  while (failCount > FAIL_THRESHOLD)
  {
    // Send alert to gateway
    shameUser();
    checkWeightThreshold(getWeightValue());
  }
}

int getWeightValue(){
  // Check ADC
  sensor1Val = analogRead(pinADC1);
  sensor2Val = analogRead(pinADC2);
  sensor3Val = analogRead(pinADC3);
  
  // Sum raw values
  return sensor1Val + sensor2Val + sensor3Val;
}

void checkWeightThreshold(int value){
  if (value > EMPTY_THRESHOLD)  // Not empty
  {
    if (failCount != 0)
    {
      failCount--;
    }
  }
  else if (value > NO_BOTTLE_THESHOLD)  // Empty
  {
    if (failCount != 1023)
    {
      failCount++;
    }
  }
  else  // Bottle removed, being replaced
  {
    failCount = 0;
  }
}

void shameUser(){ // This function should run for about 1 second
  // Lights and sounds and stuff
}


