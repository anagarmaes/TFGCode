#include <EmonLib.h>
#include <WiFi.h>

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0 //en este núcleo se controla la wifi
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// Variables conexión WiFi
#define WIFI_NETWORK "Redmi Note 9"
#define WIFI_PASSWORD "************"
#define WIFI_TIMEOUT_MS 10000 // 10 second WiFi connection timeout
#define WIFI_RECOVER_TIME_MS 30000 // Wait 30 seconds after a failed connection attempt


#define pinV 39
#define pinI 35
#define vCalibration 214
#define iCalibration 4.4
#define phase_shift 1

EnergyMonitor emon1; //creamos instancia Energy Monitor

unsigned long lastmillis = millis();

void setup() {
  Serial.begin(115200);

  //Inicializamos la libreria EmonLib
  emon1.voltage(pinV, vCalibration, phase_shift);  // Voltage: input pin, calibration, phase_shift
  emon1.current(pinI, iCalibration);       // Current: input pin, calibration.

  //TASK1: Conexión Wifi
  xTaskCreatePinnedToCore(
    keepWiFiAlive,
    "keep WiFi Alive",  // Task name
    3072,               // Stack size (bytes)
    NULL,               // Parameter
    1,                  // Task priority
    NULL,               // Task handle
    0                   // ARDUINO_RUNNING_CORE
  );

  //TASK 2: Calcular parámetros EmonLib
  xTaskCreatePinnedToCore(
    emonLibParameters,
    "emonLibParameters", // Task name
    1024,                // Stack size (bytes)
    NULL,                // Parameter
    1,                   // Task priority
    NULL,                // Task handle
    1                    // ARDUINO_RUNNING_CORE
  );
}

void keepWiFiAlive(void * pvParameters) {
  for (;;) {
    Serial.print("WiFi: Core --> ");
    Serial.println(xPortGetCoreID());
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi still connected");
      vTaskDelay(10000 / portTICK_PERIOD_MS); //10 segundos
      continue;
    }

    Serial.println("WiFi Connecting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

    unsigned long startAttemptTime = millis();

    // Keep looping while we're not connected and haven't reached the timeout
    while (WiFi.status() != WL_CONNECTED &&
           millis() - startAttemptTime < WIFI_TIMEOUT_MS) {}

    // When we couldn't make a WiFi connection (or the timeout expired)
    // sleep for a while and then retry.
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi FAILED");
      vTaskDelay(WIFI_RECOVER_TIME_MS / portTICK_PERIOD_MS);
      continue;
    }
    Serial.print("WiFi Connected: ");
    Serial.println(WiFi.localIP());
  }
}

void emonLibParameters(void * pvParameters) {
  for (;;) {
    int cont = 0;
    float sumP = 0;
    float sumS = 0;
    float sumVrms = 0;
    float sumIrms = 0;
    float sumPF = 0;
    float diffTime = 0;
    Serial.print("Emonlib: Core --> ");
    Serial.println(xPortGetCoreID());
    float timeMin = millis();

    while (diffTime < 10000) { //10 s
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
      diffTime = millis() - timeMin;
      cont++;
    }
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
    Serial.println(sumPF / cont, 3);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
