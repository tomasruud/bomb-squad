#include <TFT.h>
#include <SPI.h>

#define TFT_CS 10
#define TFT_RST 8
#define TFT_DC 9

#define X_PIN A0
#define Y_PIN A2

TFT screen = TFT(TFT_CS, TFT_DC, TFT_RST);

#define SAMPLE_SIZE 20

int x_samples[SAMPLE_SIZE];
int x_average = 0;
int x_total = 0;

int y_samples[SAMPLE_SIZE];
int y_average = 0;
int y_total = 0;

int read_index = 0;

void setup() {
  Serial.begin(9600);

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  screen.begin();
}

void loop() {
  x_total -= x_samples[read_index];
  y_total -= y_samples[read_index];

  x_samples[read_index] = analogRead(X_PIN);
  y_samples[read_index] = analogRead(Y_PIN);

  x_total += x_samples[read_index];
  y_total += y_samples[read_index];

  read_index++;

  if(read_index >= SAMPLE_SIZE)
    read_index = 0;

  x_average = x_total / SAMPLE_SIZE;
  y_average = y_total / SAMPLE_SIZE;

  Serial.print("[X: ");
  Serial.print(x_average);
  Serial.print(", Y: ");
  Serial.print(y_average);
  Serial.print("]\n");

  delay(1);
}
