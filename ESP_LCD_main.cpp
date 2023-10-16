#include "Botao.h"
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32WebServer.h>
#include <WiFi.h>
#include <HTTPClient.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool alarmeAtivo = false;

int horaDespertador = 23;
int minutoDespertador = 0;
int pinBotaoX = 12;

const char* ssid = "Luciano"; // internet //
const char* password = "yuji2106";  // senha da internet //

bool teste = false;
bool config = false;

const char* serverName = "http://10.0.0.101:80/postpath";  // ip do esp client //
Botao botoes (16, 17, 18, lcd, teste);

int ponteiroPosicao = 0;  // 0 = horas dezena, 1 = horas unidade, 2 = minutos dezena, 3 = minutos unidade
int valores[4] = {0, 0, 0, 0};

void setup() {
  
  pinMode(pinBotaoX, INPUT_PULLUP);
  Wire.begin();
  rtc.begin();

  Serial.begin(115200);
if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

lcd.init();
lcd.backlight();
lcd.clear();

  // Conectar-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi!");

  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    int httpCode = http.POST("key=value"); // POST data

    if(httpCode > 0) {
        // Verificar o código de resposta HTTP
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    } else {
        Serial.printf("Erro na requisição HTTP: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}
void enviar_req (){
if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    int httpCode = http.POST("key=value"); // POST data

    if(httpCode > 0) {
        // Verificar o código de resposta HTTP
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    } else {
        Serial.printf("Erro na requisição HTTP: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}
//... (Restante do código antes do loop)

void loop() {
    // Checar se o botãoX foi pressionado
    if (digitalRead(pinBotaoX) == LOW) { // LOW quando o botão é pressionado
        delay(200);  // debounce
        config = !config;  // Alternar entre os modos
        Serial.println("Modo de Configuração");
    }

    if (config) {
        // Modo de configuração
        botoes.checarBotoes();
        botoes.getHorario(horaDespertador, minutoDespertador);
    } else {
        // Modo normal (exibir relógio)
        DateTime now = rtc.now();

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Hora: ");
        lcd.print(now.hour(), DEC);
        lcd.print(":");
        lcd.print(now.minute(), DEC);
        lcd.print(":");
        lcd.print(now.second(), DEC);

        lcd.setCursor(0, 1);
        lcd.print("Data: ");
        lcd.print(now.day(), DEC);
        lcd.print("/");
        lcd.print(now.month(), DEC);
        lcd.print("/");
        lcd.print(now.year(), DEC);

        if (!alarmeAtivo && now.hour() == horaDespertador && now.minute() == minutoDespertador) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ALARME!");
            enviar_req();
            delay(10000);
            alarmeAtivo = true;
        }

        delay(1000);
    }
}
