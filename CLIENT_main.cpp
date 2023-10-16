#include <WiFi.h>
#include <ESP32WebServer.h>

const char* ssid = "Luciano";
const char* password = "yuji2106";
const int pinAlimentacao = 23;

ESP32WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_STA); // Configuração para o modo estação (station mode)
  WiFi.begin(ssid, password);
  pinMode(pinAlimentacao, OUTPUT);

  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    server.on("/postpath", HTTP_POST, []() {
      digitalWrite(pinAlimentacao, HIGH);
      Serial.println("Received POST request!");
      server.send(200, "text/plain", "POST request received");
      delay(5000);
      digitalWrite(pinAlimentacao, LOW);
    });

    server.begin();
    Serial.println("Server started. Send a POST request to /postpath");
  } else {
    Serial.println("WiFi Failed");
  }
}

void loop(void) {
  server.handleClient();
  delay(1);
}
