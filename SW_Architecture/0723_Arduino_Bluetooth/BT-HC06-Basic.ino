// Basic bluetooth test sketch. HC-06_01
//bluetooth default : slave, 9600bps, N, 8, 1 PinCode(1234), 
//시리얼 모니터에서 9600bps, line ending 없음 설정 후 AT명령 --> OK 리턴
//AT+VERSION ==> BT SPP V3.0
//AT+NAMEiot17 ==> OKname   : 이름 변경 iot00

//Bluetooth Arduino
//VCC <--> 5V
//GND <--> GND
//TXD --> RX(10)
//RXD <-- TX(11) 

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX
 
void setup(){
    Serial.begin(9600);
 
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
    Serial.print("Uploaded : ");
    Serial.println(__DATE__);
    Serial.println("HM-06 is ready for AT commands:");
 
    // HC-06 default baud rate is 9600
    BTSerial.begin(9600);  
    pinMode(13,OUTPUT);
}
// 98:DA:60:07:D6:C4
 
void loop(){
    int ch;
    // Keep reading from HC-06 and send to Arduino Serial Monitor
    if (BTSerial.available())
    {
      ch = BTSerial.read();
      Serial.write(ch);
      if(ch == '0')
        digitalWrite(13,LOW);
//        Serial.println(BTSerial.read());
      else if(ch == '1')
        digitalWrite(13,HIGH);
    }
    // Keep reading from Arduino Serial Monitor and send to HC-06
    if (Serial.available())
        BTSerial.write(Serial.read());
//        BTSerial.println(Serial.read());
}
