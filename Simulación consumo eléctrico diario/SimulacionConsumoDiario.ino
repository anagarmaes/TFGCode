#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include "EmonLib.h"

// Variables conexión WiFi
#define WIFI_NETWORK "Redmi Note 9"
#define WIFI_PASSWORD "b84eeb0eb3aa"

// Variables fijas de calibración
#define pinV 39
#define pinI 35
#define vCalibration 200
#define phase_shift 1

#define sendInterval 10000

float realPower, apparentPower, Vrms, Irms, PowerFactor, kWmin;
float diffTime;
int j = 0;
float sumP, sumS, sumVrms, sumIrms, sumPF, kWh;
float sumP1, sumS1, sumVrms1, sumIrms1, sumPF1, kWh1;
float sumP2, sumS2, sumVrms2, sumIrms2, sumPF2, kWh2;
float sumP3, sumS3, sumVrms3, sumIrms3, sumPF3, kWh3;
float sumP4, sumS4, sumVrms4, sumIrms4, sumPF4, kWh4;
float sumP6, sumS6, sumVrms6, sumIrms6, sumPF6, kWh6;
float sumP8, sumS8, sumVrms8, sumIrms8, sumPF8, kWh8;
float sumP9, sumS9, sumVrms9, sumIrms9, sumPF9, kWh9;
int cont;

//Variables Emoncms
IPAddress server(109, 169, 55, 159);
String apikey = "a946c2b86c727bffee87ce3d4449af3e";
const unsigned long postingInterval = 10 * 1000; // delay between updates, in milliseconds
int port = 80;

// Creación de instancias
HTTPClient http;
WiFiClient client;
EnergyMonitor emon1, emon2, emon3, emon4, emon5, emon6;
EnergyMonitor emon7, emon8, emon9, emon10, emon11, emon12;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // Instancias de cada periodo
  emon1.voltage(pinV, vCalibration, phase_shift);  // Voltage: input pin, calibration, phase_shift
  emon1.current(pinI, 0.65); // Current: input pin, calibration.
  emon2.voltage(pinV, vCalibration, phase_shift);
  emon2.current(pinI, 0.8);
  emon3.voltage(pinV, vCalibration, phase_shift);
  emon3.current(pinI, 0.4);
  emon4.voltage(pinV, vCalibration, phase_shift);
  emon4.current(pinI, 0.57);
  emon5.voltage(pinV, vCalibration, phase_shift);
  emon5.current(pinI, 1.65);
  emon6.voltage(pinV, vCalibration, phase_shift);
  emon6.current(pinI, 1.55);
  emon7.voltage(pinV, vCalibration, phase_shift);
  emon7.current(pinI, 0.3);
  emon8.voltage(pinV, vCalibration, phase_shift);
  emon8.current(pinI, 0.67);
  emon9.voltage(pinV, vCalibration, phase_shift);
  emon9.current(pinI, 0.90);
  emon10.voltage(pinV, vCalibration, phase_shift);
  emon10.current(pinI, 1.80);
  emon11.voltage(pinV, vCalibration, phase_shift);
  emon11.current(pinI, 2.7);
  emon12.voltage(pinV, vCalibration, phase_shift);
  emon12.current(pinI, 2.3);
}

void loop() {
  cont = 0;
  sumP1 = 0;
  sumS1 = 0;
  sumVrms1 = 0;
  sumIrms1 = 0;
  sumPF1 = 0;
  diffTime = 0;
  float timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon1.calcVI(20, 2000);
    float realPower = emon1.realPower;
    sumP1 += realPower;
    float apparentPower = emon1.apparentPower;
    sumS1 += apparentPower;
    float Vrms = emon1.Vrms;
    sumVrms1 += Vrms;
    float Irms = emon1.Irms;
    sumIrms1 += Irms;
    float powerFactor =  emon1.powerFactor;
    sumPF1 += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh1 = (sumS1 / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP1 / cont, sumS1 / cont, sumVrms1 / cont, sumIrms1 / cont, sumPF1 / cont, kWh1);
  serialprint(sumP1, sumS1, sumVrms1, sumIrms1, sumPF1, kWh1, cont);

  diffTime = 0;
  sumP2 = 0;
  sumS2 = 0;
  sumVrms2 = 0;
  sumIrms2 = 0;
  sumPF2 = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon2.calcVI(20, 2000);
    float realPower = emon2.realPower;
    sumP2 += realPower;
    float apparentPower = emon2.apparentPower;
    sumS2 += apparentPower;
    float Vrms = emon2.Vrms;
    sumVrms2 += Vrms;
    float Irms = emon2.Irms;
    sumIrms2 += Irms;
    float powerFactor =  emon2.powerFactor;
    sumPF2 += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh2 = (sumS2 / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP2 / cont, sumS2 / cont, sumVrms2 / cont, sumIrms2 / cont, sumPF2 / cont, kWh2);
  serialprint(sumP2, sumS2, sumVrms2, sumIrms2, sumPF2, kWh2, cont);

  diffTime = 0;
  sumP3 = 0;
  sumS3 = 0;
  sumVrms3 = 0;
  sumIrms3 = 0;
  sumPF3 = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon3.calcVI(20, 2000);
    float realPower = emon3.realPower;
    sumP3 += realPower;
    float apparentPower = emon3.apparentPower;
    sumS3 += apparentPower;
    float Vrms = emon3.Vrms;
    sumVrms3 += Vrms;
    float Irms = emon3.Irms;
    sumIrms3 += Irms;
    float powerFactor =  emon3.powerFactor;
    sumPF3 += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh3 = (sumS3 / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP3 / cont, sumS3 / cont, sumVrms3 / cont, sumIrms3 / cont, sumPF3 / cont, kWh3);
  serialprint(sumP3, sumS3, sumVrms3, sumIrms3, sumPF3, kWh3, cont);

  diffTime = 0;
  sumP4 = 0;
  sumS4 = 0;
  sumVrms4 = 0;
  sumIrms4 = 0;
  sumPF4 = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon4.calcVI(20, 2000);
    float realPower = emon4.realPower;
    sumP4 += realPower;
    float apparentPower = emon4.apparentPower;
    sumS4 += apparentPower;
    float Vrms = emon4.Vrms;
    sumVrms4 += Vrms;
    float Irms = emon4.Irms;
    sumIrms4 += Irms;
    float powerFactor =  emon4.powerFactor;
    sumPF4 += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh4 = (sumS4 / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP4 / cont, sumS4 / cont, sumVrms4 / cont, sumIrms4 / cont, sumPF4 / cont, kWh4);
  serialprint(sumP4, sumS4, sumVrms4, sumIrms4, sumPF4, kWh4, cont);

  delay(sendInterval);
  sendData(server, sumP2 / cont, sumS2 / cont, sumVrms2 / cont, sumIrms2 / cont, sumPF2 / cont, kWh2);
  serialprint(sumP2, sumS2, sumVrms2, sumIrms2, sumPF2, kWh2, cont);
  delay(sendInterval);
  sendData(server, sumP3 / cont, sumS3 / cont, sumVrms3 / cont, sumIrms3 / cont, sumPF3 / cont, kWh3);
  serialprint(sumP3, sumS3, sumVrms3, sumIrms3, sumPF3, kWh3, cont);
  delay(sendInterval);
  sendData(server, sumP4 / cont, sumS4 / cont, sumVrms4 / cont, sumIrms4 / cont, sumPF4 / cont, kWh4);
  serialprint(sumP4, sumS4, sumVrms4, sumIrms4, sumPF4, kWh4, cont);
  delay(sendInterval);
  sendData(server, sumP2 / cont, sumS2 / cont, sumVrms2 / cont, sumIrms2 / cont, sumPF2 / cont, kWh2);
  serialprint(sumP2, sumS2, sumVrms2, sumIrms2, sumPF2, kWh2, cont);
  delay(sendInterval);
  sendData(server, sumP3 / cont, sumS3 / cont, sumVrms3 / cont, sumIrms3 / cont, sumPF3 / cont, kWh3);
  serialprint(sumP3, sumS3, sumVrms3, sumIrms3, sumPF3, kWh3, cont);

  diffTime = 0;
  sumP = 0;
  sumS = 0;
  sumVrms = 0;
  sumIrms = 0;
  sumPF = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon5.calcVI(20, 2000);
    float realPower = emon5.realPower;
    sumP += realPower;
    float apparentPower = emon5.apparentPower;
    sumS += apparentPower;
    float Vrms = emon5.Vrms;
    sumVrms += Vrms;
    float Irms = emon5.Irms;
    sumIrms += Irms;
    float powerFactor =  emon5.powerFactor;
    sumPF += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh = (sumS / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP / cont, sumS / cont, sumVrms / cont, sumIrms / cont, sumPF / cont, kWh);
  serialprint(sumP, sumS, sumVrms, sumIrms, sumPF, kWh, cont);

  diffTime = 0;
  sumP6 = 0;
  sumS6 = 0;
  sumVrms6 = 0;
  sumIrms6 = 0;
  sumPF6 = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon6.calcVI(20, 2000);
    float realPower = emon6.realPower;
    sumP6 += realPower;
    float apparentPower = emon6.apparentPower;
    sumS6 += apparentPower;
    float Vrms = emon6.Vrms;
    sumVrms6 += Vrms;
    float Irms = emon6.Irms;
    sumIrms6 += Irms;
    float powerFactor =  emon6.powerFactor;
    sumPF6 += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh6 = (sumS6 / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP6 / cont, sumS6 / cont, sumVrms6 / cont, sumIrms6 / cont, sumPF6 / cont, kWh6);
  serialprint(sumP6, sumS6, sumVrms6, sumIrms6, sumPF6, kWh6, cont);

  diffTime = 0;
  sumP = 0;
  sumS = 0;
  sumVrms = 0;
  sumIrms = 0;
  sumPF = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon7.calcVI(20, 2000);
    float realPower = emon7.realPower;
    sumP += realPower;
    float apparentPower = emon7.apparentPower;
    sumS += apparentPower;
    float Vrms = emon7.Vrms;
    sumVrms += Vrms;
    float Irms = emon7.Irms;
    sumIrms += Irms;
    float powerFactor =  emon7.powerFactor;
    sumPF += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh = (sumS / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP / cont, sumS / cont, sumVrms / cont, sumIrms / cont, sumPF / cont, kWh);
  serialprint(sumP, sumS, sumVrms, sumIrms, sumPF, kWh, cont);

  delay(sendInterval);
  sendData(server, sumP1 / cont, sumS1 / cont, sumVrms1 / cont, sumIrms1 / cont, sumPF1 / cont, kWh1);
  serialprint(sumP1, sumS1, sumVrms1, sumIrms1, sumPF1, kWh1, cont);

  diffTime = 0;
  sumP8 = 0;
  sumS8 = 0;
  sumVrms8 = 0;
  sumIrms8 = 0;
  sumPF8 = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon8.calcVI(20, 2000);
    float realPower = emon8.realPower;
    sumP8 += realPower;
    float apparentPower = emon8.apparentPower;
    sumS8 += apparentPower;
    float Vrms = emon8.Vrms;
    sumVrms8 += Vrms;
    float Irms = emon8.Irms;
    sumIrms8 += Irms;
    float powerFactor =  emon8.powerFactor;
    sumPF8 += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh8 = (sumS8 / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP8 / cont, sumS8 / cont, sumVrms8 / cont, sumIrms8 / cont, sumPF8 / cont, kWh8);
  serialprint(sumP8, sumS8, sumVrms8, sumIrms8, sumPF8, kWh8, cont);

  diffTime = 0;
  sumP9 = 0;
  sumS9 = 0;
  sumVrms9 = 0;
  sumIrms9 = 0;
  sumPF9 = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon9.calcVI(20, 2000);
    float realPower = emon9.realPower;
    sumP9 += realPower;
    float apparentPower = emon9.apparentPower;
    sumS9 += apparentPower;
    float Vrms = emon9.Vrms;
    sumVrms9 += Vrms;
    float Irms = emon9.Irms;
    sumIrms9 += Irms;
    float powerFactor =  emon9.powerFactor;
    sumPF9 += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh9 = (sumS9 / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP9 / cont, sumS9 / cont, sumVrms9 / cont, sumIrms9 / cont, sumPF9 / cont, kWh9);
  serialprint(sumP9, sumS9, sumVrms9, sumIrms9, sumPF9, kWh9, cont);

  diffTime = 0;
  sumP = 0;
  sumS = 0;
  sumVrms = 0;
  sumIrms = 0;
  sumPF = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon10.calcVI(20, 2000);
    float realPower = emon10.realPower;
    sumP += realPower;
    float apparentPower = emon10.apparentPower;
    sumS += apparentPower;
    float Vrms = emon10.Vrms;
    sumVrms += Vrms;
    float Irms = emon10.Irms;
    sumIrms += Irms;
    float powerFactor =  emon10.powerFactor;
    sumPF += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh = (sumS / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP / cont, sumS / cont, sumVrms / cont, sumIrms / cont, sumPF / cont, kWh);
  serialprint(sumP, sumS, sumVrms, sumIrms, sumPF, kWh, cont);

  diffTime = 0;
  sumP = 0;
  sumS = 0;
  sumVrms = 0;
  sumIrms = 0;
  sumPF = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon11.calcVI(20, 2000);
    float realPower = emon11.realPower;
    sumP += realPower;
    float apparentPower = emon11.apparentPower;
    sumS += apparentPower;
    float Vrms = emon11.Vrms;
    sumVrms += Vrms;
    float Irms = emon11.Irms;
    sumIrms += Irms;
    float powerFactor =  emon11.powerFactor;
    sumPF += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh = (sumS / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP / cont, sumS / cont, sumVrms / cont, sumIrms / cont, sumPF / cont, kWh);
  serialprint(sumP, sumS, sumVrms, sumIrms, sumPF, kWh, cont);

  diffTime = 0;
  sumP = 0;
  sumS = 0;
  sumVrms = 0;
  sumIrms = 0;
  sumPF = 0;
  cont = 0;
  timeMin = millis();

  while (diffTime <= sendInterval) { // 1 min
    emon12.calcVI(20, 2000);
    float realPower = emon12.realPower;
    sumP += realPower;
    float apparentPower = emon12.apparentPower;
    sumS += apparentPower;
    float Vrms = emon12.Vrms;
    sumVrms += Vrms;
    float Irms = emon12.Irms;
    sumIrms += Irms;
    float powerFactor =  emon12.powerFactor;
    sumPF += powerFactor;
    diffTime = millis() - timeMin;
    cont++;
  }
  kWh = (sumS / cont) * (diffTime) / (sendInterval * 1000); // en realidad kWmin
  sendData(server, sumP / cont, sumS / cont, sumVrms / cont, sumIrms / cont, sumPF / cont, kWh);
  serialprint(sumP, sumS, sumVrms, sumIrms, sumPF, kWh, cont);

  delay(sendInterval);
  sendData(server, sumP6 / cont, sumS6 / cont, sumVrms6 / cont, sumIrms6 / cont, sumPF6 / cont, kWh6);
  serialprint(sumP6, sumS6, sumVrms6, sumIrms6, sumPF6, kWh6, cont);
  delay(sendInterval);
  sendData(server, sumP9 / cont, sumS9 / cont, sumVrms9 / cont, sumIrms9 / cont, sumPF9 / cont, kWh9);
  serialprint(sumP9, sumS9, sumVrms9, sumIrms9, sumPF9, kWh9, cont);
  delay(sendInterval);
  sendData(server, sumP3 / cont, sumS3 / cont, sumVrms3 / cont, sumIrms3 / cont, sumPF3 / cont, kWh3);
  serialprint(sumP3, sumS3, sumVrms3, sumIrms3, sumPF3, kWh3, cont);
  delay(sendInterval);
  sendData(server, sumP8 / cont, sumS8 / cont, sumVrms8 / cont, sumIrms8 / cont, sumPF8 / cont, kWh8);
  serialprint(sumP8, sumS8, sumVrms8, sumIrms8, sumPF8, kWh8, cont);
  delay(sendInterval);
  sendData(server, sumP2 / cont, sumS2 / cont, sumVrms2 / cont, sumIrms2 / cont, sumPF2 / cont, kWh2);
  serialprint(sumP2, sumS2, sumVrms2, sumIrms2, sumPF2, kWh2, cont);
  delay(sendInterval);
  sendData(server, sumP3 / cont, sumS3 / cont, sumVrms3 / cont, sumIrms3 / cont, sumPF3 / cont, kWh3);
  serialprint(sumP3, sumS3, sumVrms3, sumIrms3, sumPF3, kWh3, cont);
}

void sendData(IPAddress server, float rp, float ap, float v, float i, float pf, float e) {
  // if there's a successful connection:
  if (client.connect(server, port)) {
    Serial.println("Server listening...");
    String full_url = "http://109.169.55.159/input/post?node=mynode&json={\"realPower\":" + String(rp) + ",\"apparentPower\":" + String(ap) + ",\"Vrms\":" + String(v) + ",\"Irms\":" + String(i) + ",\"PF\":" + String(pf) + ",\"Energy\":" + String(e) + "}&apikey=" + apikey;
    http.begin(client, full_url);

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.print("Respuesta:");
      Serial.println(response);
    }
    http.end();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("Connection failed");
    Serial.println("Disconnecting...");
    client.stop();
  }
}

void serialprint(float rp, float ap, float v, float i, float pf, float e, int cont) {
  Serial.print("Real Power: ");
  Serial.print(rp / cont, 3);
  Serial.print(" W");
  Serial.print("\tApparent Power: ");
  Serial.print(ap / cont, 3);
  Serial.print(" VA");
  Serial.print("\tVrms: ");
  Serial.print(v / cont, 3);
  Serial.print(" V");
  Serial.print("\tIrms: ");
  Serial.print(i / cont, 3);
  Serial.print(" A");
  Serial.print("\tPower Factor: ");
  Serial.print(pf / cont, 3);
  Serial.print("\tConsumo Electrico: ");
  Serial.print(e, 3);
  Serial.println(" kWmin");
}
