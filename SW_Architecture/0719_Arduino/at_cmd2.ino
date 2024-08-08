#include <SoftwareSerial.h>

/*
--------------------------------------------------
아두이노 우노 핀    ESP8266 Serial WIFI 모듈  핀
  3.3V              VCC, CH_PD
 D7(TX)             RX (레벨쉬프트 사용)
 D6(RX)             TX
 GND                GND
 ------------------------------------------------
//시리얼 모니터 19200 설정, Both NL & CR 설정 후 아래 명령 실행
AT+RST    ==>  응답확인 : 핀 연결 및 모듈 테스트 
*/

SoftwareSerial wifi(6, 7) ;  // RX, TX
void setup() {
  // put your setup code here, to run once:
  wifi.begin(38400) ;
  Serial.begin(38400) ;
//  Serial.println("AT CMD TEST 2");
}



void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) wifi.write(Serial.read()) ;
  if (wifi.available()) Serial.write(wifi.read()) ;
}
