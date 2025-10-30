// Codigo Robotiks Robolympics Noviembre 2023 ROBOT 1 Y 2
  // Arduino Nano (Old bootloader)
  // Revisar en que 
  // Pines para sensores de linea REVISAR ORDEN 
#define SENSOR_LINEA_DER      A0
#define SENSOR_LINEA_IZQ      A1
  // Pines para sensores de oponente, por modificar
#define SENSOR_OPONENTE_DER   0
#define SENSOR_OPONENTE_MED   1
#define SENSOR_OPONENTE_IZQ   2
  // Pines de controlador motores AZUL!!!!!!!!!
#define MOTOR_PWMB    11
#define MOTOR_BIN2    9
#define MOTOR_BIN1    10
#define MOTOR_STBY    12
#define MOTOR_AIN1    8
#define MOTOR_AIN2    7
#define MOTOR_PWMA    6
  // Pines extra
#define ARRANCADOR    8

  // Valores sensores de linea
#define VALOR_SENSOR_LINEA_DER  250
#define VALOR_SENSOR_LINEA_IZQ  200
  

   // Valores tiempo motores
#define TIEMPO_ATRAS  150
#define TIEMPO_GIRO  100


  // Variables
int var_sensor_linea_der = 0;
int var_sensor_linea_izq = 0;
int var_sensor_oponente_der = 0;
int var_sensor_oponente_med = 0;
int var_sensor_oponente_izq = 0;
int var_arrancador = 0;
int i =1;

int sharpDistance(int sensor) {
  int limiteInferior = 80;
  int limiteSuperior = 500;
  float data = analogRead(sensor);
  float distance = 0;

  if (data >= limiteInferior && data <= limiteSuperior) {
    for (int i = 0; i < 20; i++) {
      distance = distance + analogRead(sensor);
    }
    distance = 4800 / (data - 20);
  } else {
    if (data < limiteInferior) {
      distance = 80;
    } else if (data > limiteSuperior) {
      distance = 4;
    }
  }
  //delay(100);
  return distance;
}

void leerSensores(void) {
  var_sensor_linea_der = analogRead(SENSOR_LINEA_DER);
  var_sensor_linea_izq = analogRead(SENSOR_LINEA_IZQ);
  var_sensor_oponente_der = sharpDistance(SENSOR_OPONENTE_DER);
  var_sensor_oponente_med = sharpDistance(SENSOR_OPONENTE_MED);
  var_sensor_oponente_izq = sharpDistance(SENSOR_OPONENTE_IZQ);
}

void imprimirValoresSensores(void) {
  Serial.print("Linea Der: ");
  Serial.print(var_sensor_linea_der);
  Serial.print("  ");
  Serial.print("Linea Izq: ");
  Serial.print(var_sensor_linea_izq);
  Serial.print("  ");
  Serial.print("Oponente Der: ");
  Serial.print(var_sensor_oponente_der);
  Serial.print("  ");
  Serial.print("Oponente Med: ");
  Serial.print(var_sensor_oponente_med);
  Serial.print("  ");
  Serial.print("Oponente Izq: ");
  Serial.print(var_sensor_oponente_izq);
  Serial.print("  ");
  Serial.println(""); 
}

void motoresAdelante(void) {
    // Activar driver
  digitalWrite(MOTOR_STBY, HIGH);
    // Motor A, DERECHO
  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);
  analogWrite(MOTOR_PWMA, 235);
    // Motor B, IZQUIERDO
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);
  analogWrite(MOTOR_PWMB, 235);
}

void motoresAdelanteLento(void) {
    // Activar driver
  digitalWrite(MOTOR_STBY, HIGH);
    // Motor A, DERECHO
  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);
  analogWrite(MOTOR_PWMA, 100);
    // Motor B, IZQUIERDO
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);
  analogWrite(MOTOR_PWMB, 100);
}

void motoresAtras(void) {
    // Activar driver
  digitalWrite(MOTOR_STBY, HIGH);
    // Motor A, DERECHO
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, HIGH);
  analogWrite(MOTOR_PWMA, 150);
    // Motor B, IZQUIERDO
  digitalWrite(MOTOR_BIN1, HIGH);
  digitalWrite(MOTOR_BIN2, LOW);
  analogWrite(MOTOR_PWMB, 150);
}

void motoresGiroIzquierda(void) {
    // Activar driver
  digitalWrite(MOTOR_STBY, HIGH);
    // Motor A, DERECHO
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, HIGH);
  analogWrite(MOTOR_PWMA, 200);     // Velocidad 0 - 255
    // Motor B, IZQUIERDO
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);
  analogWrite(MOTOR_PWMB, 200);
}

void motoresGiroDerecha(void) {
    // Activar driver
  digitalWrite(MOTOR_STBY, HIGH);
    // Motor A, DERECHO
  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);
  analogWrite(MOTOR_PWMA, 200);
    // Motor B, IZQUIERDO
  digitalWrite(MOTOR_BIN1, HIGH);
  digitalWrite(MOTOR_BIN2, LOW);
  analogWrite(MOTOR_PWMB, 200);
}

void motoresFreno(void) {
    // Activar driver
  digitalWrite(MOTOR_STBY, HIGH);
    // Motor A
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, LOW);
  analogWrite(MOTOR_PWMA, 0);
    // Motor B
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, LOW);
  analogWrite(MOTOR_PWMB, 0);
}

void probarMotores(void) {
  motoresAdelante();
  delay(1000);
  motoresFreno();
  delay(1000);
  motoresAtras();
  delay(1000);
  motoresFreno();
  delay(1000);
  motoresGiroDerecha();
  delay(1000);
  motoresFreno();
  delay(1000);
  motoresGiroIzquierda();
  delay(1000);
  motoresFreno();
  delay(1000);
}

void setup() {
  Serial.begin(9600);
    // Pines sensores de linea, Entradas
  pinMode(SENSOR_LINEA_DER, INPUT);
  pinMode(SENSOR_LINEA_IZQ, INPUT);
    // Pines sensores de oponente, Entradas
  pinMode(SENSOR_OPONENTE_DER, INPUT);
  pinMode(SENSOR_OPONENTE_MED, INPUT);
  pinMode(SENSOR_OPONENTE_IZQ, INPUT);
    // Pines controlador motores, Salidas
  pinMode(MOTOR_PWMB, OUTPUT);
  pinMode(MOTOR_BIN2, OUTPUT);
  pinMode(MOTOR_BIN1, OUTPUT);
  pinMode(MOTOR_STBY, OUTPUT);
  pinMode(MOTOR_AIN1, OUTPUT);
  pinMode(MOTOR_AIN2, OUTPUT);
  pinMode(MOTOR_PWMA, OUTPUT);
    // Pines extra
  pinMode(ARRANCADOR, INPUT);
}

void loop() {

  //PROGRAMA DE CALIBRACION!!!!!!!!
 //leerSensores();
  //imprimirValoresSensores();
  //delay(1000); 

//PROGRAMA DE COMPETENCIA!!!
  //var_arrancador = digitalRead(ARRANCADOR);
  //if ( var_arrancador == 1 ) {
    leerSensores();
    if ( var_sensor_linea_der > VALOR_SENSOR_LINEA_DER && var_sensor_linea_izq > VALOR_SENSOR_LINEA_IZQ ) {
      if ( var_sensor_oponente_med < 550 ) {
        motoresAdelante();
      } else if ( var_sensor_oponente_izq < 450 ) {
        motoresGiroIzquierda();
      } else if ( var_sensor_oponente_der < 450 ) {
        motoresGiroDerecha();
      } else {
        motoresAdelanteLento();
      }
    } else if ( var_sensor_linea_der < VALOR_SENSOR_LINEA_DER) {
      motoresFreno();
      motoresAtras();
      delay(TIEMPO_ATRAS);
      motoresGiroIzquierda();
      delay(TIEMPO_GIRO);    
    } 
    else if (var_sensor_linea_izq < VALOR_SENSOR_LINEA_IZQ ) {
      motoresFreno();
      motoresAtras();
      delay(TIEMPO_ATRAS);
      motoresGiroDerecha();
      delay(TIEMPO_GIRO);    
    } 
  }
    else {
      digitalWrite(MOTOR_STBY, HIGH);
    // Motor A
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, LOW);
  analogWrite(MOTOR_PWMA, 0);
    // Motor B
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, LOW);
  analogWrite(MOTOR_PWMB, 0);
 }
 
 //PROGRAMA PARA CHECAR MOTORES!!!!!
 //probarMotores();
 }