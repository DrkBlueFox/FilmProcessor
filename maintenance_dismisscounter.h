// maintenance.h
// Wartungslogik für die Filmentwicklungsmaschine

#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <Arduino.h>

// Meldestufen
enum MaintenanceLevel {
  INFO,
  WARNING,
  CRITICAL
};

// Wartungseintrag
struct MaintenanceEntry {
  String title;
  String message;
  MaintenanceLevel level;
  unsigned long lastTriggerTime;
  bool acknowledged;
  int dismissCount = 0;  // Anzahl der Bestätigungen ohne echte Behebung
};

// Beispielhafte Wartungspunkte
#define MAINTENANCE_COUNT 4
MaintenanceEntry maintenanceItems[MAINTENANCE_COUNT] = {
  {"Klinge reinigen", "Reinigung nach 50 Schnitten empfohlen", WARNING, 0, false},
  {"Chemie tauschen", "Nach 14 Tagen oder 25 Filmen wechseln", WARNING, 0, false},
  {"Heizung prüfen", "Heizdauer > 60 Min./Tag", INFO, 0, false},
  {"Temperatursensor", "Sensor unplausibel", CRITICAL, 0, false}
};

// Beispielhafte Auslösefunktion für Klingen-Wartung
int cutCounter = 0;

void recordCut() {
  cutCounter++;
  if (cutCounter >= 50) {
    maintenanceItems[0].lastTriggerTime = millis();
    maintenanceItems[0].acknowledged = false;
  }
}

// Zurücksetzen / Bestätigen durch Benutzer
void acknowledgeMaintenance(int id) {
  if (id >= 0 && id < MAINTENANCE_COUNT) {
    maintenanceItems[id].dismissCount++;
    maintenanceItems[id].acknowledged = true;

    // Hochstufung bei dreifachem Ignorieren
    if (maintenanceItems[id].dismissCount >= 3 && maintenanceItems[id].level != CRITICAL) {
      maintenanceItems[id].level = CRITICAL;
    }
  }
}

#endif // MAINTENANCE_H
