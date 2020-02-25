#include <SPort.h>                  //Include the SPort library

SPortHub hub(0x12, 5);              //Hardware ID 0x12, Software serial pin 3
SimpleSPortSensor lapsensor0(0x1AEB);   //Sensor with ID 0x5900
SimpleSPortSensor lapsensor1(0x1AEC);   //Sensor with ID 0x5900
SimpleSPortSensor lapsensor2(0x1AED);   //Sensor with ID 0x5900
SimpleSPortSensor lapsensor3(0x1AEE);   //Sensor with ID 0x5900
int x = 0;
int val = 0;
int val2=0;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int lapnr=1;
int lap0=0;
int lap1=0;
int lap2=0;
int lap3=0;
void setup() {
    hub.commandId = 0x1B;       
  hub.registerSensor(lapsensor0);       //Add sensor to the hub
  hub.registerSensor(lapsensor1);       //Add sensor to the hub
  hub.registerSensor(lapsensor2);       //Add sensor to the hub
  hub.registerSensor(lapsensor3);       //Add sensor to the hub
  hub.begin();
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Serial.begin(115200);
}

void loop() {
  lapsensor0.value = lap0;            //Overall LAP
  lapsensor1.value = lap1;
  lapsensor2.value = lap2;
  lapsensor3.value = lap3;             //Set the sensor value
  hub.handle();

  if (stringComplete) {
    Serial.println(inputString);
     
    if(lapnr==3){
      lap1=inputString.toInt();
      lap0=inputString.toInt();
     lapnr=0;
    }
     if(lapnr==2){
       lap2=inputString.toInt();
       lap0=inputString.toInt();
    }
     if(lapnr==1){
        lap3=inputString.toInt();
        lap0=inputString.toInt();
  
   
    }
    lapnr++;
    
             inputString = "";
    stringComplete = false;
 
  }
  
}

void handleCommand(int prim, int applicationId, int value) {
  hub.sendCommand(0x19, applicationId, value + 1);    //Send a command back to lua, with 0x32 as reply and the value + 1
  Serial.println("BACK");
}


    void serialEvent() {
    while (Serial.available()) {
     // get the new byte:
     char inChar = (char)Serial.read();
     // add it to the inputString:
     inputString += inChar;
     // if the incoming character is a newline, set a flag so the main loop can
     // do something about it:
     if (inChar == '\n') {
       stringComplete = true;
     }
    }
    }
