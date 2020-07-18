//====================================================================================================
/******************************************************************
 Created with thingerbits Academy for Arduino - 16.03.2020 23:29:38
 Project     : 9 LED Pattern
 Author      : Hasarinda Manjula
 Description : Arduino PIN d3 to D12
******************************************************************/
/*
int t = 40;
int rnd =5;
int pat1t =75;

void setup()
{
   for(int i=3; i<=12; i++)
   pinMode(i,OUTPUT);
}

void loop(){

   for(int i=0; i<=rnd; i++) {
   pat1();}
   for(int i=0; i<=rnd; i++){
   pat2();}
   for(int i=0; i<=rnd; i++) {
   pat3();}
   for(int i=0; i<=rnd; i++) {
   pat4();}
   for(int i=0; i<=rnd; i++){
   pat5();}
   for(int i=0; i<=rnd; i++) {
   pat6();}
   for(int i=0; i<=rnd; i++) {
   pat7();}
   for(int i=0; i<=rnd; i++) {
   pat8();}
   for(int i=0; i<=rnd; i++) {
   pat9();}


}

void pat1(){
    for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      delay(pat1t);
      digitalWrite(i,LOW);

    }

    for(int i=11; i>=4; i--) {
      digitalWrite(i,HIGH);
      delay(pat1t);
      digitalWrite(i,LOW);
    }
}
void pat2(){
     for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      digitalWrite(i-1,HIGH);
      digitalWrite(i+1,HIGH);
      delay(100);
      digitalWrite(i,LOW);
      digitalWrite(i-1,LOW);
      digitalWrite(i+1,LOW);
    }

    for(int i=11; i>=4; i--) {
      digitalWrite(i,HIGH);
      digitalWrite(i-1,HIGH);
      digitalWrite(i+1,HIGH);
      delay(100);
      digitalWrite(i,LOW);
      digitalWrite(i-1,LOW);
      digitalWrite(i+1,LOW);
    }
}
void pat3(){
  for(int i=3; i<=12; i=i+2) {
      digitalWrite(i,HIGH);
      delay(100);
      digitalWrite(i,LOW);

    }

    for(int i=12; i>=3; i=i-2) {
      digitalWrite(i,HIGH);
      delay(100);
      digitalWrite(i,LOW);
    }
}
void pat4(){
      for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      delay(100);
    }

    for(int i=12; i>=2; i--) {
      digitalWrite(i,HIGH);
      delay(100);
      digitalWrite(i,LOW);
    }
}
void pat5(){
     for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      }
    delay(100);
    for(int i=3; i<=12; i++) {
      digitalWrite(i,LOW);
      }
    delay(100);
}
void pat6(){
       for(int i=3; i<=8; i++) {
      digitalWrite(i,HIGH);
      }
    for(int i=8; i<=12; i++) {
      digitalWrite(i,LOW);
      }
    delay(200);
    for(int i=3; i<=8; i++) {
      digitalWrite(i,LOW);
      }
    for(int i=8; i<=12; i++) {
      digitalWrite(i,HIGH);
      }
    delay(200);
}
void pat7(){
       for(int i=3; i<=12; i=i+2) {
      digitalWrite(i,HIGH);
      }
    for(int i=4; i<=12; i=i+2) {
      digitalWrite(i,LOW);
      }
    delay(200);
     for(int i=3; i<=12; i=i+2) {
      digitalWrite(i,LOW);
      }
    for(int i=4; i<=12; i=i+2) {
      digitalWrite(i,HIGH);
      }
    delay(200);
}
void pat8(){
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    delay(t);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    delay(t);
    digitalWrite(6,HIGH);
    digitalWrite(9,HIGH);
    delay(t);
    digitalWrite(6,LOW);
    digitalWrite(9,LOW);
    delay(t);
    digitalWrite(5,HIGH);
    digitalWrite(10,HIGH);
    delay(t);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    delay(t);
    digitalWrite(4,HIGH);
    digitalWrite(11,HIGH);
    delay(t);
    digitalWrite(4,LOW);
    digitalWrite(11,LOW);
    delay(t);
    digitalWrite(3,HIGH);
    digitalWrite(12,HIGH);
    delay(t);
    digitalWrite(3,LOW);
    digitalWrite(12,LOW);
    delay(t);
     digitalWrite(4,HIGH);
    digitalWrite(11,HIGH);
    delay(t);
    digitalWrite(4,LOW);
    digitalWrite(11,LOW);
    delay(t);
    digitalWrite(5,HIGH);
    digitalWrite(10,HIGH);
    delay(t);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    delay(t);
    digitalWrite(6,HIGH);
    digitalWrite(9,HIGH);
    delay(t);
    digitalWrite(6,LOW);
    digitalWrite(9,LOW);
    delay(t);
}

void pat9(){
    for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
    }
     for(int i=3; i<=12; i++) {
      digitalWrite(i,LOW);
      delay(100);
      digitalWrite(i,HIGH);
    }
    for(int i=11; i>=4; i--) {
      digitalWrite(i,LOW);
      delay(100);
      digitalWrite(i,HIGH);
    }

}
*/
//====================================================================================================
/*
https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/

//Global Variables
    int sensorPin = 0;      //pin number to use the ADC
    int sensorValue = 0;    //initialization of sensor variable, equivalent to EMA Y
    float EMA_a = 0.6;      //initialization of EMA alpha
    int EMA_S = 0;          //initialization of EMA S

void setup(){
    Serial.begin(115200);           //setup of Serial module, 115200 bits/second
    EMA_S = analogRead(sensorPin);  //set EMA S for t=1
}

void loop(){
    sensorValue = analogRead(sensorPin);                //read the sensor value using ADC
    EMA_S = (EMA_a*sensorValue) + ((1-EMA_a)*EMA_S);    //run the EMA
    Serial.println(EMA_S);                              //print digital value to serial
    delay(50);                                          //50ms delay
}
*/