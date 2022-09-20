int v_out = D0;
int i_out = D7;

float t;
unsigned long sampling_interval;
unsigned long t_actual;


int f = 50; //f fundamental
int ns = 40; //numero de muestras
int fs =  ns; //f de muestreo

int samples_i[40];
int samples_v[40];

void setup() {
  Serial.begin(115200);
  analogWriteRange(1023); //10 bits
  analogWriteFreq(40000); //maxima frecuencia a la que puede ir el PWM

  for (int i = 0; i < ns; i++) {
    t = (float)i / fs;
    samples_v[i] = (int)(512 * sin(2 * PI * t) + 512);
    samples_i[i] = (int)(512 * sin(2 * PI * t + PI/6) + 512);
  }
  sampling_interval = (unsigned long) 1000000 / (f * ns);
  t_actual = micros();
}

void loop() {
  for (int j = 0; j < ns; j++) {
    analogWrite(v_out, samples_v[j]);
    analogWrite(i_out, samples_i[j]);
    delayMicroseconds(sampling_interval  - (micros() - t_actual));
    t_actual = micros();
  }
}
