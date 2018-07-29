//Sensor de temperatura / Humedad DHT11
//Sensor de Presion BMP280
//Sensor de luminosidad ldr Gl55

#include <Adafruit_Sensor.h>
#include "Adafruit_BMP280.h"
#include "DHT.h"

Adafruit_BMP280 bmp; // I2C

#define DHTTYPE DHT11   // DHT 11
const int DHTPin = 5;     // what digital pin we're connected to

DHT dht(DHTPin, DHTTYPE);

const int LDRPin = A0;
const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ

float presion; // Almacena la presion atmosferica (Pa)
float temperatura; // Almacena la temperatura (oC)
int altitud; // Almacena la altitud (m) (se puede usar variable float)

float dht11_humedad;
float dht11_temperatura;

int luminosidad;
int iluminacion;


void setup() {

  bmp.begin(); // Inicia el sensor
  dht.begin();
  pinMode(LDRPin, INPUT);

  Serial.begin(9600); // Inicia comunicacion serie
  Serial.println("BMP280 Sensor de Presion y Temperatura");


}


void loop() {

  delay(2000);

  luminosidad = analogRead(LDRPin);
  //iluminacion = ((long)(1024-luminosidad)*A*10)/((long)B*Rc*luminosidad));  //usar si LDR entre GND y A0 
  iluminacion = ((long)luminosidad*A*10)/((long)B*Rc*(1024-luminosidad));    //usar si LDR entre A0 y Vcc (como en el esquema anterior)
  
  // Imprime valores por el serial monitor:
  Serial.print("Iluminacion: ");
  Serial.print(luminosidad);
  Serial.print("\tIndice: ");
  Serial.println(iluminacion);
  

  // Lee valores del sensor:
  presion = bmp.readPressure() / 100;
  temperatura = bmp.readTemperature();
  altitud = bmp.readAltitude() + 48; // Ajustar con el valor local

  // leer valores sensor dht11
  dht11_humedad = dht.readHumidity();
  dht11_temperatura = dht.readTemperature();

  // Imprime valores por el serial monitor:
  Serial.print(F("Presion: "));
  Serial.print(presion);
  Serial.print(" hPa");
  Serial.print("\t");
  Serial.print(("Temp: "));
  Serial.print(temperatura);
  Serial.print(" *C");
  Serial.print("\t");
  Serial.print("Altitud (aprox): ");
  Serial.print(altitud);
  Serial.println(" m");

  if (isnan(dht11_humedad) || isnan(dht11_temperatura)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Hum: ");
  Serial.print(dht11_humedad);
  Serial.print(" %\t");
  Serial.print("Temp: ");
  Serial.print(dht11_temperatura);
  Serial.println(" *C ");

}
