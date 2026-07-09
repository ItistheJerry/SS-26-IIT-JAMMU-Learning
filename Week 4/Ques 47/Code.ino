#define SIMULATE_WITH_LDR

#ifdef SIMULATE_WITH_LDR
  #define LDR_PIN 34
#else
  #include <Wire.h>
  #include "MAX30105.h"
  #include "heartRate.h"
  MAX30105 particleSensor;
#endif

#define ALERT_LED_PIN 25

float hrSamples[5]  = {0};
float spo2Samples[5] = {0};
int   sampleIdx     = 0;
int   sampleCount   = 0;

void addSample(float hr, float spo2) {

  hrSamples[sampleIdx]   = hr;
  spo2Samples[sampleIdx] = spo2;
  sampleIdx = (sampleIdx + 1) % 5;
  if (sampleCount < 5) sampleCount++;

}

float avgHR() {

  float sum = 0;
  for (int i = 0; i < sampleCount; i++) sum += hrSamples[i];
  return sum / sampleCount;

}

float avgSpO2() {

  float sum = 0;
  for (int i = 0; i < sampleCount; i++) sum += spo2Samples[i];
  return sum / sampleCount;

}

#ifdef SIMULATE_WITH_LDR
void getSimulatedReadings(float &hr, float &spo2) {

  int ldrRaw = analogRead(LDR_PIN);

  hr   = map(ldrRaw, 0, 4095, 100, 40);
  spo2 = map(ldrRaw, 0, 4095, 99, 88);

  hr   += random(-2, 3);
  spo2 += random(-1, 2);

  hr   = constrain(hr,   30, 200);
  spo2 = constrain(spo2, 80, 100);

}
#endif

bool isAlert(float hr, float spo2) {

  return (hr < 50 || hr > 120 || spo2 < 94);

}

void setup() {

  Serial.begin(115200);
  pinMode(ALERT_LED_PIN, OUTPUT);
  digitalWrite(ALERT_LED_PIN, LOW);

#ifdef SIMULATE_WITH_LDR
  Serial.println("[MODE] LDR Simulation Mode");
  Serial.println("Move the LDR slider in Wokwi to simulate different readings.");
#else
  Wire.begin();
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {

    Serial.println("[ERROR] MAX30102 not found! Check wiring.");
    while (1);

  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
  Serial.println("[MODE] MAX30102 Real Sensor Mode");
#endif

  Serial.println("\nTimestamp(ms), HR(bpm), SpO2(%), Status");

}

unsigned long lastRead = 0;

void loop() {

  if (millis() - lastRead < 2000) return;
  lastRead = millis();

  float rawHR, rawSpO2;

#ifdef SIMULATE_WITH_LDR
  getSimulatedReadings(rawHR, rawSpO2);
#else
  long irValue = particleSensor.getIR();
  if (irValue < 50000) {

    Serial.println("No finger detected. Place finger on sensor.");
    return;

  }
  rawHR   = 75;
  rawSpO2 = 98;
#endif

  addSample(rawHR, rawSpO2);
  float smoothHR   = avgHR();
  float smoothSpO2 = avgSpO2();

  bool alert = isAlert(smoothHR, smoothSpO2);

  digitalWrite(ALERT_LED_PIN, alert ? HIGH : LOW);

  String status;
  if (alert) {

    if (smoothHR < 50)       status = "BRADYCARDIA";
    else if (smoothHR > 120) status = "TACHYCARDIA";
    else                     status = "LOW SPO2";
  } else {

    status = "NORMAL";

  }

  Serial.printf("%lu, %.0f, %.0f, %s\n",
                millis(), smoothHR, smoothSpO2, status.c_str());

  Serial.println("-----------------------------");
  Serial.printf("  Heart Rate : %.0f bpm\n", smoothHR);
  Serial.printf("  SpO2       : %.0f %%\n",  smoothSpO2);
  Serial.printf("  Status     : %s\n",        status.c_str());
  if (alert) Serial.println("  ALERT! Red LED ON");
  Serial.println("-----------------------------");

}
