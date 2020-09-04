#include <IRremote.h>
//
#define soundPin A0
#define relayPin A1

const int receiverPin = 7;
IRrecv irrecv(receiverPin);
decode_results results;
bool isLightOn = true;
bool setOnVoice = true;

void setup() {
  
  Serial.begin (9600);
  pinMode(soundPin, INPUT);
  pinMode(relayPin, OUTPUT);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  long sum;
  long sum1;
  long sum2;
  
  
  //  Serial.println(results.value);
  if(setOnVoice){
    if (irrecv.decode(&results)){
      if(results.value == 904613785)
        setOnVoice = false;

      
        
      irrecv.resume();
    }else{
      sum1 = analogRead(soundPin);
      delay(1);
      sum2 = analogRead(soundPin);
      sum = sum2 - sum1;
      
      if(sum < -600 || sum > 600){
        Serial.println(sum);
        if(isLightOn)
          digitalWrite(relayPin, HIGH);
        else
          digitalWrite(relayPin, LOW);
        isLightOn = !isLightOn;     
        delay(300);
      }else
        Serial.println(0);
    }
  }else{
    if (irrecv.decode(&results)){
      switch (results.value){
      case 3018811909:
        cheshmak();
        break;
        
      case 904613785:
        digitalWrite(relayPin, HIGH);
        delay(300);
        digitalWrite(relayPin, LOW);
        delay(300);
        digitalWrite(relayPin, HIGH);
        delay(300);
        setOnVoice = true;
      break;
      
      default:
        if(isLightOn)
          digitalWrite(relayPin, HIGH);
        else
          digitalWrite(relayPin, LOW);
        isLightOn = !isLightOn;
        delay(300);
      break;
      } 
      irrecv.resume();
    }
  }
}


void cheshmak(){
  int n=0;
  while(n<4){
    digitalWrite(relayPin, HIGH);
    delay(400);
    digitalWrite(relayPin, LOW);
    delay(400); 
    n++;
  }
}
