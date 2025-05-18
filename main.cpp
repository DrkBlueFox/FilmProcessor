

if (!isTankCompatible(currentProcess, detectTankType(TANK_ID_PIN_DEV))) {
  setError(ERROR_TANK_MISMATCH);
  logEvent("Tanktyp stimmt nicht mit Auswahl überein");
  return;
}

startFilEinzug();