#include <IRremote.h> 
#include <IRremoteInt.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

/*
  @Proyecto:    Robot Mini-Sumo
  @Autor:       Equipo Weber Bot
  @Placa:       Arduino NANO
  @Descripción: Código para robot minisumo, con sistema de detección infrarrojo
*/

// ========================== Declaración de Variables ==========================
int emisorIR       = 3;  // emisores infrarrojos controlados a través de transistor 2n2222a
int emisorLinea    = 2;  // emisores infrarrojos sigue linas 
const int sensor0        = A0;  // Receptores IR
const int sensor45       = A1;  //
const int sensor90       = A2;  //
const int sensor135      = A3;  //
const int sensor180      = A4;  //
const int sensor270      = A5;  //

int valor0 = 0;  //inicializamos el valor que va a corresonder con la lectura de los sensores
int valor45 = 0;
int valor90 = 0;
int valor135 = 0;
int valor180 = 0;
int valor270 = 0;

// ========================== SENSORES SIGUE LINEAS  ==========================
int sensorA  = A6;
int sensorB  = A7;

int valorA   = 0;
int valorB   = 0;

// ========================== MOTORES ==========================================
int motorR1        = 10;  // Pin Motor Derecha Adelante
int motorR2        = 9;   // Pin Motor Derecha Atras
int motorL1        = 11;   // Pin Motor Izquierda Adelante
int motorL2        = 6;   // Pin Motor Izquierda Atras

// ========================== LEDS INDICADORES ==================================
int ledTest        = 13;  // Led indicador encendido
int ledR           = 7;   // Led indicador Ready, semaforo
int ledG           = 4;  // Led indicador LUCHA!
int ledB           = 5;  // Led indicador otros

/*
int botonA       = 6;   // Pin de activación
int botonModo    = 2;
//int botonReset = ;
*/

int receptorIR = 8;
IRrecv receptorIr(receptorIR);
decode_results codigoLeido;

//Condicionales

boolean Test    = true;      // Indica el modo pruebas del código
boolean Lucha   = false;     // Indica si el sumo ha sido activado para competir


void setup() {
  Serial.begin(9600);
  Serial.println("Weber Bot iniciando..."); //

  receptorIr.enableIRIn();

//configuración de los pines de entrada y salida
  
  pinMode(ledTest, OUTPUT);
  pinMode(emisorIR, OUTPUT);
  pinMode(emisorLinea, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);  
  pinMode(ledB, OUTPUT);

  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
  

 // pinMode(botonA, INPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);

  analogWrite(motorR1, 0);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 0);

  pinMode(sensor0, INPUT);
  pinMode(sensor45, INPUT);
  pinMode(sensor90, INPUT);
  pinMode(sensor135, INPUT);
  pinMode(sensor180, INPUT);
  pinMode(sensor270, INPUT);

  for(int i=0; i<3; i++){
    digitalWrite(ledTest, HIGH);
    delay(500);
    digitalWrite(ledTest, LOW);
    delay(500);      
  }  

}

void loop(){
  if(Lucha) {
    Serial.println("<<< MODO LUCHA >>>");

    //
    if (receptorIr.decode(&codigoLeido)) { 
    Serial.println(codigoLeido.value, HEX);

    switch (codigoLeido.value) {
    
    case 0xFF6897:
      for(int i=0; i<5; i++){
        digitalWrite(ledR, LOW);
        delay(500);
        digitalWrite(ledR, HIGH);
        delay(500);      
      }  

      lucha(); 
    
    break;
    }
   receptorIr.resume();
    }
  }//cierra el modo lucha

  else if (Test) {
    Serial.println("<<< MODO TEST >>>");
    test();
  }

  else {
    error();
    Serial.println("<<< ERROR: modo no seleccionado >>>");
  }



}//cierra el loop

/////////////////////////////////
//Programas !!

void lucha(){

  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);

  valorA = analogRead(sensorA);
  valorB = analogRead(sensorB);  
  //boolean insuto = valor;
  

  if(valorA >700 && valorB >700){
  //si se encuentra dentro del circulo, escanea y mueve



  }

  else if(valorA >700 && valorB <700){
  //si detectó el limite en el sensor B, volver en sentido contrario y girar

  }

  else if(valorA <700 && valorB >700){
  //si detectó el limite en el sensor A, volver en sentido contrario y girar
  
  }

  else {
    //error
  }

}




//funcion test(#)

void test() {
  
  //Prueba LEDs
  digitalWrite(ledG, LOW);
  delay(1000);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);
  delay(1000);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledR, LOW);
  delay(1000);
  digitalWrite(ledR, HIGH);

  //Prueba emisores
  digitalWrite(emisorIR, HIGH);
  delay(2000);
  digitalWrite(emisorIR, LOW);

  //Prueba motores
  rotarR();
  delay(1000);
  rotarL();
  delay(1000);
  adelante();
  delay(1000);
  atras();
  delay(1000);
  stop();

}

void error(){
  Serial.println("Error desconocido..");
  digitalWrite(ledTest, HIGH);
}



/*


priorizar el sensor linea, si detecta linea retrocer y girar 180º

Activar renotamente, el robot espara 5s, con secuencia de
pitidos y ledR, luego comienza la secuencia lucha, ledV y ledB.

escanear y perseguir al contrincante (seguir al contrincante
 si no se detecta una linea)
La condicion va a ser que el valor de los sigue lineas sea "negro"
escanear, mover, repetir secuencia.

sino se cumple la condicion de estar dentro del color negro porque llegamos al limite
entonces ejecutar la funcion, "daleAtras();""
*/

void atras(){
  analogWrite(motorR1, 0);
  analogWrite(motorR2, 255);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 255);
}
void adelante(){
  analogWrite(motorR1, 255); // motor derecho adelante
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 255);
  analogWrite(motorL2, 0);
}


void stop(){
  analogWrite(motorR1, 0);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 0);
}
void rotarR(){
  analogWrite(motorR1, 255);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 255);
}
void rotarL(){
  analogWrite(motorR1, 0);
  analogWrite(motorR2, 255);
  analogWrite(motorL1, 255);
  analogWrite(motorL2, 0);
}
