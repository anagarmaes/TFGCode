#include "EmonLib.h"

#define pinV 39
#define pinI 35
#define vCalibration 210
#define iCalibration 4.4 // caso 1 (P1 = 1150 W)
#define phase_shift 1

/*
 #define iCalibration 8.8 // caso 2 (P2 = 2300 W)
 #define iCalibration // caso 3 (P3 = 3450 W)
 #define iCalibration // caso 4 (P4 = 4600 W)
 */

float realPower, apparentPower, Vrms, Irms, PowerFactor;
float actualTime, diffTime;

EnergyMonitor emon1;

void setup()
{
  Serial.begin(115200);

  emon1.voltage(pinV, vCalibration, phase_shift);  // Voltage: input pin, calibration, phase_shift
  emon1.current(pinI, iCalibration);       // Current: input pin, calibration.
}

void loop() {
  int cont = 0;
  // decalaracion sumatorios
  float sumP = 0;
  float sumS = 0;
  float sumVrms = 0;
  float sumIrms = 0;
  float sumPF = 0;
  diffTime = 0;
  float timeMin = millis();

  while (diffTime <= 60000) { // 1 min
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
  Serial.println(sumPF / cont, 3);

}
