// developer_load.h
// Entwicklerbelastung basierend auf Filmfläche

#ifndef DEVELOPER_LOAD_H
#define DEVELOPER_LOAD_H

#include <Arduino.h>
#include <Preferences.h>

#define STEP_LENGTH_MM 0.2f          // Schrittweite des Motors in mm
#define REF_FILM_AREA_CM2 630.0f     // Referenz: 135-36 hat ca. 630 cm²
#define PREF_NAMESPACE "machine"
#define PREF_DEV_LOAD "devload"

Preferences prefs;

float totalFilmArea = 0.0;  // in cm²

// Schritte und Filmtyp aufnehmen (nach jedem Transport)
void addDeveloperLoad(int steps, float filmWidthMM) {
  float mm = steps * STEP_LENGTH_MM;
  float area_cm2 = (mm * filmWidthMM) / 10.0f; // mm² zu cm²
  totalFilmArea += area_cm2;
  saveDeveloperLoad();
}

// Speichern in EEPROM
void saveDeveloperLoad() {
  prefs.begin(PREF_NAMESPACE, false);
  prefs.putFloat(PREF_DEV_LOAD, totalFilmArea);
  prefs.end();
}

// Laden aus EEPROM
void loadDeveloperLoad() {
  prefs.begin(PREF_NAMESPACE, true);
  totalFilmArea = prefs.getFloat(PREF_DEV_LOAD, 0.0);
  prefs.end();
}

// Belastungseinheiten berechnen (1.0 = 135/36)
float getDeveloperLoadUnits() {
  return totalFilmArea / REF_FILM_AREA_CM2;
}

// Zurücksetzen (z. B. bei Chemiewechsel)
void resetDeveloperLoad() {
  totalFilmArea = 0.0;
  saveDeveloperLoad();
}

#endif // DEVELOPER_LOAD_H
