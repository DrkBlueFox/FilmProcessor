// sensors.h
// Sensorüberwachung für Filmentwicklungsmaschine

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "errors.h"
#include "sd_log.h"

// Sensor-Pin-Definitionen
#define SENSOR_DEV_IN    2
#define SENSOR_DEV_OUT   3
#define SENSOR_FIX_IN    4
#define SENSOR_FIX_OUT   5
#define SENSOR_WASH_IN   6
#define SENSOR_WASH_OUT  7
#define SENSOR_DRY_IN    8
#define SENSOR_DRY_OUT   9
#define SENSOR_FILM_INSERT 10

// Initialisierung der Sensoren
void initSensors() {
  pinMode(SENSOR_DEV_IN, INPUT);
  pinMode(SENSOR_DEV_OUT, INPUT);
  pinMode(SENSOR_FIX_IN, INPUT);
  pinMode(SENSOR_FIX_OUT, INPUT);
  pinMode(SENSOR_WASH_IN, INPUT);
  pinMode(SENSOR_WASH_OUT, INPUT);
  pinMode(SENSOR_DRY_IN, INPUT);
  pinMode(SENSOR_DRY_OUT, INPUT);
  pinMode(SENSOR_FILM_INSERT, INPUT_PULLUP);
}

// Film-Einführungssensor prüfen
bool isFilmInserted() {
  return digitalRead(SENSOR_FILM_INSERT) == LOW;
}

// Sensorstatus überprüfen
void checkSensors() {
  if (digitalRead(SENSOR_DEV_IN) == LOW) {
    setError(ERROR_SENSOR_DEV_MISSING);
    logEvent("Sensor Entwickler-Eingang fehlt");
  }
  if (digitalRead(SENSOR_DEV_OUT) == LOW) {
    setError(ERROR_SENSOR_DEV_MISSING);
    logEvent("Sensor Entwickler-Ausgang fehlt");
  }
  if (digitalRead(SENSOR_FIX_IN) == LOW) {
    setError(ERROR_SENSOR_FIX_MISSING);
    logEvent("Sensor Fixierer-Eingang fehlt");
  }
  if (digitalRead(SENSOR_FIX_OUT) == LOW) {
    setError(ERROR_SENSOR_FIX_MISSING);
    logEvent("Sensor Fixierer-Ausgang fehlt");
  }
  if (digitalRead(SENSOR_WASH_IN) == LOW) {
    setError(ERROR_SENSOR_WASH_MISSING);
    logEvent("Sensor Wäscher-Eingang fehlt");
  }
  if (digitalRead(SENSOR_WASH_OUT) == LOW) {
    setError(ERROR_SENSOR_WASH_MISSING);
    logEvent("Sensor Wäscher-Ausgang fehlt");
  }
  if (digitalRead(SENSOR_DRY_IN) == LOW) {
    setError(ERROR_SENSOR_DRY_MISSING);
    logEvent("Sensor Trockner-Eingang fehlt");
  }
  if (digitalRead(SENSOR_DRY_OUT) == LOW) {
    setError(ERROR_SENSOR_DRY_MISSING);
    logEvent("Sensor Trockner-Ausgang fehlt");
  }
}

#endif // SENSORS_H
