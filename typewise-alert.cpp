#include "typewise-alert.h"
#include "TargetAleter.h"
#include "TemperatureBreachClassifier.h"

TargetAlert *getAlert(const AlertTarget &alertTarget);

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
        BreachType breachType;
        TemperatureBreachClassifier *breachClassifier;
        if(coolingType == PASSIVE_COOLING){
            breachClassifier = new TemperatureBreachClassifier(new PassiveCooling);
        }
        if(coolingType == HI_ACTIVE_COOLING){
            breachClassifier = new TemperatureBreachClassifier(new HiActiveCooling);
        }
        if(coolingType == MED_ACTIVE_COOLING){
            breachClassifier = new TemperatureBreachClassifier(new MedActiveCooling);
        }
        return breachClassifier->classifyBreach(temperatureInC);

}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

    TargetAlert *targetAlert = getAlert(alertTarget);

    targetAlert->alertTheTarget(breachType);
}

TargetAlert *getAlert(const AlertTarget &alertTarget) {
    TargetAlert *targetAlert;
    if(alertTarget == TO_CONTROLLER){
        targetAlert = new TargetAlert(new ControllerAlert);
    }
    if(alertTarget == TO_EMAIL){
        targetAlert = new TargetAlert(new EmailAlert);
    }
    return targetAlert;
}
