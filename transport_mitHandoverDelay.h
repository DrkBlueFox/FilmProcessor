// transport.h
// Steuerung des Leadereinzug und Filmtransports

#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <Arduino.h>
#include "display.h"
#include "sd_log.h"
#include "errors.h"

#define LEADER_STEPS 3000  // Anzahl der Schritte für Leadereinzug (konfigurierbar)
#define BATH_STEPS 2500    // Schritte pro Bad (konfigurierbar)
#define CUTTER_PIN 13      // Pin für Linearantrieb (Schneidmechanik)
#define HANDOVER_DELAY 500 // ms Pause zwischen Bädern zur Entlastung des Leaders

// Maschinenstatus
enum MachineState {
  STATE_IDLE,
  STATE_EINZUG,
  STATE_DEV,
  STATE_FIX,
  STATE_WASH,
  STATE_DRY,
  STATE_DONE,
  STATE_ERROR
};

MachineState machineState = STATE_IDLE;

// Motorsteuerung aktivieren (falls über Enable-Pin)
void enableTransportMotors() {
  // z. B. digitalWrite(ENABLE_PIN, LOW);
}

// Schneidvorgang auslösen
void activateCutMechanism() {
  logEvent("Schnittvorgang wird ausgeführt");
  digitalWrite(CUTTER_PIN, HIGH);
  delay(800);  // Dauer der Schneidbewegung
  digitalWrite(CUTTER_PIN, LOW);
}

// Bewegung eines Abschnitts (z. B. Entwickler, Fixierer, etc.) mit Übergabepause
void moveFilmThroughPhase(const String &phaseName, MachineState nextState) {
  logEvent("Transport durch " + phaseName);
  setText("t0", "Phase: " + phaseName);

  for (int i = 0; i < BATH_STEPS; i++) {
    digitalWrite(STEPPER_DEV_STEP, HIGH);
    delayMicroseconds(800);
    digitalWrite(STEPPER_DEV_STEP, LOW);
    delayMicroseconds(800);
  }

  delay(HANDOVER_DELAY); // Warten vor Motorstart des nächsten Bads

  machineState = nextState;
}

// Leadereinzug starten
void startFilmEinzug() {
  logEvent("Leadereinzug gestartet");
  setText("t0", "Leader wird eingezogen...");
  machineState = STATE_EINZUG;
  enableTransportMotors();

  for (int i = 0; i < LEADER_STEPS; i++) {
    digitalWrite(STEPPER_DEV_STEP, HIGH);
    delayMicroseconds(800);
    digitalWrite(STEPPER_DEV_STEP, LOW);
    delayMicroseconds(800);
  }

  activateCutMechanism();
  logEvent("Leader wurde abgeschnitten");
  machineState = STATE_DEV;
  setText("t0", "Phase: Entwickler");
}

// Haupttransportablauf
void runFilmProcess() {
  if (machineState == STATE_DEV) {
    moveFilmThroughPhase("Entwickler", STATE_FIX);
  } else if (machineState == STATE_FIX) {
    moveFilmThroughPhase("Fixierer", STATE_WASH);
  } else if (machineState == STATE_WASH) {
    moveFilmThroughPhase("Wäscher", STATE_DRY);
  } else if (machineState == STATE_DRY) {
    moveFilmThroughPhase("Trockner", STATE_DONE);
  } else if (machineState == STATE_DONE) {
    setText("t0", "Entwicklung abgeschlossen");
    logEvent("Prozess beendet");
  }
}

#endif // TRANSPORT_H
