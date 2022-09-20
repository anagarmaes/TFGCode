#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include "EmonLib.h"

// Variables conexión WiFi
#define WIFI_NETWORK "Redmi Note 9"
#define WIFI_PASSWORD "b84eeb0eb3aa"

#define pinV 39
#define pinI 35
#define vCalibration 210
#define iCalibration 4.4 // caso 1 (P1 = 1150 W)
#define phase_shift 1

/*
  #define iCalibration 8.8
  #define iCalibration 13.2
  #define iCalibration 14.08
*/

float realPower, apparentPower, Vrms, Irms, PowerFactor, kWmin;
float actualTime, diffTime;
float kWmin; //kW en un minuto

// Necesario cuando la señal contiene componentes armónica
double THD12 = 50;
double fp12 = 1 / sqrt(1 + pow((THD12 / 100), 2)); // PF = powerFactor =  emon1.powerFactor*fp12
double THD123 = 51.5388;
double fp123 = 1 / sqrt(1 + pow((THD123 / 100), 2)); // PF = powerFactor =  emon1.powerFactor*fp12

//Variables Emoncms
IPAddress server(109, 169, 55, 159);
String apikey = "a946c2b86c727bffee87ce3d4449af3e"; //APIKey lectura y escritura
int port = 80;

HTTPClient http;
WiFiClient client;

EnergyMonitor emon1;

void setup()
{
  Serial.begin(115200);

  // Conexión WiFi
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  emon1.voltage(pinV, vCalibration, phase_shift);  // Voltage: input pin, calibration, phase_shift
  emon1.current(pinI, iCalibration);       // Current: input pin, calibration.
}

void loop() {
  int cont = 0;
  float sumP = 0;
  float sumS = 0;
  float sumVrms = 0;
  float sumIrms = 0;
  float sumPF = 0;
  diffTime = 0;
  float timeMin = millis();

  while (diffTime <= 10000) { // 1 min
    emon1.calcVI(20, 2000);
    float realPower = emon1.realPower;
    sumP += realPower;
    float apparentPower = emon1.apparentPower;
    sumS += apparentPower;
    float Vrms = emon1.Vrms;
    sumVrms += Vrms;
    float Irms = emon1.Irms;
    sumIrms += Irms;
    float powerFactor =  emon1.powerFactor;
    sumPF += powerFactor;
    diffTime = millis() - timeMin; // contabilizar el tiempo
    cont++;
  }

  kWmin = kWmin + (sumS / cont) * (diffTime) / 60000000; //kWmin, porque queremos 1 min y en kW

  // Envío de datos a Emoncms
  sendData(server, sumP / cont, sumS / cont, sumVrms / cont, sumIrms / cont, sumPF / cont, kWh);

  // Imprimir por pantalla
  Serial.print("Real Power: ");
  Serial.print(sumP / cont, 3);
  Serial.print(" W");
  Serial.print("\tApparent Power: ");
  Serial.print(sumS / cont, 3);
  Serial.print(" VA");
  Serial.print("\tVrms: ");
  Serial.print(sumVrms / cont, 3);
  Serial.print(" V");
  Serial.print("\tIrms: ");
  Serial.print(sumIrms / cont, 3);
  Serial.print(" A");
  Serial.print("\tPower Factor: ");
  Serial.print(sumPF / cont, 3);
  Serial.print("\tConsumo Electrico: ");
  Serial.print(kWh, 3);
  Serial.println("kWmin");
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
