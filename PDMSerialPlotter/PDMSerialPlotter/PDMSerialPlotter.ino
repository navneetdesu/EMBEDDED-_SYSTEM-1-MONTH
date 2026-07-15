#include <PDM.h>

#define LED_PIN LED_BUILTIN

short sampleBuffer[256];
volatile int samplesRead = 0;

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  PDM.onReceive(onPDMdata);

  if (!PDM.begin(1, 16000)) {
    Serial.println("Microphone failed!");
    while (1);
  }

  PDM.setGain(30);

  Serial.println("===== Voice Detection Started =====");
}

void loop() {

  if (samplesRead > 0) {

    long sum = 0;

    for (int i = 0; i < samplesRead; i++) {
      sum += abs(sampleBuffer[i]);
    }

    int level = sum / samplesRead;

    Serial.print("Sound Level: ");
    Serial.println(level);

    if (level < 250) {

      Serial.println("SILENT");
      digitalWrite(LED_PIN, LOW);

    }
    else if (level < 700) {

      Serial.println("LOW VOICE");

      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);

    }
    else if (level < 1500) {

      Serial.println("VOICE DETECTED!");

      digitalWrite(LED_PIN, HIGH);
      delay(300);
      digitalWrite(LED_PIN, LOW);

    }
    else {

      Serial.println("LOUD SOUND!");

      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
      }
    }

    Serial.println("------------------------");

    samplesRead = 0;
  }
}