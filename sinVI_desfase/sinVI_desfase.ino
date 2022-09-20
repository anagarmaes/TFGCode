int v_out = D0;
int i_out = D7;

int f = 50;
int ns = 40;
unsigned long sampling_interval, t_actual;

float samples_v[40] = {512, 592, 670, 744, 812, 873, 925, 967,
                       998, 1017, 1023, 1017, 998, 967, 925, 873,
                       812, 744, 670, 592, 512, 431, 353, 279,
                       211, 150, 98, 56, 25, 6, 0, 6,
                       25, 56, 98, 150, 211, 279, 353, 431
                      };

float samples_i[40] = {812, 873, 925, 967, 998, 1017, 1023, 1017,
                       998, 967, 925, 873, 812, 744, 670, 592,
                       512, 431, 353, 279, 211, 150, 98, 56,
                       25, 6, 0, 6, 25, 56, 98,150,
                       211, 279, 353, 431, 512, 592, 670, 744
                      };


void setup() {
  Serial.begin(115200);
  analogWriteRange(1023); //10 bits
  analogWriteFreq(40000); //maxima frecuencia a la que puede ir el PWM
  sampling_interval = (unsigned long) 1000000 / (f * ns);
  t_actual = micros();
}

void loop() {
  for (int i = 0; i < ns; i++) {
    analogWrite(v_out, samples_v[i]);
    analogWrite(i_out, samples_i[i]);
    delayMicroseconds(sampling_interval  - (micros() - t_actual));
    t_actual = micros();
  }
}
