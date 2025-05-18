// tank_config.h
// Tanktyp-Erkennung und Konfiguration über ID-Pin

#ifndef TANK_CONFIG_H
#define TANK_CONFIG_H

#include <Arduino.h>

// Beispielhafte Pin-Zuweisung für Tank-ID
#define TANK_ID_PIN_DEV  21
#define TANK_ID_PIN_FIX  22
#define TANK_ID_PIN_WASH 23
#define TANK_ID_PIN_DRY  24

// Tanktyp-IDs
enum TankType {
  TANK_UNKNOWN,
  TANK_SW_DEV,
  TANK_C41_DEV,
  TANK_FIX,
  TANK_WASH,
  TANK_DRY
};

// Prozessmodus (z. B. aus Displaywahl)
enum ProcessType {
  PROC_UNKNOWN,
  PROC_SW,
  PROC_C41
};

// Tanktyp über ID-Pin erkennen
TankType detectTankType(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
  delay(10); // Stabilisierung

  if (digitalRead(pin) == LOW) {
    switch (pin) {
      case TANK_ID_PIN_DEV: return TANK_SW_DEV;  // Standard: SW Entwickler
      case TANK_ID_PIN_FIX: return TANK_FIX;
      case TANK_ID_PIN_WASH: return TANK_WASH;
      case TANK_ID_PIN_DRY: return TANK_DRY;
      default: return TANK_UNKNOWN;
    }
  }
  return TANK_UNKNOWN;
}

// Kompatibilitätsprüfung Tank <-> Prozesswahl
bool isTankCompatible(ProcessType selected, TankType devTank) {
  if (selected == PROC_SW && devTank == TANK_SW_DEV) return true;
  if (selected == PROC_C41 && devTank == TANK_C41_DEV) return true;
  return false;
}

// Alle Tanks abfragen (z. B. bei Systemstart)
void scanAllTanks() {
  TankType devType = detectTankType(TANK_ID_PIN_DEV);
  TankType fixType = detectTankType(TANK_ID_PIN_FIX);
  TankType washType = detectTankType(TANK_ID_PIN_WASH);
  TankType dryType = detectTankType(TANK_ID_PIN_DRY);

  // Optional: Logik, Anzeige, Sicherheitsprüfungen...
}

#endif // TANK_CONFIG_H