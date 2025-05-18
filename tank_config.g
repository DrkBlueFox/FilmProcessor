enum ProcessType {
  PROC_UNKNOWN,
  PROC_SW,
  PROC_C41
};

bool isTankCompatible(ProcessType selected, TankType devTank) {
  if (selected == PROC_SW && devTank == TANK_SW_DEV) return true;
  if (selected == PROC_C41 && devTank == TANK_C41_DEV) return true;
  return false;
}