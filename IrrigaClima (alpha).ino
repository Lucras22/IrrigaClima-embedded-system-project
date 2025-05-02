/*
██╗     ██╗   ██╗ ██████╗ ██████╗  █████╗ ███████╗
██║     ██║   ██║██╔═════╗██╔══██╗██╔══██╗██╔════╝
██║     ██║   ██║██║     ║██████╔╝███████║███████╗
██║     ██║   ██║██║     ║██╔══██╗██╔══██║╚════██║
███████╗╚██████╔╝╚██████╔╝██║  ██║██║  ██║███████║
╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝
-----------------------------------------------------------
📌 Autor: Lucas Galindo
🔗 GitHub: https://github.com/Lucras22
📧 E-mail: devlucasgalindo@email.com
💼 LinkedIn: https://www.linkedin.com/in/lucasgalindoiot/
-----------------------------------------------------------
📜 Instruções de Uso:
- 
-----------------------------------------------------------
📂 Repositório do Projeto:
🔗 https://github.com/Lucras22/IrrigaClima
-----------------------------------------------------------
🛠️ Licença: ....
*/


/* Fluxo do que o codigo faz:

Conectar ao Wi-Fi:
Conecta ao Wi-Fi com as credenciais fornecidas.

Inicializar os Sensores:
BME280 (Temperatura, Pressão, Umidade)
Sensor de Chuva
Sensor de Umidade do Solo
Sensor UV (GUVA)
MQ135 (Qualidade do Ar)

Loop Principal:
Ler dados dos sensores.
Exibir dados no monitor serial.

Controlar relé de irrigação:
Se solo > 60% (Desativa irrigação)
Se solo < 20% (Irrigação imediata)
Se chovendo (Desativa irrigação)
Caso contrário (Lógica de irrigação).
Montar mensagem com dados.
Enviar mensagem para Telegram.
Aguardar 10 segundos.

Lógica de Irrigação:
Dia (LDR < 2000): 15 min ligado, 15 min desligado.
Noite (LDR > 2000): 15 min ligado, 1 hora desligado.

Envio de Mensagens:
Envia mensagem a cada 15 minutos.
   
*/

// incluindo bibliotecas
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// definindo os nomes dos pinos
#define RAIN_SENSOR_PIN 34
#define SOIL_MOISTURE_PIN 32
#define UV_SENSOR_PIN 25
#define LDR_SENSOR_PIN 33
#define MQ135_SENSOR_PIN 35
#define RELAY_PIN 27

// token e id do bot do Telegram
const String botToken = "7216059515:AAEDxW2u7SX1LDhAnxY75iOgoUomGTyzTCU";
const String chatId = "7003158288";

// Nome e Senha do WiFi
const char* ssid = "Lucas Galindo | Poco C65"; 
const char* password = "lucras22"; 

// Configuração do sensor BME280
Adafruit_BME280 bme;
unsigned long previousMillis = 0;
unsigned long irrigationInterval = 15 * 60 * 1000; // 15 minutos por padrão

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("WiFi conectado");

  bool status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(UV_SENSOR_PIN, INPUT);
  pinMode(LDR_SENSOR_PIN, INPUT);
  pinMode(MQ135_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 
}

void loop() {
  unsigned long currentMillis = millis();

  int rainSensorValue = digitalRead(RAIN_SENSOR_PIN);
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  int uvAnalog = analogRead(UV_SENSOR_PIN);
  int ldrValue = analogRead(LDR_SENSOR_PIN);
  int mq135Value = analogRead(MQ135_SENSOR_PIN);

  float soilMoisturePercentage = map(soilMoistureValue, 0, 4095, 0, 100);
  bool isRaining = (rainSensorValue == LOW);

  int uvIndex = uvAnalog / 20;

  bool isDay = ldrValue < 2000;
  bool isNight = ldrValue >= 2000;

  if (isNight) {
    irrigationInterval = 60 * 60 * 1000;
  } else {
    irrigationInterval = 15 * 60 * 1000;
  }

  String irrigationStatus = "";

  if (soilMoisturePercentage > 60) {
    digitalWrite(RELAY_PIN, LOW);
    irrigationStatus = "Solo úmido - Irrigação desativada";
  } else if (isRaining) {
    digitalWrite(RELAY_PIN, LOW);
    irrigationStatus = "Chuva detectada - Irrigação desativada";
  } else if (soilMoisturePercentage < 20) {
    digitalWrite(RELAY_PIN, HIGH);
    irrigationStatus = "Solo muito seco - Irrigação imediata";
  } else if (currentMillis - previousMillis >= irrigationInterval) {
    digitalWrite(RELAY_PIN, HIGH);
    previousMillis = currentMillis;
    irrigationStatus = isNight ? "Modo Noturno: Irrigação a cada 1h" : "Modo Diurno: Irrigação a cada 15min";
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  Serial.printf("Chuva: %s\n", isRaining ? "Chuva detectada" : "Não está chovendo");
  Serial.printf("Umidade do Solo: %.2f%%\n", soilMoisturePercentage);
  Serial.printf("Índice UV: %d\n", uvIndex);
  Serial.printf("LDR (Luminosidade): %d\n", ldrValue);
  Serial.printf("MQ-135 (Qualidade do Ar): %d\n", mq135Value);
  Serial.println(irrigationStatus);

  Serial.printf("Temperatura = %.2f °C\n", bme.readTemperature());
  Serial.printf("Pressão = %.2f hPa\n", bme.readPressure() / 100.0F);
  Serial.printf("Altitude = %.2f m\n", bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.printf("Umidade = %.2f %%\n\n", bme.readHumidity());

  String message = "Dados IrrigaClima:\n\n";
  message += isRaining ? "Chuva: Chuva detectada\n" : "Chuva: Não está chovendo\n";
  message += "Umidade do Solo: " + String(soilMoisturePercentage) + "%\n";
  message += "Índice UV: " + String(uvIndex) + "\n";
  message += "Luminosidade: " + String(ldrValue) + "\n";
  message += "Qualidade do Ar (MQ-135): " + String(mq135Value) + "\n";
  message += "Temperatura: " + String(bme.readTemperature()) + " °C\n";
  message += "Pressão: " + String(bme.readPressure() / 100.0F) + " hPa\n";
  message += "Altitude: " + String(bme.readAltitude(SEALEVELPRESSURE_HPA)) + " m\n";
  message += "Umidade: " + String(bme.readHumidity()) + " %\n\n";
  message += irrigationStatus + "\n";

  sendMessage(message);
  delay(10000);
}

void sendMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + botToken + "/sendMessage";

    http.begin(url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String postData = "chat_id=" + chatId + "&text=" + message;
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Código de resposta: " + String(httpResponseCode));
      Serial.println("Resposta: " + response);
    } else {
      Serial.print("Erro na requisição: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }
}
