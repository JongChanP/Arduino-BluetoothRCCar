//#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출
#include <Servo.h>
 
int blueTx=2;   //Tx (보내는핀 설정)at
int blueRx=3;   //Rx (받는핀 설정)
//SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

Servo myservo;  // create servo object to control a servoServo

String rxData = "";
boolean bStart = false;
int dataCnt = 0;

int Xval=0;
int Yval=0;
int ServoVal;
boolean dirX=HIGH;
boolean dirY=HIGH;
byte readdata;
boolean START = LOW;

// the setup routine runs once when you press reset:
void setup()  { 
  myservo.attach(12); 
  
  Serial.begin(38400);   //블루투스 연결
  Serial.setTimeout(50);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);

}

//byte rbuf[8];
unsigned long preMicro = 0;

// the loop routine runs over and over again forever:
void loop()  { 
  unsigned long curMicro = micros();
//myservo.detach();
//delay(10);

  if (Serial.available()) { 

     char data = Serial.read();
      //Serial.print(data);
     if (bStart){
      if(data == '@'){
      parseData(rxData);
      bStart = false;
      rxData = "";
      } else {
        rxData += data;
      }
     } else {
      if(data == '#') bStart =true;
     }
  }
}

void parseData(String rxStr){

  String cmd = rxStr.substring(0,rxStr.indexOf(','));
  String data = rxStr.substring(rxStr.indexOf(',')+1);

  if(cmd =="SERVO"){
    ServoVal = data.toInt();
    ServoVal = map(ServoVal, 0, 255, 45, 135);
    myservo.write(ServoVal);
  } else if(cmd =="PWM"){
    Xval = data.toInt();
    if(!START && (Xval > 128-5 && Xval < 128+5)){
      START=HIGH;
      }
    if(START){
      Yval=Xval-128;
      digitalWrite(13,HIGH);
    
    if(Yval>0){
      dirX=HIGH;
      dirY=LOW;
    } else {
      dirX=LOW;
      dirY=HIGH;
    }
    float SteerVal = float(ServoVal) - 90.0;
    digitalWrite(7,dirX);
    digitalWrite(8,dirY);
    int outDir1 = 0;
    int outDir2 = 0;
//    int outDir1 = map(abs(Yval)*((10.0 - SteerVal/45.0)/11.0),0,128,0,255);
//    int outDir2 = map(abs(Yval)*((10.0 + SteerVal/45.0)/11.0),0,128,0,255);
    if(SteerVal >0 ){
//      outDir1 = map(abs(Yval)*(1 - SteerVal/45.0),0,128,0,255);
      outDir1 = map(abs(Yval),0,128,0,255);
      outDir2 = map(abs(Yval),0,128,0,255);
    }else {
      outDir1 = map(abs(Yval),0,128,0,255);
//      outDir2 = map(abs(Yval)*(1 + SteerVal/45.0),0,128,0,255);
      outDir2 = map(abs(Yval),0,128,0,255);
    }

    analogWrite(5,outDir1);
    analogWrite(6,outDir2);

//  if(Serial.available()) 
//    mySerial.write(Serial.read());
  }
  }

//     Serial.print(Xval);
//     Serial.print(',');
//     Serial.println(ServoVal);
}
