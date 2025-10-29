// --- Pines de sensores ---
#define SENSOR_LINEA_DER      A7
#define SENSOR_LINEA_IZQ      A6
#define SENSOR_OPONENTE_DER   7
#define SENSOR_OPONENTE_MED   8
#define SENSOR_OPONENTE_IZQ   10

// Variables
int var_sensor_linea_der = 0;
int var_sensor_linea_izq = 0;
int var_sensor_oponente_der = 0;
int var_sensor_oponente_med = 0;
int var_sensor_oponente_izq = 0;

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
  return distance;
}

void leerSensores(void) {
  var_sensor_linea_der = analogRead(SENSOR_LINEA_DER);
  var_sensor_linea_izq = analogRead(SENSOR_LINEA_IZQ);
  var_sensor_oponente_der = digitalRead(SENSOR_OPONENTE_DER);
  var_sensor_oponente_med = digitalRead(SENSOR_OPONENTE_MED);
  var_sensor_oponente_izq = digitalRead(SENSOR_OPONENTE_IZQ);
}

void imprimirValoresSensores(void) {
  Serial.print("Linea Der: ");
  Serial.print(var_sensor_linea_der);
  Serial.print(" | Linea Izq: ");
  Serial.print(var_sensor_linea_izq);
  Serial.print(" | Oponente Der: ");
  Serial.print(var_sensor_oponente_der);
  Serial.print(" | Oponente Med: ");
  Serial.print(var_sensor_oponente_med);
  Serial.print(" | Oponente Izq: ");
  Serial.print(var_sensor_oponente_izq);
  Serial.println();
}



void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando lectura de sensores y pines...");
}

void loop() {
  leerSensores();
  imprimirValoresSensores();

  Serial.println("------------------------");
  delay(1000); // 0.4 segundos entre lecturas
}
