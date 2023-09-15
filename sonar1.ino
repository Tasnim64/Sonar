#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 5;
const int echoPin = 18;
const int buzzerPin = 13;
const int LED1 = 27;
const int LED2 = 14;
const int LED3 = 12;

#define SOUND_SPEED 0.0343
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distanceCm = duration * SOUND_SPEED / 2;
    distanceInch = distanceCm * CM_TO_INCH;

    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.print("Distance (inch): ");
    Serial.println(distanceInch);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(distanceCm);
    lcd.print("cm");
    lcd.print(distanceInch);
    lcd.print("inch");

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(buzzerPin, LOW);

    if (distanceCm > 10 && distanceCm <= 15) {
      lcd.setCursor(0, 1);
      lcd.print("ALERT");
      Serial.println("ALERT");
      digitalWrite(LED1, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      digitalWrite(buzzerPin, LOW);
    } else if (distanceCm > 5 && distanceCm <= 10) {
      lcd.setCursor(0, 1);
      lcd.print("ALERT ALERT");
      Serial.println("ALERT ALERT");
      digitalWrite(LED2, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(250);
      digitalWrite(LED2, LOW);
      digitalWrite(buzzerPin, LOW);
    } else if (distanceCm > 0 && distanceCm <= 5) {
      lcd.setCursor(0, 1);
      lcd.print("ALERT ALERT ALERT");
      Serial.println("ALERT ALERT ALERT");
      digitalWrite(LED3, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(350);
      digitalWrite(LED3, LOW);
      digitalWrite(buzzerPin, LOW);
    }
  }
}
