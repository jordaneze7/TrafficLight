#define LEDR 13
#define LEDJ 12
#define LEDV 11
#define LEDPIETON 10
#define BTN 2

unsigned long duration_rouge = 15000;
unsigned long duration_jaune = 5000;
unsigned long duration_vert = 15000;
unsigned long tempsActuel = millis();
unsigned long tempsReset = 0;
bool pietonDemande = true;

enum Etatfeu {
  FEUROUGE,
  FEUJAUNE,
  FEUVERT
};

Etatfeu etatActuel = FEUROUGE;

void pieton()
{
  digitalWrite(LEDV, LOW);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDJ, LOW);
  for (int i = 0; i < 10; i++) {
    unsigned long t1 = millis();
    while (millis() - t1 < 500);  // 250 ms off
    digitalWrite(LEDPIETON, HIGH);

    unsigned long t2 = millis();
    while (millis() - t2 < 500);  // 250 ms on
    digitalWrite(LEDPIETON, LOW);
  }
  etatActuel = FEUVERT;
  tempsReset = tempsActuel;
}

void feu_rouge() {
  if(digitalRead(BTN) == LOW)
  {
    pietonDemande = true;
  }
  if(pietonDemande)
  {
    pieton();
    pietonDemande = false;
  }
  digitalWrite(LEDV, LOW);
  digitalWrite(LEDJ, LOW);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDPIETON, LOW);
  if((tempsActuel - tempsReset) >= duration_rouge)
  {
    etatActuel = FEUVERT;
    tempsReset = tempsActuel;
  }
}

void feu_jaune() {
  if(digitalRead(BTN) == LOW)
  {
    pietonDemande = true;
  }
  digitalWrite(LEDV, LOW);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDJ, HIGH);
  digitalWrite(LEDPIETON, LOW);
  if((tempsActuel - tempsReset) >= duration_jaune)
  {
    etatActuel = FEUROUGE;
    tempsReset = tempsActuel;
  }
}

void feu_vert() {
  if(digitalRead(BTN) == LOW)
  {
    pietonDemande = true;
  }
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDJ, LOW);
  digitalWrite(LEDV, HIGH);
  digitalWrite(LEDPIETON, LOW);
  if((tempsActuel - tempsReset) >= duration_vert)
  {
    etatActuel = FEUJAUNE;
    tempsReset = tempsActuel;
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDJ, OUTPUT);
  pinMode(LEDV, OUTPUT);
  pinMode(LEDPIETON, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  tempsActuel = millis();
  switch(etatActuel) {
    case FEUROUGE:
      feu_rouge();
    break;
    case FEUJAUNE:
      feu_jaune();
    break;
    case FEUVERT:
      feu_vert();
    break;
  }
}

