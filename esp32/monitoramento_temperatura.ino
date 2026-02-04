#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// config vai ficar em secrets.h
#include "secrets.h"

// DS18B20
const int ONE_WIRE_BUS = 4;     // alterar aqui se for usar outro GPIO
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LED
const int LED_PIN = 2;          // o led está onboard
const float LIMITE_TEMP = 30.0; // aqui altera a temperatura limite

// para os testes usar: 60000 (1 minuto)
// para uso real usar: 3600000 (1 hora)
const unsigned long INTERVALO_MS = 60000; // altera aqui a temp

unsigned long ultimoEnvio = 0;

void conectarWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Conectando no Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

bool enviarParaPlanilha(float tempC, int ledLigado) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi desconectado. Reconectando...");
    conectarWiFi();
  }

  String url = String(SHEETS_URL) +
               "?temp=" + String(tempC, 2) +
               "&led=" + String(ledLigado);

  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.print("Sheets respondeu: ");
    Serial.println(payload);
    http.end();
    return true;
  }

  Serial.print("Erro HTTP: ");
  Serial.println(httpCode);
  http.end();
  return false;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  sensors.begin();
  conectarWiFi();

  Serial.println("Projeto: Monitoramento de temperatura (ESP32 + DS18B20)");
  Serial.println("Status: em construção / testes");
}

void loop() {
  unsigned long agora = millis();

  if (agora - ultimoEnvio >= INTERVALO_MS) {
    ultimoEnvio = agora;

    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);

    if (tempC == DEVICE_DISCONNECTED_C) {
      Serial.println("Erro: DS18B20 não detectado (verifique ligação e resistor 4.7k).");
      return;
    }

    int ledLigado = (tempC >= LIMITE_TEMP) ? 1 : 0;
    digitalWrite(LED_PIN, ledLigado ? HIGH : LOW);

    Serial.print("Temp: ");
    Serial.print(tempC);
    Serial.print(" C | LED: ");
    Serial.println(ledLigado ? "LIGADO" : "DESLIGADO");

    enviarParaPlanilha(tempC, ledLigado);
  }

  delay(50);
}
