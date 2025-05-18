// Konfigurationsdatei für ESP32 GPIO-Zuordnung
// Projekt: Durchlauf-Filmentwicklungsmaschine

#ifndef CONFIG_H
#define CONFIG_H

// Stepper Pins
#define STEPPER_DEV_STEP 16
#define STEPPER_DEV_DIR  17
#define STEPPER_FIX_STEP 18
#define STEPPER_FIX_DIR  19
#define STEPPER_WASH_STEP 21
#define STEPPER_WASH_DIR  22
#define STEPPER_DRY_STEP 25
#define STEPPER_DRY_DIR  26

// Heizung
#define HEATER_DEV_PIN 33  // PWM oder Digital
#define HEATER_DRY_PIN 32  // PWM oder Digital

// Wassersteuerung
#define VALVE_WATER_PIN 14

// Buzzer
#define BUZZER_PIN 27

// Sensorik
#define SENSOR_LEADER 4
#define SENSOR_DEV_IN 5
#define SENSOR_DEV_OUT 12
#define SENSOR_FIX_IN 13
#define SENSOR_FIX_OUT 15
#define SENSOR_WASH_OUT 23

// Temperatur (1-Wire)
#define TEMP_ONEWIRE_PIN 2

// Tankidentifikation
#define TANK_ID_PIN 34

// Nextion Display (UART)
#define NEXTION_TX_PIN 1
#define NEXTION_RX_PIN 3

#endif // CONFIG_H
