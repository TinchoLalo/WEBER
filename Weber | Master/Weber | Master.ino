#include <IRremote.h> 
#include <IRremoteInt.h>


/*
  @Proyecto:    Robot Mini-Sumo
  @Autor:       Equipo Weber Bot
  @Placa:       Arduino NANO
  @Descripción: Código para robot minisumo, con sistema de detección infrarrojo y motores DC
*/

//========================== MODOS ========================== 

boolean Test    = false;      // Indica el modo pruebas del código
boolean Lucha   = !Test;     // Indica si el sumo ha sido activado para competir
boolean TestMotor = false;
boolean linea   = false;


//========================== REFERENCIAS ========================== 
int ref = 600;
int dis[] = {7,7,7,7,7}; // 0, 45, 90, 135, 180


//== ULTRASONICO
int disparo = 0;
int eco = 0;
long tiempoPulso;
float  dstMedida;

// ========================== SENSORES INFRAROJOS ==========================
int emisorIR       = 12;  // emisores infrarrojos controlados a través de transistor 2n2222a
//int emisorLinea    = 2;  // emisores infrarrojos sigue linas 
const int sensor0        = A4;  // Receptores IR
const int sensor45       = A6;  //
const int sensor90       = A5;  //
const int sensor135      = A3;  //
const int sensor180      = A1;  //
const int sensor270      = A0;  //

int valor0 = 0;  //inicializamos el valor que va a corresonder con la lectura de los sensores
int valor45 = 0;
int valor90 = 0;
int valor135 = 0;
int valor180 = 0;
int valor270 = 0;

// ========================== SENSORES SIGUE LINEAS  ==========================
int sensorA  = A2;
int sensorB  = A7;

int valorA   = 0;
int valorB   = 0;

// ========================== MOTORES ==========================================
int motorR1        = 10;  // Pin Motor Derecha Adelante
int motorR2        = 9;   // Pin Motor Derecha Atras
int motorL1        = 11;   // Pin Motor Izquierda Adelante
int motorL2        = 6;   // Pin Motor Izquierda Atras

// velocidades del motor
int max = 255; 
int mid = 125;


int R1 = mid;
int R2 = mid;
int L1 = mid;
int L2 = mid;

// ========================== LEDS INDICADORES ==================================
int ledTest        = 13;  // Led indicador encendido
int ledR           = 4;   // Led indicador Ready, semaforo
int ledG           = 7;  // Led indicador LUCHA!
int ledB           = 8;  // Led indicador otros

/*
int botonA       = 6;   // Pin de activación
int botonModo    = 2;
//int botonReset = ;
*/



//========================= BUZZER PARLANTE =========================//
/*
int bGND = 2;
int buzzer = 3;
*/

//== ULTRASONICO
int disp = 2;
int eco = 3;
long tPulso;
float  dstMedida;

//  ========================= CONTROL REMOTO =========================//
int receptorIR = 5;
IRrecv receptorIr(receptorIR);
decode_results codigoLeido;



//========================= START =========================//

void setup() {
  Serial.begin(9600);
  Serial.println("Weber Bot iniciando..."); //
  
  receptorIr.enableIRIn();

  //configuración de los pines de entrada y salida
  
  pinMode(ledTest, OUTPUT);
  pinMode(emisorIR, OUTPUT);
  pinMode(eco, INPUT);
<<<<<<< HEAD
  pinMode(disp, OUTPUT);
  digitalWrite(disp, LOW);
=======
  pinMode(disparo, OUTPUT);
  digitalWrite(disparo, LOW);
>>>>>>> 7d8953545bb72b8a8e4e50b1e0207b97150d9372

  //pinMode(emisorLinea, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);  
 // pinMode(ledB, OUTPUT);
  //pinMode(bGND, OUTPUT);
  

  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
  //digitalWrite(bGND, HIGH);
  //analogWrite(Buzzer, 150);

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
    delay(100);
    digitalWrite(ledTest, LOW);
    delay(100);      
  }  

  /*
  tone(buzzer, 1000, 1000);
  */
}

//========================= UPDATE =========================//
void loop(){
 
  if(Lucha) {
    //Serial.println("<<< MODO LUCHA >>>");
  
    if (receptorIr.decode(&codigoLeido)) { 
      Serial.println(codigoLeido.value, HEX);

      switch (codigoLeido.value) {
        case 0xAF4060ED:
          for(int i=0; i<5; i++){
            digitalWrite(ledR, LOW);
            delay(500);
            digitalWrite(ledR, HIGH);
            delay(500);      
          }  
<<<<<<< HEAD
          /*default: // modo default por si acaba la pila del control
=======
        /*default: // modo default por si acaba la pila del control
>>>>>>> 7d8953545bb72b8a8e4e50b1e0207b97150d9372
            for(int i=0; i<5; i++){
            digitalWrite(ledR, LOW);
            delay(500);
            digitalWrite(ledR, HIGH);
            delay(500);      
          }   */
          lucha(); 
          
<<<<<<< HEAD
        case 0x7B429C09:
          adelante();
          delay(50);
          stop();
          
          break;
        case 0xE8910B0D:
          atras();
          delay(50);
          stop();
             
          break;
        
        case 0x7BA58C69:
          adelanteL();
          delay(50);
          stop();
          
          break;
        case 0x63DD5653:
          adelanteR();
          delay(50);
          stop();
          
          break;

        /*case 0xCB0905A9:
          taladro();
          
          break;*/

        case 0xC98734CD:
          rotarL();
          delay(50);
          stop();
      
          break;
        
=======
        case 0xCB:
          adelante();
          delay(200);
          break;
        case 0xCB:
          atras();
          delay(200);   
          break;
        case 0xCB:
          taladro();
          break;
         case 0xCB:
          rotarL();
          delay(200);
          break;
         case 0xCB:
          rotaR();
          delay(200);
          break;
>>>>>>> 7d8953545bb72b8a8e4e50b1e0207b97150d9372
      }
    
      receptorIr.resume();
    }
  }//cierra el modo lucha

  else if (Test && !TestMotor) {
    Serial.println("<<< MODO TEST >>>");
    test();
  }

  else if (TestMotor){
    testMotor();
  }
  
  else {
    error();
    Serial.println("<<< ERROR: modo no seleccionado >>>");
  }


}//cierra el loop

/////////////////////////////////
//Programas !!

void lucha(){do {

  digitalWrite(ledG, LOW);
  valorA = analogRead(sensorA);  

  if(valorA<ref){

<<<<<<< HEAD
    digitalWrite(disp, LOW);
    delayMicroseconds(50);
    digitalWrite(disp, HIGH);
    delayMicroseconds(10); 
    digitalWrite(disp, LOW);
=======
    /*if(linea == true){
      rotarL();
      delay(300);
      stop();
      linea = false;
    }*/
    
   /* digitalWrite(disp, LOW);
       delayMicroseconds(50);
       digitalWrite(disp, HIGH);
       delayMicroseconds(10); 
       digitalWrite(disp, LOW);
  
  tPulso = pulseIn(eco, HIGH);

  if(tPulso>1200 && tPulso<6000){*/
>>>>>>> 7d8953545bb72b8a8e4e50b1e0207b97150d9372
  
    tPulso = pulseIn(eco, HIGH);

    valor0 = analogRead(sensor0);
    valor45 = analogRead(sensor45);
    valor90 = analogRead(sensor90);
    valor135 = analogRead(sensor135);
    valor180 = analogRead(sensor180);
    //valor270 = analogRead(sensor270);

    if(tPulso>10 && tPulso<3500){R1=255; L1=255;}
    else if(valor0>dis[0]){L1=200;R2=200;} //20
    else if(valor45>dis[1]){L1=200;R2=100;} // 50
    else if(valor135>dis[3]){R1=200;L2=100;} // 55
    else if(valor180>dis[4]){R1=200;L2=200;} //55

  }

  else if(valorA>ref){//toca la linea blanca
    
    analogWrite(motorR1, 0);
    analogWrite(motorR2, 255);
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 255);
    delay(170);
    analogWrite(motorR1, 255);
    analogWrite(motorR2, 0);
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 255);
    delay(200);

    //linea = true;
  }
  else {
  R1 = 100;
  R2 = 0;
  L1 = 0;
  L2 = 100;
  }

  //concluimos
  analogWrite(motorR1, R1);
  analogWrite(motorR2, R2);
  analogWrite(motorL1, L1);
  analogWrite(motorL2, L2);
  delay(100);
  


  //digitalWrite(ledR, HIGH)
  } while(true);
}




//funcion test(#)

void test() {
  digitalWrite(disp, LOW);
      delayMicroseconds(50);
      digitalWrite(disp, HIGH);
      delayMicroseconds(10); 
      digitalWrite(disp, LOW);
  
  tPulso = pulseIn(eco, HIGH);

  Serial.println(tPulso);

    valor0 = analogRead(sensor0);//40
    valor45 = analogRead(sensor45);//50
    valor90 = analogRead(sensor90);//50
    valor135 = analogRead(sensor135);//40
    valor180 = analogRead(sensor180);//60
    valorA = analogRead(sensorA);

    Serial.print(valor0);
    Serial.print(" - ");
    Serial.print(valor45);
    Serial.print(" - ");
    Serial.print(valor90);
    Serial.print(" - ");
    Serial.print(valor135);
    Serial.print(" - ");
    Serial.print(valor180);
    Serial.print(" - ");
    Serial.print(valorA);
    Serial.print(" - ");

    

  //tone(3, 2000);
  //noTone(3);

  //Prueba LEDs
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledR, LOW);

  //Prueba motores
  /*rotarR();
  delay(1000);
  rotarL();
  delay(1000);
  adelante();
  delay(1000);
  atras();
  delay(1000);
  stop();*/

}

void testMotor(){
  
  /*
  rotarR();
  delay(1000);
  rotarL();
  delay(1000);
  adelante();
  delay(1000);
  atras();
  delay(1000);
  stop();
  */
  taladro();
  //willy();

}

void error(){
  Serial.println("Error desconocido..");
  digitalWrite(ledTest, HIGH);
  //reset();
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

void adelanteR(){
  analogWrite(motorR1, 255); // motor derecho adelante
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 0);
}

void adelanteL(){
  analogWrite(motorR1, 0); // motor derecho adelante
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

//Funciones divertidas

void taladro(){

  for(int C=0; C<200; C++){
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledR, LOW);
  rotarR();
  delay(40);
  stop();
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);
  digitalWrite(ledR, HIGH);
  rotarL();
  delay(40);
  }
}

void willy(){

  for(int C=0; C<10; C++){
  analogWrite(motorR1, 0);
  analogWrite(motorR2, 255);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 255);
  delay(500);
  analogWrite(motorR1, 255);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 255);
  analogWrite(motorL2, 0);
  delay(500);
  }
}
