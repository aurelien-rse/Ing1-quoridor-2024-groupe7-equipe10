#include <LedControl.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    0x3C

#define LoadPin 10
#define DinPin 11
#define ClockPin 13
#define Matrices 4
#define BUTTON_PIN 2  // Pin du bouton pour changer le format horaire (AM/PM)
#define BUTTON_PIN2 3
#define BUTTON_PIN3 4
#define BUTTON_PIN4 5
#define BUZZER_PIN 6 // Connectez le buzzer à la broche 8
bool reveil = false;
bool is12HourFormat = false;
bool pm = false;
int loca =0;
int heures;
int minutes;
int adresse = 1017;   
int adresse1 = 1020;
int adresse2 = 1023;
int adresse3 = 1010;
int adresse4 = 1000;
int alarmHour = 6;
int alarmMinute = 0;
LedControl matriceLed(DinPin, ClockPin, LoadPin, Matrices);
RTC_DS1307 RTC;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  //initialisation des matrices de led
  for (int i = 0; i < Matrices; i++) {
    matriceLed.shutdown(i, false);       
    matriceLed.setIntensity(i, 5);       
    matriceLed.clearDisplay(i);          
  }
  
  //initialisation de la connexion
  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  if (EEPROM.get(adresse,alarmHour)== 0xFF){
    RTC.adjust(DateTime(__DATE__, __TIME__));  }
  else {
    heures=EEPROM.get(adresse3,heures);
    minutes=EEPROM.get(adresse4,minutes);
    RTC.adjust(DateTime(RTC.now().year(), RTC.now().month(), RTC.now().day(), heures, minutes, RTC.now().second()));
    
  }
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_RESET)) {
  Serial.println(F("Ecran OLED non trouvé"));
  for (;;);  // Arrêt du programme si l'écran ne répond pas
  }
  display.begin(SSD1306_SWITCHCAPVCC,OLED_RESET);
  display.setTextColor(SSD1306_WHITE); // Couleur du texte (blanc)
  display.display();   
  delay(2000);
  display.clearDisplay();
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUTTON_PIN2, INPUT);
  pinMode(BUTTON_PIN3, INPUT);
  pinMode(BUTTON_PIN4, INPUT);
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);
  EEPROM.get(adresse,alarmHour);
  EEPROM.get(adresse1,alarmMinute);
  EEPROM.get(adresse2,reveil);
  
}

void loop() {
   DateTime now = RTC.now();
  // Heure actuelle
  heures = now.hour();
  minutes = now.minute();
  if (reveil){
    if (alarmHour==heures && alarmMinute==minutes){
      loca=3;
      
      }
  }
  if (is12HourFormat) {
    if (heures >=12) {
        pm = true;
        heures = heures-12; // Convertit PM
    }else {
      pm = false;
    }
      

}
  
  int digits[] = {
    heures / 10,   // Dizaine des heures
    heures % 10,   // Unité des heures
    minutes / 10,  // Dizaine des minutes
    minutes % 10   // Unité des minutes
  };
  if (digitalRead(BUTTON_PIN) == HIGH && loca==0) {
    delay(200);
    is12HourFormat = !is12HourFormat;  // Basculer entre 12h et 24h
  }
   if (digitalRead(BUTTON_PIN2) == HIGH && loca==0) {
    delay(200);
    loca =1;
  }
  if (digitalRead(BUTTON_PIN3) == HIGH && loca==0) {
    delay(200);
    loca =3;
  }
   if (digitalRead(BUTTON_PIN4) == HIGH && loca==3) {
   delay(200);
   loca =0;
  }
  if (digitalRead(BUTTON_PIN) == HIGH && loca==3) {
   delay(200);
   reveil=!reveil;
  }
  if (digitalRead(BUTTON_PIN2) == HIGH && loca==3) {
   delay(200);
   loca=4;
  }
  
  if (loca==4) {
    changreveil(alarmHour ,alarmMinute);
    loca=3;
  }
   if (digitalRead(BUTTON_PIN4) == HIGH && loca==1) {
      delay(200);
    loca=0;
    }
   if (digitalRead(BUTTON_PIN) == HIGH && loca==1) {
     delay(200);
     loca=2;
   }
   if (loca==2) {
  display.clearDisplay();
  display.setCursor(1,0);  // Position du texte sur l'écran
  display.print(F("Pour le changement"));
  display.setCursor(1,10);  // Position du texte sur l'écran
  display.print(F("2.Augmenter de 1"));
  display.setCursor(1,20);  // Position du texte sur l'écran
  display.print(F("3.Diminuer de 1"));
  display.setCursor(1,30);  // Position du texte sur l'écran
  display.print(F("4.Confirmation"));
  display.display(); 
     changheur(heures,minutes);
     loca=1;
  } 
   


  if (loca ==0){
  for (int i = 0; i < Matrices; i++) {
    matriceLed.clearDisplay(i);        
    afficherChiffre(digits[3-i], i);                         
    
  }
  display.clearDisplay();
  display.setCursor(1,2);  // Position du texte sur l'écran
  display.print(F("1:Passer en am/pm"));
  display.display(); 
  display.drawLine(0,12,127,12,WHITE);
  display.setCursor(1,15);  // Position du texte sur l'écran
  display.print(F("2:Regler heure"));
  display.drawLine(0,25,127,25,WHITE);
  display.setCursor(1,28);  // Position du texte sur l'écran
  display.print(F("3:Reveil"));
  display.drawLine(0,38,127,38,WHITE);
  display.setCursor(1,41);  // Position du texte sur l'écran
  display.print(F("4:Alarme"));
  display.drawLine(0,51,127,51,WHITE);
  if (is12HourFormat) {
    if (pm == true){
      display.setCursor(60,55);  // Position du texte sur l'écran
      display.print(F("PM"));
    }else{
      display.setCursor(60,55);  // Position du texte sur l'écran
      display.print(F("AM"));
    }
  }
  display.display(); 
  delay(500);
  matriceLed.setLed(2, 3, 7, true);
  matriceLed.setLed(2, 4, 7, true);
  delay(500);
}

if (loca==1){
  display.clearDisplay();
  display.setCursor(1,0);  // Position du texte sur l'écran
  display.print(F("1.Lancer changement")); 
  display.setCursor(1,9);  // Position du texte sur l'écran
  display.print(F("4.Quitter"));
  display.display(); 
  for (int i = 0; i < Matrices; i++) {
    matriceLed.clearDisplay(i);        
    afficherChiffre(digits[3-i], i);                         
  }
  

  if (is12HourFormat) {
    if (pm == true){
      display.setCursor(60,55);  // Position du texte sur l'écran
      display.print(F("PM"));
    }else{
      display.setCursor(60,55);  // Position du texte sur l'écran
      display.print(F("AM"));
    }
  }
  display.display(); 
  delay(500);
  matriceLed.setLed(2, 3, 7, true);
  matriceLed.setLed(2, 4, 7, true);
  delay(500);
}
if (loca==3){
  display.clearDisplay();
  display.setCursor(0,0);  // Position du texte sur l'écran
  display.print(F("1.On/Off")); 
  display.setCursor(0,10);  // Position du texte sur l'écran
  display.print(F("2.Reglez le reveil")); 
  display.setCursor(0,20);  // Position du texte sur l'écran
  display.print(F("4.Quitter"));
  display.setCursor(0,40);  // Position du texte sur l'écran
  display.print(alarmHour);
  display.setCursor(15,40);  // Position du texte sur l'écran
  display.print(alarmMinute); 
  display.display(); 
  if (reveil==true){
    display.setCursor(0,50);  // Position du texte sur l'écran
    display.print(F("ON"));
    display.display();
  }else{
    display.setCursor(0,50);  // Position du texte sur l'écran
    display.print(F("OFF"));
    display.display();
    }
  }
  for (int i = 0; i < Matrices; i++) {
    matriceLed.clearDisplay(i);        
    afficherChiffre(digits[3-i], i);                         
  }

  if (is12HourFormat) {
    if (pm == true){
      display.setCursor(60,55);  // Position du texte sur l'écran
      display.print(F("PM"));
    }else{
      display.setCursor(60,55);  // Position du texte sur l'écran
      display.print(F("AM"));
    }
  }
  display.display(); 
  delay(500);
  matriceLed.setLed(2, 3, 7, true);
  matriceLed.setLed(2, 4, 7, true);
  delay(500);
  if (pm==true²){
    heures=heures+12;
  }
  EEPROM.put(adresse2, reveil);
  EEPROM.put(adresse,alarmHour);
  EEPROM.put(adresse1,alarmMinute);
  EEPROM.put(adresse3, heures);
  EEPROM.put(adresse4,minutes);
}

void afficherChiffre(int chiffre, int adresse) {
  const byte chiffres[10][8] = {
    {0x00,0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00},
    {0x00,0x00,0x00, 0x42, 0x7F, 0x40, 0x00, 0x00},  
    {0x00,0x62, 0x51, 0x49, 0x49, 0x46, 0x00, 0x00},  
    {0x00,0x22, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00},  
    {0x00,0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00},  
    {0x00,0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00},  
    {0x00,0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, 0x00},  
    {0x00,0x01, 0x71, 0x09, 0x05, 0x03, 0x00, 0x00},  
    {0x00,0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00},  
    {0x00,0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00}   
  };// Affiche de 0 à 9 dans la matrice en hexadecimal

  byte chiffreTourne[8];

  for (int ligne = 0; ligne < 8; ligne++) {
    chiffreTourne[ligne] = 0;
    for (int colonne = 0; colonne < 8; colonne++) {
      if (chiffres[chiffre][colonne] & (1 << ligne)) {
        chiffreTourne[ligne] |= (1 << (7 - colonne));// Boucle passage de lignes à colonnes
      }
    }
  }

  for (int ligne = 0; ligne < 8; ligne++) {
    matriceLed.setRow(adresse, ligne, chiffreTourne[ligne]);// Affichage de la led au complet
  }
}

void changheur (int &heures, int &minutes){
  bool hourConfirmed = false;  // Flag pour terminer l'ajustement de l'heure
  bool minuteConfirmed = false;  // Flag pour terminer l'ajustement des minutes
  bool validation =false;
  // Modifier l'heure
  while (!hourConfirmed) {
    // Vérifier si le bouton d'incrémentation est pressé
    if (digitalRead(BUTTON_PIN2) == HIGH) {
      delay(200);  // Anti-rebond
      heures = (heures + 1) % 24;  // Incrémenter l'heure, revenir à 0 après 23
      int digits[] = {heures / 10, heures % 10, minutes / 10, minutes % 10};
      afficherChiffre(digits[3], 0);
      afficherChiffre(digits[2], 1);
      afficherChiffre(digits[1], 2);
      afficherChiffre(digits[0], 3);
    }

    // Vérifier si le bouton de décrémentation est pressé
    if (digitalRead(BUTTON_PIN3) == HIGH) {
      delay(200);  // Anti-rebond
      heures = (heures - 1 + 24) % 24;  // Décrémenter l'heure, revenir à 23 après 0
      int digits[] = {heures / 10, heures % 10, minutes / 10, minutes % 10};
      afficherChiffre(digits[3], 0);
      afficherChiffre(digits[2], 1);
      afficherChiffre(digits[1], 2);
      afficherChiffre(digits[0], 3);
    }

    // Vérifier si le bouton de confirmation est pressé pour valider l'heure
    if (digitalRead(BUTTON_PIN4) == HIGH && validation ==false) {
      delay(200);
      hourConfirmed = true;  // Terminer l'ajustement de l'heure
      int digits[] = {heures / 10, heures % 10, minutes / 10, minutes % 10};
      afficherChiffre(digits[3], 0);
      afficherChiffre(digits[2], 1);
      afficherChiffre(digits[1], 2);
      afficherChiffre(digits[0], 3);
      RTC.adjust(DateTime(RTC.now().year(), RTC.now().month(), RTC.now().day(), heures, minutes, RTC.now().second()));
          }
  }
  validation = true;
  // Modifier les minutes
  while (!minuteConfirmed) {
    // Vérifier si le bouton d'incrémentation est pressé pour les minutes
    if (digitalRead(BUTTON_PIN2) == HIGH) {
      delay(200);
      minutes = (minutes + 1) % 60;  // Incrémenter les minutes, revenir à 0 après 59
      int digits[] = {heures / 10, heures % 10, minutes / 10, minutes % 10};
      afficherChiffre(digits[3], 0);
      afficherChiffre(digits[2], 1);
      afficherChiffre(digits[1], 2);
      afficherChiffre(digits[0], 3);
    }

    // Vérifier si le bouton de décrémentation est pressé pour les minutes
    if (digitalRead(BUTTON_PIN3) == HIGH) {
      delay(200);
      minutes = (minutes - 1 + 60) % 60;  // Décrémenter les minutes, revenir à 59 après 0
      int digits[] = {heures / 10, heures % 10, minutes / 10, minutes % 10};
      afficherChiffre(digits[3], 0);
      afficherChiffre(digits[2], 1);
      afficherChiffre(digits[1], 2);
      afficherChiffre(digits[0], 3);
    }

    // Vérifier si le bouton de confirmation est pressé pour valider les minutes
    if (digitalRead(BUTTON_PIN4) == HIGH && validation == true) {
      delay(200);
      minuteConfirmed = true;  // Terminer l'ajustement des minutes
      int digits[] = {heures / 10, heures % 10, minutes / 10, minutes % 10};
      afficherChiffre(digits[3], 0);
      afficherChiffre(digits[2], 1);
      afficherChiffre(digits[1], 2);
      afficherChiffre(digits[0], 3);
      RTC.adjust(DateTime(RTC.now().year(), RTC.now().month(), RTC.now().day(), heures, minutes, RTC.now().second()));  // Sauvegarder l'heure et les minutes dans le RTC
    }
  }
}
void changreveil (int &alarmHour ,int &alarmMinute){
  bool hourConfirmed = false;  // Flag pour terminer l'ajustement de l'heure
  bool minuteConfirmed = false;  // Flag pour terminer l'ajustement des minutes
  bool validation =false;
  // Modifier l'heure
  while (!hourConfirmed) {
    // Vérifier si le bouton d'incrémentation est pressé
    if (digitalRead(BUTTON_PIN2) == HIGH) {
      delay(200);  // Anti-rebond
      alarmHour = (alarmHour + 1) % 24;  // Incrémenter l'heure, revenir à 0 après 23
        display.clearDisplay();
        display.setCursor(1,0);  // Position du texte sur l'écran
        display.print(F("Pour le changement"));
        display.setCursor(1,10);  // Position du texte sur l'écran
        display.print(F("2.Augmenter de 1"));
        display.setCursor(1,20);  // Position du texte sur l'écran
        display.print(F("3.Diminuer de 1"));
        display.setCursor(1,30);  // Position du texte sur l'écran
        display.print(F("4.Confirmation"));
        display.setCursor(0,40);  // Position du texte sur l'écran
        display.print(alarmHour);
        display.setCursor(15,40);  // Position du texte sur l'écran
        display.print(alarmMinute); 
        display.display();
    }

    // Vérifier si le bouton de décrémentation est pressé
    if (digitalRead(BUTTON_PIN3) == HIGH) {
      delay(200);  // Anti-rebond
      alarmHour = (alarmHour - 1 + 24) % 24;  // Décrémenter l'heure, revenir à 23 après 0
        display.clearDisplay();
        display.setCursor(1,0);  // Position du texte sur l'écran
        display.print(F("Pour le changement"));
        display.setCursor(1,10);  // Position du texte sur l'écran
        display.print(F("2.Augmenter de 1"));
        display.setCursor(1,20);  // Position du texte sur l'écran
        display.print(F("3.Diminuer de 1"));
        display.setCursor(1,30);  // Position du texte sur l'écran
        display.print(F("4.Confirmation"));
        display.setCursor(0,40);  // Position du texte sur l'écran
        display.print(alarmHour);
        display.setCursor(15,40);  // Position du texte sur l'écran
        display.print(alarmMinute); 
        display.display();
    }

    // Vérifier si le bouton de confirmation est pressé pour valider l'heure
    if (digitalRead(BUTTON_PIN4) == HIGH && validation ==false) {
      delay(200);
      hourConfirmed = true;  // Terminer l'ajustement de l'heure
      }
  }
  validation = true;
  // Modifier les minutes
  while (!minuteConfirmed) {
    // Vérifier si le bouton d'incrémentation est pressé pour les minutes
    if (digitalRead(BUTTON_PIN2) == HIGH) {
      delay(200);
      alarmMinute = (alarmMinute + 1) % 60;  // Incrémenter les minutes, revenir à 0 après 59
        display.clearDisplay();
        display.setCursor(1,0);  // Position du texte sur l'écran
        display.print(F("Pour le changement"));
        display.setCursor(1,10);  // Position du texte sur l'écran
        display.print(F("2.Augmenter de 1"));
        display.setCursor(1,20);  // Position du texte sur l'écran
        display.print(F("3.Diminuer de 1"));
        display.setCursor(1,30);  // Position du texte sur l'écran
        display.print(F("4.Confirmation"));
        display.setCursor(0,40);  // Position du texte sur l'écran
        display.print(alarmHour);
        display.setCursor(15,40);  // Position du texte sur l'écran
        display.print(alarmMinute); 
        display.display();
      
    }

    // Vérifier si le bouton de décrémentation est pressé pour les minutes
    if (digitalRead(BUTTON_PIN3) == HIGH) {
      delay(200);
      alarmMinute = (alarmMinute - 1 + 60) % 60;  // Décrémenter les minutes, revenir à 59 après 0
    }
        display.clearDisplay();
        display.setCursor(1,0);  // Position du texte sur l'écran
        display.print(F("Pour le changement"));
        display.setCursor(1,10);  // Position du texte sur l'écran
        display.print(F("2.Augmenter de 1"));
        display.setCursor(1,20);  // Position du texte sur l'écran
        display.print(F("3.Diminuer de 1"));
        display.setCursor(1,30);  // Position du texte sur l'écran
        display.print(F("4.Confirmation"));
        display.setCursor(0,40);  // Position du texte sur l'écran
        display.print(alarmHour);
        display.setCursor(15,40);  // Position du texte sur l'écran
        display.print(alarmMinute); 
        display.display();

    // Vérifier si le bouton de confirmation est pressé pour valider les minutes
    if (digitalRead(BUTTON_PIN4) == HIGH && validation == true) {
      delay(200);
      minuteConfirmed = true;  // Terminer l'ajustement des minutes
      
  }
 }
}
