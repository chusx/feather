#include <CANSAME5x_port.h>
#include <CANSAME5x.h>
#include <CANController.h>

CANSAME5x CAN;
int count = 0;
unsigned long msec_last;

#define FIVE_MIN 300000

void setup() {
  Serial.begin(115200);

  Serial.println("CAN Sender");
  pinMode(13, OUTPUT); // built in led pin
  pinMode(6, OUTPUT); // for an external reset button
  digitalWrite(6, LOW);

  pinMode(PIN_CAN_STANDBY, OUTPUT);
  digitalWrite(PIN_CAN_STANDBY, false); // turn off STANDBY
  pinMode(PIN_CAN_BOOSTEN, OUTPUT);
  digitalWrite(PIN_CAN_BOOSTEN, true); // turn on booster

  if (!CAN.begin(500000)) {
    Serial.println("Starting CAN failed!");
    while(1) delay(10);
  }

  Serial.println("Starting CAN!");
  send_can();
}

void loop() {
  unsigned long msec = millis();

  if ((msec - msec_last) > FIVE_MIN)  {
    msec_last = msec;
    Serial.println(count);
    send_can();
    count += 1;
  }
}

void send_can() {
  digitalWrite(13, HIGH); 
  Serial.print("Sending packet ... ");
  for (int i = 0; i < 1000; i++) {
    CAN.beginPacket(0x281); 
    CAN.write(1);  
    /*
    CAN.write(0);  
    CAN.write(0);  
    CAN.write(0);  
    CAN.write(0);  
    CAN.write(0);  
    CAN.write(0);  
    CAN.write(0);  
    */
    CAN.endPacket(); 
    delay(5); 
  }
  digitalWrite(13, LOW); 
  Serial.println("done.");
}
