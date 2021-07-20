#include "DHT.h"

// #define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321

DHT dht0(0, DHTTYPE);
DHT dht1(1, DHTTYPE);
DHT dht2(2, DHTTYPE);
DHT dht3(3, DHTTYPE);
DHT dht4(4, DHTTYPE);

// analog input for the LM35 DZ Sensor
float reading; // store the calculation of computReadLm function
// int[] tabPin = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

void setup()
{
  Serial.begin(115200);

  // Initialize DHT
  dht0.begin();
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
}

void loop()
{
  String resultTotal = "{";
  resultTotal += "\"lm35\":";
  resultTotal += readLM();
  resultTotal += ",";
  //delay(1000);
  resultTotal += "\"dht\":";
  resultTotal += readDHT();
  resultTotal += "}";
  Serial.println(resultTotal);
  //Serial.println("Hello");
  delay(3000);
}

String computeReadOfLm(int pin)
{
  float xVal = analogRead(pin);
  reading = (xVal * 500.0) / 1024;
  //return String(reading,2);
  return String(reading ,2);
}

String readLM()
{
  String result = "";
  result += "{";

  result += "\"Tv1\":\"" + computeReadOfLm(0) + "\",";
  result += "\"Tv2\":\"" + computeReadOfLm(1) + "\",";
  result += "\"Tv3\":\"" + computeReadOfLm(2) + "\",";
  result += "\"Tv4\":\"" + computeReadOfLm(3) + "\",";
  result += "\"Tv5\":\"" + computeReadOfLm(4) + "\",";

  result += "\"Tab1\":\"" + computeReadOfLm(5) + "\",";
  result += "\"Tab2\":\"" + computeReadOfLm(6) + "\",";
  result += "\"Tab3\":\"" + computeReadOfLm(7) + "\",";
  result += "\"Tab4\":\"" + computeReadOfLm(8) + "\",";
  result += "\"Tab5\":\"" + computeReadOfLm(9) + "\",";

  result += "\"Te1\":\"" + computeReadOfLm(10) + "\",";
  result += "\"Te1\":\"" + computeReadOfLm(11) + "\",";
  result += "\"Te1\":\"" + computeReadOfLm(12) + "\",";

  result += "\"Ts1\":\"" + computeReadOfLm(13) + "\",";
  result += "\"Ts1\":\"" + computeReadOfLm(14) + "\",";
  result += "\"Ts1\":\"" + computeReadOfLm(15) + "\"";

  result += "}";

  return result;
}

String readDHT()
{
  // lecture de chaque dht
  float h0 = dht0.readHumidity();
  float h1 = dht1.readHumidity();
  float h2 = dht2.readHumidity();
  float h3 = dht3.readHumidity();
  float h4 = dht4.readHumidity();

  // verification de la lecture
  if (isnan(h0) && isnan(h1) && isnan(h2) && isnan(h3) && isnan(h4))
  {
    Serial.println("Erreur");
    //return "Erreur";
  }

  // building the string result
  String result = "";

  result += "{";

  result += "\"DHT0\":\"" + String(h0, 2) + "\",";
  result += "\"DHT1\":\"" + String(h1,2) + "\",";
  result += "\"DHT2\":\"" + String(h2,2) + "\",";
  result += "\"DHT3\":\"" + String(h3,2) + "\",";
  result += "\"DHT4\":\"" + String(h4,2) + "\"";

  result += "}";

  // return the result of the lecture
  return result;
  //return "{DHT0 : 12, DHT1 : 11}";
}
