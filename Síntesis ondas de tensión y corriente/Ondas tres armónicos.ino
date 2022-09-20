int v_out = D0;
int i_out = D7;

float t;
unsigned long sampling_interval;
unsigned long t_actual;

int f = 50;
int samples_v[40];
int ns = 40; //numero de muestras
int fs =  ns; //f de muestreo

int samples[40], samples_f0[40], samples_f1[40], samples_f2[40]; //para 3 armónicos

void setup() {
  analogWriteRange(1023);
  analogWriteFreq(40000);

  for (int i = 0; i < ns; i++) {
    t = (float)i / fs;
    samples_f0[i] = (int)(256 * sin(2 * PI * t) + 256);
    samples_f1[i] = (int)(128 * sin(2 * PI * 2 * t) + 128);
    samples_f2[i] = (int)(64 * sin(2 * PI * 3 * t) + 64);
    samples[i] = samples_f0[i] + samples_f1[i] + samples_f2[i];

    samples_v[i] = (int)(512 * sin(2 * PI * t) + 512);
  }

  sampling_interval = (unsigned long) 1000000 / (f * ns);
  t_actual = micros();
}

void loop() {
  for (int j = 0; j < ns; j++) {
    analogWrite(v_out, samples_v[j]);
    analogWrite(i_out, samples[j]);
    delayMicroseconds(sampling_interval - (micros() - t_actual));
    t_actual = micros();
  }
}
