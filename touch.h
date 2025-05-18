// touch.h // Touch-Eingabeverarbeitung vom Nextion-Display

#ifndef TOUCH_H #define TOUCH_H

#include <Arduino.h> #include "display.h" #include "maintenance.h" #include "sd_log.h"

#define NEXTION Serial2

// Touch-Ereignisse abfragen void checkTouchInput() { while (NEXTION.available() >= 7) { byte buffer[7]; for (int i = 0; i < 7; i++) { buffer[i] = NEXTION.read(); }

// Touch Event erkannt
if (buffer[0] == 0x65 && buffer[4] == 0xFF && buffer[5] == 0xFF && buffer[6] == 0xFF) {
  byte pageID = buffer[1];
  byte compID = buffer[2];
  byte eventType = buffer[3];

  if (eventType == 0x01) {
    handleTouch(pageID, compID);
  }
}

} }

// Reaktion auf Touch-Ereignisse void handleTouch(byte page, byte component) { if (page == 0 && component == 1) { logEvent("Start-Button gedrückt"); // Startprozess aufrufen } else if (page == 0 && component == 2) { logEvent("Notstopp ausgelöst"); // Notstopp-Funktion auslösen } else if (page == 2 && component == 1) { acknowledgeMaintenance(0); logEvent("Wartungseintrag 1 bestätigt"); } // Weitere Komponenten einfügen }

#endif // TOUCH_H


