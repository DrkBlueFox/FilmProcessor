// display.h // Nextion Displaysteuerung für ESP32

#ifndef DISPLAY_H #define DISPLAY_H

#include <Arduino.h> #define NEXTION Serial2

// Drei 0xFF zur Abschlusskennung void sendTerminator() { NEXTION.write(0xFF); NEXTION.write(0xFF); NEXTION.write(0xFF); }

// Textfeld aktualisieren (z. B. Statusanzeige) void setText(const String &component, const String &text) { NEXTION.print(component + ".txt="" + text + """); sendTerminator(); }

// Zahl setzen (z. B. Fortschritt) void setValue(const String &component, int value) { NEXTION.print(component + ".val=" + String(value)); sendTerminator(); }

// Seite wechseln void setPage(const String &pageName) { NEXTION.print("page " + pageName); sendTerminator(); }

// Fehleranzeige auf Fehlerseite ausgeben void showError(const String &errorMessage) { setPage("error"); delay(100); setText("t_error", errorMessage);  // 't_error' = Textfeld auf Fehlerseite }

// Wartungshinweis auf Wartungsseite setzen void showMaintenanceHint(int index, const String &title, const String &msg, const String &level) { // Beispiel für Felder: t_m0, t_m0lvl, t_m0msg (max 5 z. B.) setText("t_m" + String(index), title); setText("t_m" + String(index) + "msg", msg); setText("t_m" + String(index) + "lvl", level); }

// Displayinitialisierung (UART starten) void initDisplay(int baudrate = 9600) { NEXTION.begin(baudrate); delay(100); setPage("main"); setText("t0", "Systemstart..."); }

#endif // DISPLAY_H


