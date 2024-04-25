#include <Servo.h>

#define PULSADOR_PIN 14 //Antes5
#define PULSADOR_EMERGENCIA 16
#define LED_VERDE_PIN 0
#define SERVO 2

int contadorPulsos = 0;
int brillo = 0;
Servo myservo; 

void setup() {
  pinMode(PULSADOR_PIN, INPUT_PULLUP);
  pinMode(PULSADOR_EMERGENCIA, INPUT_PULLUP);
  pinMode(LED_VERDE_PIN, OUTPUT);

  myservo.attach(SERVO);
  myservo.write(0);   
}

void loop() {
  // Verificar si se ha presionado el pulsador
  if (digitalRead(PULSADOR_PIN) == LOW) {
    // Esperar un breve tiempo para evitar falsos positivos
    delay(50);
    // Esperar hasta que el pulsador sea liberado
    while (digitalRead(PULSADOR_PIN) == LOW) {
      // Esperar
    }
    delay(50);
    
    // Incrementar el contador de pulsos
    contadorPulsos++;
    if (contadorPulsos == 4) {
        contadorPulsos = 1;
    }
    Serial.println("Pulsador pulsado");
  }

  if (digitalRead(PULSADOR_EMERGENCIA) == LOW) {
    // Esperar un breve tiempo para evitar falsos positivos
    delay(50);
    // Esperar hasta que el pulsador sea liberado
    while (digitalRead(PULSADOR_EMERGENCIA) == LOW) {
      // Esperar
    }
    delay(50);

    contadorPulsos = 0;
  }

  regular_LED_Servo(contadorPulsos);
}

void regular_LED_Servo(int contadorPulsos) {
  brillo = 0;
  switch (contadorPulsos) {
    case 0:
      myservo.write(0);
      brillo = 0;
      break;
    case 1:
      myservo.write(0);     
      brillo = 50; // Baja intensidad
      break;
    case 2:
      myservo.write(90);
      brillo = 100; // Media intensidad
      break;
    case 3:
      myservo.write(180);
      brillo = 255; // Alta intensidad
      break;
  }
  analogWrite(LED_VERDE_PIN, brillo);
}
