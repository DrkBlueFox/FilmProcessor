

if (!isTankCompatible(currentProcess, detectTankType(TANK_ID_PIN_DEV))) {
  setError(ERROR_TANK_MISMATCH);
  logEvent("Tanktyp stimmt nicht mit Auswahl überein");
  return;
}

if (isFilmInserted() && machineState == STATE_WAIT_FOR_FILM) {
  logEvent("Film eingeführt – Leader erkannt");
  startFilmEinzug();  // Transportlogik
}