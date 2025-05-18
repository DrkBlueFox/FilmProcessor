// agitation.h
// Zeitgesteuerte Agitation für alle Prozessbäder (z. B. Rührmotor oder Magnetrührer)

#ifndef AGITATION_H
#define AGITATION_H

#include <Arduino.h>

// GPIOs für Agitation pro Bad
#define AGITATE_PIN_DEV 30
#define AGITATE_PIN_FIX 31
#define AGITATE_PIN_WASH 32

// Agitationseinstellungen (ms)
#define AGITATE_INTERVAL 30000
#define AGITATE_DURATION 5000

unsigned long lastAgitationDev = 0;
unsigned long lastAgitationFix = 0;
unsigned long lastAgitationWash = 0;

void initAgitation() {
  pinMode(AGITATE_PIN_DEV, OUTPUT);
  digitalWrite(AGITATE_PIN_DEV, LOW);
  pinMode(AGITATE_PIN_FIX, OUTPUT);
  digitalWrite(AGITATE_PIN_FIX, LOW);
  pinMode(AGITATE_PIN_WASH, OUTPUT);
  digitalWrite(AGITATE_PIN_WASH, LOW);

  lastAgitationDev = millis();
  lastAgitationFix = millis();
  lastAgitationWash = millis();
}

void updateAgitation() {
  unsigned long now = millis();

  if (now - lastAgitationDev >= AGITATE_INTERVAL) {
    digitalWrite(AGITATE_PIN_DEV, HIGH);
    delay(AGITATE_DURATION);
    digitalWrite(AGITATE_PIN_DEV, LOW);
    lastAgitationDev = millis();
  }

  if (now - lastAgitationFix >= AGITATE_INTERVAL) {
    digitalWrite(AGITATE_PIN_FIX, HIGH);
    delay(AGITATE_DURATION);
    digitalWrite(AGITATE_PIN_FIX, LOW);
    lastAgitationFix = millis();
  }

  if (now - lastAgitationWash >= AGITATE_INTERVAL) {
    digitalWrite(AGITATE_PIN_WASH, HIGH);
    delay(AGITATE_DURATION);
    digitalWrite(AGITATE_PIN_WASH, LOW);
    lastAgitationWash = millis();
  }
}

#endif // AGITATION_H

