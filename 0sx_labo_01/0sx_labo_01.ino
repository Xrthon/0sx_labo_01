
const short NUMBER_OF_BLINK = 4;
const short BLINK_INTERVAL = 500;  
const short TWO_SECOND  = 2000; 

int ledState = LOW;  // ledState état de la lumiére
unsigned short  appState = 1; //État de l'application
unsigned short  currentBlink = 0; //État de l'application
short fadeAmout = 4;
short brightness = 255;
unsigned long currentMilli=0;
unsigned long previousMillis = 0;  // dernier changement de la led
unsigned short stateOfcycle = 0;

void setup() {
  // set the digital pin as output:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  

  switch(appState){

    case 1:
      //Allume la LED
      if (currentMillis-previousMillis >= TWO_SECOND) {
          previousMillis = currentMillis;
          ledState!=ledState;
          appState++;
        }
      Serial.println("Allume – 1993855");
      break;
    case 2:
      //Clignotement de la LED
      if(currentBlink<=NUMBER_OF_BLINK){
        if(currentMillis-previousMillis >= BLINK_INTERVAL) {
          previousMillis = currentMillis;
          if (ledState == LOW) {
              ledState = HIGH;
              currentBlink++;
              Serial.println("Clignotement – 1993855");


          } else {
              ledState = LOW;
          }
          digitalWrite(LED_BUILTIN, ledState);
        }
      }else{
        currentBlink = 0;
        digitalWrite(LED_BUILTIN, HIGH);
        ledState=255;
        ++appState;
      }
        break;
      case 3: 
        //Fondu de la lumiére LED 
        Serial.println("Variation – 1993855 ");
        if(currentMillis-previousMillis >= 8) {
          analogWrite(LED_BUILTIN, ledState);
          previousMillis = currentMillis;
          ledState -= fadeAmout;
          if (ledState <=0) {
            Serial.println("Variation – 1993855 ");
            ledState=LOW;
            digitalWrite(LED_BUILTIN, ledState);
            ++appState;
            previousMillis = currentMillis;
          }
        }
        break;
      case 4:
        //Éteint la lumiére  LED
        Serial.println("Éteint – 1993855");
        if (currentMillis-previousMillis >= TWO_SECOND) {
          previousMillis = currentMillis;
          ledState =HIGH;
          digitalWrite(LED_BUILTIN, ledState);
          appState=1;
        }
        break;
    }
    

  
}

void switchTheAppState(){
  
}


