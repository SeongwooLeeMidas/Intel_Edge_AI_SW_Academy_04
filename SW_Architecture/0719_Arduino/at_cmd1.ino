/*
--------------------------------------------------
아두이노 우노 핀    ESP8266 Serial WIFI 모듈  핀
  3.3V              VCC, CH_PD
 D0(TX)             RX (레벨쉬프트 사용)
 D1(RX)             TX
 GND                GND
 ------------------------------------------------
시리얼 모니터 115200bps 설정, Both NL & CR 설정 후 아래 명령 실행
AT+RST                       //restart
AT+UART_DEF=38400,8,1,0,0    
시리얼 모니터 38400 설정 변경후  
AT+RST              //응답 확인
*/

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
