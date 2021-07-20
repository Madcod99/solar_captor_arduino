#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "wifiarduino";
const char *password = "";
//const char* password = "arduinoWifi";

//Your Domain name with URL path or IP address with path
const char *serverName = "http://192.168.1.100:3000/";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

// const String espName = "esp1";
// int value;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop()
{
  if ((millis() - lastTime) > timerDelay)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      if (Serial.available() > 0)
      {
        HTTPClient http;
        http.begin(serverName);
        http.addHeader("Content-Type", "application/json");
        // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        String httpRequestData = "";
        String value = Serial.readStringUntil('\n');
        // httpRequestData += "&value=";
        httpRequestData += value;
        Serial.println(value);
        int httpResponseCode = http.POST(httpRequestData);
        http.end();
      }
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
