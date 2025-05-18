// storage.h // EEPROM-basierte Speicherfunktionen für ESP32 (Preferences/NVS)

#ifndef STORAGE_H #define STORAGE_H

#include <Preferences.h>

Preferences prefs;

// Namespace für alle Maschinendaten #define STORAGE_NAMESPACE "machine"

// Schlüsseldefinitionen #define KEY_CUT_COUNT     "cutCount" #define KEY_CHEM_CHANGE   "chemChangeDay" #define KEY_RUNTIME_HOURS "runtimeH" #define KEY_TANK_TYPE     "tankType"

// Speicherung: Schnittzähler void saveCutCount(int value) { prefs.begin(STORAGE_NAMESPACE, false); prefs.putInt(KEY_CUT_COUNT, value); prefs.end(); }

int loadCutCount() { prefs.begin(STORAGE_NAMESPACE, true); int val = prefs.getInt(KEY_CUT_COUNT, 0); prefs.end(); return val; }

// Speicherung: Chemiewechsel-Tag (z. B. epochDay) void saveChemChangeDay(int day) { prefs.begin(STORAGE_NAMESPACE, false); prefs.putInt(KEY_CHEM_CHANGE, day); prefs.end(); }

int loadChemChangeDay() { prefs.begin(STORAGE_NAMESPACE, true); int val = prefs.getInt(KEY_CHEM_CHANGE, 0); prefs.end(); return val; }

// Speicherung: Maschinenlaufzeit in Stunden void saveRuntimeHours(float hours) { prefs.begin(STORAGE_NAMESPACE, false); prefs.putFloat(KEY_RUNTIME_HOURS, hours); prefs.end(); }

float loadRuntimeHours() { prefs.begin(STORAGE_NAMESPACE, true); float val = prefs.getFloat(KEY_RUNTIME_HOURS, 0.0); prefs.end(); return val; }

// Speicherung: Aktiver Tanktyp ("SW" oder "C41") void saveTankType(String type) { prefs.begin(STORAGE_NAMESPACE, false); prefs.putString(KEY_TANK_TYPE, type); prefs.end(); }

String loadTankType() { prefs.begin(STORAGE_NAMESPACE, true); String val = prefs.getString(KEY_TANK_TYPE, ""); prefs.end(); return val; }

#endif // STORAGE_H


