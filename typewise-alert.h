#pragma once
#include <string>
#include <iostream>
#include <map>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef enum {
    ALERT_REQUIRED,
    ALERT_NOT_REQUIRED
} AlertNecessity;

typedef enum {
    ALERT_SENT,
    ALERT_NOT_SENT
} AlertStatus;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

AlertStatus checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
