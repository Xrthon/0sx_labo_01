
const short NUMBER_OF_BLINK = 4;
const short BLINK_INTERVAL = 500;  
const short TWO_SECOND  = 2000;
const short FADE_TOTAL_TIME = 2048;
const short FADE_TOTAL_VALUE = 256;

unsigned short ledState = LOW;
unsigned short  appState = 1; 


//Gestion du temps 
unsigned long currentMillis=0;
unsigned long previousMillis = 0;

void setup() {
  // set the digital pin as output:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  //Sinon usigned long currentMillis = ....
  currentMillis = millis();

  switch(appState){
    case 1:
      //Allumer la LED
      turnTheLEDOnOrOff(TWO_SECOND, HIGH);
      break;
    case 2:
      //Clignotement de la LED
      blinkTheLED(NUMBER_OF_BLINK,BLINK_INTERVAL);
      break;
    case 3: 
      //Fondu de la lumiére LED 
      fadeTheLED(FADE_TOTAL_TIME,FADE_TOTAL_VALUE);
      break;
    case 4:
      //Éteindre la Led
      turnTheLEDOnOrOff(TWO_SECOND, LOW);
      break;
  }
}





void fadeTheLED(const int TOTAL_DURATION, const short START_FADE_VALUE){
  static short brightness = START_FADE_VALUE;
  static short fadeAmout = (brightness>=127) ? -1 : 1;
  ledState = (brightness>=127) ?  HIGH: LOW;

  //Calculer le temps pour chaque étape
  static int durationFadeStep = (TOTAL_DURATION/(brightness/fadeAmout));

  //Mettre le temps de la duration positif
  durationFadeStep = (durationFadeStep < 0) ? (durationFadeStep*-1): durationFadeStep;
  static int showDA = 0;
  
  //On afficher l'état et le DA
  if(showDA<1){
    Serial.println("\nVariation – 1993855 ");
    digitalWrite(LED_BUILTIN, ledState);
    ++showDA;
  }
  if(currentMillis-previousMillis >= durationFadeStep) {
    analogWrite(LED_BUILTIN, brightness);
    previousMillis = currentMillis;
    brightness += fadeAmout;
    if(brightness<=0){
      appState++;
      brightness = START_FADE_VALUE;
      showDA=0;
    }
  }
}
void  blinkTheLED(const int MAX_BLINK, const int BLINK_INTERVAL){
  static int compteur = 0;
  static unsigned short currentBlink = 0; //BLink en cours

  //On afficher l'état et le DA
  if(compteur<1){
    Serial.print("Clignotement - 1993855 --> ");
    compteur++;
  }

  //On s'assure que le nombre de clignotement effectuer ne dépasse pas le nombre Maximum
  if(currentBlink<MAX_BLINK){
    if(currentMillis-previousMillis >= BLINK_INTERVAL) {
      previousMillis = currentMillis;
      //Changer l'état de la led à l'aide d'un TRUE | FALSE 
      ledState = (ledState == LOW) ? HIGH : LOW;
      digitalWrite(LED_BUILTIN, ledState);
      if (ledState) {
        currentBlink++;
        Serial.print(compteur++);
        Serial.print(" ");
      }
    }
  }else{
    //Rénitialisation pour la prochaine loop()
    compteur=0;
    currentBlink=0;
    appState++;
  }
  
}
void turnTheLEDOnOrOff(const int TIME_TO_WAIT, const int VALUE){
  static int showDA = 0;
  ledState = (VALUE==1) ? HIGH : LOW;
  if(showDA<1){
    if(!ledState){
    Serial.println("Éteint - 1993855");
    digitalWrite(LED_BUILTIN, ledState);
    }else{
    Serial.println("Allumé - 1993855");
    digitalWrite(LED_BUILTIN, ledState);
    }
    showDA++;
  }



  if (currentMillis-previousMillis >= TIME_TO_WAIT) {
  showDA=0;
  previousMillis = currentMillis;
  if(!ledState){
    appState=1;
    digitalWrite(LED_BUILTIN, ledState);
  }else{
    appState++;
  }

  }
}


