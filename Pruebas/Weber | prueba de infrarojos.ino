// ===================== VARIABLES ====================          
const int emisor = 3;
const int receptor = A0;
/* 
const int sensor0        = A0;  
const int sensor45       = A1;  
const int sensor90       = A2;  
const int sensor135      = A3;  
const int sensor180      = A4;  
const int sensor270      = A5;

*/


void setup() {

    pinMode(receptor, INPUT); 
    pinMode(emisor, OUTPUT); 

}


void loop() {

    serial.begin(9600);
    Serial.println("Weber Bot iniciando..."); 

    digitalWrite(emisor, HIGH);
    valor = analogRead(receptor);
    serial.println(valor);
    delay(1000)
}