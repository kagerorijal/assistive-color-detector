#include <Wire.h>
#include "Adafruit_TCS34725.h"

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X
);

struct ColorData {
  float h, s, v;
  float lux;
  float temp;
  const char* label;
};

ColorData dataset[] = {
  {46, 0.38, 0.40, 46, 3651, "Hitam Sulfur"},
  {1, 0.81, 0.83, 0, 0, "Merah Cabe"},
  {25, 0.36, 0.47, 55, 3750, "Navy"},
  {43, 0.44, 0.42, 1195, 3315, "Putih Bersih"},
  {47, 0.44, 0.41, 1456, 3344, "Putih Netral"},
  {76, 0.60, 0.45, 938, 3309, "Hijau Pupus"},
  {132, 0.51, 0.50, 281, 5170, "Hijau Fuji"},
  {156, 0.60, 0.47, 471, 7324, "Tosca"},
  {61, 0.30, 0.41, 92, 4133, "Hijau Botol"},
  {30, 0.56, 0.51, 121, 2552, "Hijau Army"},
  {39, 0.69, 0.49, 1235, 2395, "Kuning Kenari"},
  {22, 0.75, 0.59, 411, 1677, "Kuning Kunyit"},
  {21, 0.78, 0.60, 554, 1631, "Kuning Emas"},
  {17, 0.46, 0.47, 406, 2785, "Lilac"},
  {8, 0.83, 0.73, 15, 5414, "Orange Sunkist"},
  {41, 0.40, 0.42, 636, 3544, "Abu Muda"},
  {24, 0.52, 0.51, 78, 2623, "Abu Tua"},
  {138, 0.37, 0.43, 888, 6033, "Turkish Muda"},
  {174, 0.62, 0.44, 369, 11374, "Turkish Tua"},
  {202, 0.27, 0.42, 119, 18620, "Biru Benhur"},
  {20, 0.54, 0.49, 656, 2368, "Baby Pink"},
  {4, 0.75, 0.73, 0, 0, "Merah Maroon"},
  {359, 0.78, 0.78, 0, 25327, "Pink Fanta"},
  {8, 0.45, 0.52, 47, 2529, "Ungu Tua"},
  {21, 0.34, 0.43, 331, 3975, "Lavender"},
  {32, 0.57, 0.47, 692, 2577, "Beige"},
  {21, 0.57, 0.55, 70, 2236, "Coklat Kopi"},
  {1, 0.68, 0.69, 0, 8249, "Magenta"},
  {23, 0.51, 0.54, 38, 2658, "Hitam Reaktif"},
  {22, 0.50, 0.54, 39, 2697, "Jet Black"}

  /*{73, 0.32, 0.38, 54, 4219, "Hitam Sulfur"},
  {8, 0.68, 0.62, 19, 2708, "Merah Cabe"},
  {68, 0.29, 0.38, 55, 4314, "Navy"},
  {40, 0.45, 0.42, 278, 3239, "Putih Bersih"},
  {40, 0.46, 0.42, 297, 3191, "Putih Netral"},
  {70, 0.52, 0.42, 200, 3389, "Hijau Pupus"},
  {105, 0.36, 0.43, 92, 4709, "Hijau Fuji"},
  {139, 0.40, 0.43, 121, 5987, "Tosca"},
  {74, 0.32, 0.39, 60, 4267, "Hijau Botol"},
  {48, 0.39, 0.40, 66, 3602, "Hijau Army"},
  {37, 0.66, 0.48, 284, 2410, "Kuning Kenari"},
  {23, 0.67, 0.54, 104, 1897, "Kuning Kunyit"},
  {21, 0.73, 0.57, 127, 1684, "Kuning Emas"},
  {21, 0.46, 0.46, 109, 2916, "Lilac"},
  {11, 0.76, 0.64, 37, 2881, "Orange Sunkist"},
  {40, 0.40, 0.42, 155, 3505, "Abu Muda"},
  {49, 0.37, 0.40, 62, 3723, "Abu Tua"},
  {123, 0.28, 0.41, 218, 5507, "Turkish Muda"},
  {155, 0.41, 0.42, 116, 7511, "Turkish Tua"},
  {116, 0.14, 0.38, 67, 6327, "Biru Benhur"},
  {20, 0.54, 0.49, 148, 2348, "Baby Pink"},
  {15, 0.59, 0.53, 39, 1879, "Merah Maroon"},
  {5, 0.68, 0.62, 10, 5050, "Pink Fanta"},
  {43, 0.33, 0.40, 53, 3982, "Ungu Tua"},
  {29, 0.35, 0.42, 100, 3811, "Lavender"},
  {31, 0.55, 0.47, 170, 2667, "Beige"},
  {48, 0.37, 0.40, 58, 3706, "Coklat Kopi"},
  {19, 0.50, 0.49, 42, 2520, "Magenta"},
  {65, 0.31, 0.38, 52, 4130, "Hitam Reaktif"},
  {62, 0.31, 0.38, 54, 4069, "Jet Black"},*/
};

const int dataCount = sizeof(dataset) / sizeof(dataset[0]);
const int k = 1;

float minH = 1, maxH = 156;
float minS = 0.36, maxS = 0.81;
float minV = 0.40, maxV = 0.83;
float minLux = 0, maxLux = 1456;
float minTemp = 0, maxTemp = 7324;

float weightH = 0.5;
float weightS = 0.3;
float weightV = 0.2;
float weightLux = 0.0;
float weightTemp = 0.0;

SoftwareSerial mySerial(11, 10);
DFRobotDFPlayerMini myDFPlayer;

int tombolPin = 2;
bool tombolSudahDitekan = false;

void setup() {
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("TCS34725 detected.");
  } else {
    Serial.println("TCS34725 not found. Check wiring.");
    //while (1);
  }

  mySerial.begin(9600);
  
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("Gagal komunikasi dengan DFPlayer.");
    //while (true);
  }

  Serial.println("DFPlayer siap!");
  myDFPlayer.volume(30);

  pinMode(tombolPin, INPUT_PULLUP);
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (c == 0) c = 1;

  float r_scaled = ((float)r / c) * 255.0;
  float g_scaled = ((float)g / c) * 255.0;
  float b_scaled = ((float)b / c) * 255.0;

  r_scaled = constrain(r_scaled, 0, 255);
  g_scaled = constrain(g_scaled, 0, 255);
  b_scaled = constrain(b_scaled, 0, 255);

  float h, s, v;
  rgbToHsv(r_scaled, g_scaled, b_scaled, &h, &s, &v);

  float lux = tcs.calculateLux(r, g, b);
  float temp = tcs.calculateColorTemperature(r, g, b);

  float nh = (h - minH) / (maxH - minH);
  float ns = (s - minS) / (maxS - minS);
  float nv = (v - minV) / (maxV - minV);
  float nlux = (lux - minLux) / (maxLux - minLux);
  float ntemp = (temp - minTemp) / (maxTemp - minTemp);

  float distances[dataCount];
  for (int i = 0; i < dataCount; i++) {
    float dh = (nh - (dataset[i].h - minH) / (maxH - minH));
    float ds = (ns - (dataset[i].s - minS) / (maxS - minS));
    float dv = (nv - (dataset[i].v - minV) / (maxV - minV));
    float dlux = (nlux - (dataset[i].lux - minLux) / (maxLux - minLux));
    float dtemp = (ntemp - (dataset[i].temp - minTemp) / (maxTemp - minTemp));

    float dist = sqrt(
      weightH * dh * dh +
      weightS * ds * ds +
      weightV * dv * dv +
      weightLux * dlux * dlux +
      weightTemp * dtemp * dtemp
    );

    distances[i] = dist;
  }

  int indices[k];
  for (int i = 0; i < k; i++) indices[i] = i;
  for (int i = k; i < dataCount; i++) {
    int maxIdx = 0;
    for (int j = 1; j < k; j++) {
      if (distances[indices[j]] > distances[indices[maxIdx]]) maxIdx = j;
    }
    if (distances[i] < distances[indices[maxIdx]]) {
      indices[maxIdx] = i;
    }
  }

  int voteCount[dataCount] = {0};
  for (int i = 0; i < k; i++) {
    voteCount[indices[i]]++;
  }

  int maxVotes = 0;
  int bestIndex = indices[0];
  for (int i = 0; i < k; i++) {
    if (voteCount[indices[i]] > maxVotes) {
      maxVotes = voteCount[indices[i]];
      bestIndex = indices[i];
    }
  }

  if (digitalRead(tombolPin) == LOW && !tombolSudahDitekan) {
    tombolSudahDitekan = true;
    myDFPlayer.play(bestIndex + 1);
    Serial.print("Deteksi warna: ");
    Serial.print(dataset[bestIndex].label);
    //Serial.print(bestIndex);
    Serial.print(" | H: "); Serial.print((int)h);
    Serial.print(" S: "); Serial.print((int)(s * 100));
    Serial.print(" V: "); Serial.print((int)(v * 100));
    Serial.print(" | Lux: "); Serial.print((int)lux);
    Serial.print(" | Temp: "); Serial.println((int)temp);
    delay(1000);
  } 
  
  /*Serial.print(" | H: "); Serial.print((int)h);
  Serial.print(" S: "); Serial.print((int)(s * 100));
  Serial.print(" V: "); Serial.print((int)(v * 100));
  Serial.print(" | Lux: "); Serial.print((int)lux);
  Serial.print(" | Temp: "); Serial.println((int)temp);
  delay(1000);*/
  
  if (digitalRead(tombolPin) == HIGH && tombolSudahDitekan) {
    tombolSudahDitekan = false;
  }
}

void rgbToHsv(float r, float g, float b, float *h, float *s, float *v) {
  r /= 255.0; g /= 255.0; b /= 255.0;
  float maxVal = max(r, max(g, b));
  float minVal = min(r, min(g, b));
  float delta = maxVal - minVal;

  if (delta == 0) {
    *h = 0;
  } else if (maxVal == r) {
    *h = 60 * fmod(((g - b) / delta), 6);
  } else if (maxVal == g) {
    *h = 60 * (((b - r) / delta) + 2);
  } else {
    *h = 60 * (((r - g) / delta) + 4);
  }
  if (*h < 0) *h += 360;
  *s = (maxVal == 0) ? 0 : delta / maxVal;
  *v = maxVal;
}