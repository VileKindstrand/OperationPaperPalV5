// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~  KONSTANTER  ~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// För knappar
const int buttonPinTwo = 2;           // Pin för knapp två
// const int buttonPinThree = 6;         // Pin för knapp tre om det skulle behövas
int buttonStateTwo = 0;               // Variabel för att lagra tillståndet för knapp två
// int buttonStateThree = 0;           // Variabel för att lagra tillståndet för knapp tre om det skulle behövas

// För ultraljudssensorn
const int trigPin = 3;                
const int echoPin = 4;                
float duration, distance;             // Variabler för ultraljudssensoravläsningar

// För stegmotorn
int motorUppNedPin1 = 9;              // Blå - 28BYJ48 pin 1
int motorUppNedPin2 = 10;             // Rosa - 28BYJ48 pin 2
int motorUppNedPin3 = 11;             // Gul - 28BYJ48 pin 3
int motorUppNedPin4 = 12;             // Orange - 28BYJ48 pin 4
int motorSpeed = 2400;                // Variabel för att ställa in stegmotorhastighet
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};  // Sekvens för stegmotorn

// variabel som representerar hur många toalettrutor som använts
int wipe_count = 0;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~  VOID SETUP  ~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {
  // deklarerar att knappar är en input
  pinMode(buttonPinTwo, INPUT);
  // pinMode(buttonPinThree, INPUT);  ifall man skulle vela implementera en tredje knapp

  // För ultraljudssensorn
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  // Deklarera motorpinnar som utgångar
  pinMode(motorUppNedPin1, OUTPUT);
  pinMode(motorUppNedPin2, OUTPUT);
  pinMode(motorUppNedPin3, OUTPUT);
  pinMode(motorUppNedPin4, OUTPUT);
  Serial.begin(9600);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~  VOID LOOP  ~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void loop() {
  buttonStateTwo = digitalRead(buttonPinTwo);
  // buttonStateThree = digitalRead(buttonPinThree);    ifall man skulle vela implementera en tredje knapp

  if (buttonStateTwo == HIGH) {   // if satsen startar när knappen blir tryckt på. Så länge sensorn inte har någonting framför sig kommer motorn att rotera. Det här görs i små intervallen
    sensorThing();
    while (distance > 15) {
      sensorThing();
      actuallySpins();
    }
    wipe_count += 2;    //adderar wipe_count variabeln med två
    delay(500);
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~  FUNKTIONER  ~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sensorThing() {    //funktion för ultraljudssensorn
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print("Avstånd: ");
  Serial.println(distance);
  delay(100);
}

void fram() {   //funktion för att få motorn att rotera "framåt"
  for (int i = 7; i >= 0; i--) {
    setOutputUppNed(i);
    delayMicroseconds(motorSpeed);
  }
}

void bak() {    //funktion för att få motorn att rotera "bakåt"
  for (int i = 0; i < 8; i++) {
    setOutputUppNed(i);
    delayMicroseconds(motorSpeed);
  }
}

void actuallySpins() {    //funkion som tar in "fram" eller "bak" funktion och startar den faktiskt funktionen.   for (int i = 0; i < x; i++)  "x" bestämmer hur stor rotationen per "step" är
  for (int i = 0; i < 12; i++) {
    bak();
  }
}

void setOutputUppNed(int out) {   //motorn använder sig av magneter som måste sättas på i en viss ordning. Den här funktionen säger till att motorn gör just detta.
  digitalWrite(motorUppNedPin1, bitRead(lookup[out], 0));
  digitalWrite(motorUppNedPin2, bitRead(lookup[out], 1));
  digitalWrite(motorUppNedPin3, bitRead(lookup[out], 2));
  digitalWrite(motorUppNedPin4, bitRead(lookup[out], 3));
}
