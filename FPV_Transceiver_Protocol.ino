#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출

const int analogInPin0 = A0; 
const int analogInPin1 = A1; 
//int blueTx=2;   //Tx (보내는핀 설정) 아두이노나노 + 블루투스모듈 사용할 경우
//int blueRx=3;   //Rx (받는핀 설정) 아두이노나노 + 블루투스모듈 사용할 경우
int blueTx=4;   //Tx (보내는핀 설정) Jarduino-UNO-BTmini사용할 경우
int blueRx=7;   //Rx (받는핀 설정) Jarduino-UNO-BTmini사용할 경우
int sensorValue1 = 0;  
int sensorValue2 = 0; 
int outputValue1 = 0;
int outputValue2 = 0;
unsigned long preMil = 0;
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
 
void setup() 
{
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(38400); //블루투스 시리얼
}
void loop()
{  
  unsigned long curMil = millis();
  sensorValue1 = analogRead(analogInPin0);
  sensorValue2 = analogRead(analogInPin1);
  outputValue1 = map(sensorValue1, 0, 1023, 0, 255);
  outputValue2 = map(sensorValue2, 0, 1023, 0, 255);

  byte wbuf[4]={0xFF,0x01,0x02,0x03};
  
  wbuf[2] = outputValue1;
  wbuf[3] = outputValue2;
  if(curMil - preMil > 50) {
    preMil = curMil;
    mySerial.print("#SERVO,");
    mySerial.print(outputValue1);
    mySerial.print("@");

    mySerial.print("#PWM,");
    mySerial.print(outputValue2);
    mySerial.print("@");
    //mySerial.write(wbuf,4);

//  if (mySerial.available()) {       
//    Serial.write(mySerial.read());  //블루투스측 내용을 시리얼모니터에 출력
  }
  //if (Serial.available()) {         
  //  mySerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
  //}

//  delay(15);
}
