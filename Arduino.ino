#include "Servo.h"
#include <Wire.h>

Servo myservo;
float vitesse = 0.5;
float vitesse_droite = vitesse * 180;
float vitesse_gauche = 90 - 90*vitesse;

// Adresse I2C du MPU6050
const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

bool load = false, discharge = false;

double lastY1 = 18, lastY2 = 18, lastY3 = 18, lastY4 = 18, lastY5 = 18, lastY6 = 18;

void setup() {
  myservo.attach(9); // attach the servo to our servo object
  myservo.write(90); // stop the motor

//Angle de base a ~16°
//Doit stopper le chargement a ~11.5°

  // Initialisation de la communication I2C
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // Registre de configuration du MPU6050
  Wire.write(0); // Réveille le MPU6050
  Wire.endTransmission(true);

  // Initialisation de la communication série pour l'affichage des résultats
  Serial.begin(9600);
  Serial.println("Waiting for input...");
}


void loop() {
  if (Serial.available() > 0) {
    char inputChar = Serial.read();

    Serial.print("Received: ");
    Serial.println(inputChar);

    if (inputChar == 'c') {
      // toggle charge
      //load = true;
      //discharge = false;
      myservo.write(180);
    } 
    else if (inputChar == 'd') {
      //discharge = true;  // maintenue
      //load = false;
      myservo.write(0);
    } 
    else if (inputChar == 's') {
      // relâchement pour la décharge
      //discharge = false;
      myservo.write(90);
    }
  }

  if (load) {
    // lecture MPU6050
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);

    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    Tmp = Wire.read() << 8 | Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();

    int xAng = map(AcX, minVal, maxVal, -90, 90);
    int yAng = map(AcY, minVal, maxVal, -90, 90);
    int zAng = map(AcZ, minVal, maxVal, -90, 90);

    lastY6 = lastY5;
    lastY5 = lastY4;
    lastY4 = lastY3;
    lastY3 = lastY2;
    lastY2 = lastY1;
    lastY1 = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);

    y = (lastY1 + lastY2 + lastY3 + lastY4 + lastY5 + lastY6) / 6;

    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    //y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

    Serial.println(y);

    if (y > 10) {
      myservo.write(180); // charge
    } else {
      load = false;
    }
  }

  if (discharge) {
    myservo.write(0); // décharge tant que d est maintenu
  }

    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);

    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    Tmp = Wire.read() << 8 | Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();

    int xAng = map(AcX, minVal, maxVal, -90, 90);
    int yAng = map(AcY, minVal, maxVal, -90, 90);
    int zAng = map(AcZ, minVal, maxVal, -90, 90);

    lastY3 = lastY2;
    lastY2 = lastY1;
    lastY1 = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);

    y = (lastY1 + lastY2 + lastY3) / 3;

    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    //y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

    Serial.println(y);
}
