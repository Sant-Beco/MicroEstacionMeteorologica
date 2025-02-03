#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
#include <BH1750.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Credenciales de tu red WiFi
const char* ssid = "*****************"; /* Nombre de la red WIFI */
const char* password = "*****************"; /* Contraseña de red WIFI */

// Configuración de ThingSpeak
const char* server = "http://api.thingspeak.com";
String apiKey = "*****************"; /* Write API Key del chanel de thinkspeak */

// Definición del sensor BMP180
Adafruit_BMP085 bmp;

// Definición del sensor DHT22
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Instancia del sensor BH1750
BH1750 lightMeter;

// Pin para el LED
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando sensores...");

  pinMode(ledPin, OUTPUT);  // Configura el LED como salida
  Wire.begin(18, 19);       // SDA en GPIO18, SCL en GPIO19

  if (!bmp.begin()) {
    Serial.println("Error: Sensor BMP180 no detectado.");
  }

  dht.begin();

  if (lightMeter.begin()) {
    Serial.println("BH1750 inicializado correctamente.");
  } else {
    Serial.println("Error: Sensor BH1750 no detectado.");
  }

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(ledPin, HIGH);  // Enciende el LED mientras se conecta a WiFi
    delay(500);
    digitalWrite(ledPin, LOW);   // Apaga el LED para simular parpadeo
    Serial.print(".");
  }
  Serial.println("\n¡Conexión WiFi establecida!");
  digitalWrite(ledPin, HIGH);  // Mantén el LED encendido cuando se haya conectado exitosamente
}

void loop() {
  float presion = bmp.begin() ? bmp.readPressure() : NAN;
  float humedad = dht.readHumidity();
  float temperaturaDHT = dht.readTemperature();
  float lux = lightMeter.begin() ? lightMeter.readLightLevel() : NAN;

  Serial.println("Lecturas de los sensores:");
  if (!isnan(presion)) {
    Serial.print("Presión: ");
    Serial.print(presion);
    Serial.println(" Pa");
  } else {
    Serial.println("Error al leer presión.");
  }

  if (!isnan(humedad)) {
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");
  } else {
    Serial.println("Error al leer humedad.");
  }

  if (!isnan(temperaturaDHT)) {
    Serial.print("Temperatura (DHT22): ");
    Serial.print(temperaturaDHT);
    Serial.println(" °C");
  } else {
    Serial.println("Error al leer temperatura.");
  }

  if (!isnan(lux)) {
    Serial.print("Intensidad de luz: ");
    Serial.print(lux);
    Serial.println(" lx");
  } else {
    Serial.println("Error al leer intensidad de luz.");
  }
  Serial.println();

  // Si el ESP32 ya está conectado a Wi-Fi, desconectar antes de realizar el envío
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Desconectando de Wi-Fi...");
    WiFi.disconnect();  // Desconectar Wi-Fi
    delay(1000);        // Esperar un poco antes de continuar
  }

  // Conectar nuevamente a Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(ledPin, HIGH);  // Enciende el LED mientras se conecta
    delay(500);
    digitalWrite(ledPin, LOW);   // Apaga el LED
    Serial.print(".");
  }
  Serial.println("\n¡Conexión WiFi establecida!");

  // Ahora enviar los datos a ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = server;
    url += "/update?api_key=" + apiKey;

    if (!isnan(temperaturaDHT)) url += "&field1=" + String(temperaturaDHT);
    if (!isnan(humedad)) url += "&field2=" + String(humedad);
    if (!isnan(lux)) url += "&field3=" + String(lux);
    if (!isnan(presion)) url += "&field4=" + String(presion);

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("Datos enviados a ThingSpeak correctamente.");
      Serial.println("Respuesta HTTP: " + String(httpResponseCode));
    } else {
      Serial.println("Error al enviar datos: " + http.errorToString(httpResponseCode));
    }

    http.end();
  }

  // Desconectar después de enviar los datos
  WiFi.disconnect();
  Serial.println("Desconectado de Wi-Fi.");

  // Espera 5 minutos antes de la siguiente lectura
  delay(300000);  // 5 minutos

  // Parpadeo del LED (indica que el programa sigue corriendo)
  digitalWrite(ledPin, HIGH);  // Enciende el LED
  delay(500);                  // Espera 500ms
  digitalWrite(ledPin, LOW);   // Apaga el LED
  delay(500);                  // Espera 500ms
}
