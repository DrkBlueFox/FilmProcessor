// sd_log.h // Ereignis- und Fehlerlogging auf SD-Karte

#ifndef SD_LOG_H #define SD_LOG_H

#include <SD.h> #include <SPI.h>

#define SD_CS_PIN 5  // Chip-Select-Pin anpassen! #define LOGFILE "/log.txt"

// Initialisierung der SD-Karte bool initSD() { return SD.begin(SD_CS_PIN); }

// Aktuelle Zeit simuliert (ggf. durch RTC ersetzen) String getTimeStamp() { unsigned long ms = millis(); unsigned long sec = ms / 1000; unsigned long min = sec / 60; unsigned long hour = min / 60; char buffer[32]; snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu", hour % 24, min % 60, sec % 60); return String(buffer); }

// Logeintrag schreiben void logEvent(String entry) { File logFile = SD.open(LOGFILE, FILE_APPEND); if (logFile) { logFile.print("["); logFile.print(getTimeStamp()); logFile.print("] "); logFile.println(entry); logFile.close(); } }

// Beispiel: logEvent("Filmstart erkannt - Typ SW");

#endif // SD_LOG_H


