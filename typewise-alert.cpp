#include "typewise-alert.h"
#include "TargetAleter.h"
#include "TemperatureBreachClassifier.h"

TargetAlert* getAlert(const AlertTarget &alertTarget);


std::map<CoolingType, ITemperatureBreachClassifier*> CoolingTypeMap = {
        {PASSIVE_COOLING, new PassiveCooling},
        {HI_ACTIVE_COOLING, new HiActiveCooling},
        {MED_ACTIVE_COOLING, new MedActiveCooling}
};

TemperatureBreachClassifier* getClassifiedBreach(std::map<CoolingType, ITemperatureBreachClassifier*> CoolingTypeMap, CoolingType coolingType){
    return new TemperatureBreachClassifier(CoolingTypeMap[coolingType]);
}


BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
        TemperatureBreachClassifier *breachClassifier;
        breachClassifier = getClassifiedBreach(CoolingTypeMap, coolingType);
        return breachClassifier->classifyBreach(temperatureInC);
}

AlertStatus checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

    TargetAlert* targetAlert = getAlert(alertTarget);

    return targetAlert->alertTheTarget(breachType);

}

TargetAlert* getAlert(const AlertTarget &alertTarget) {
    TargetAlert *targetAlert;
    if(alertTarget == TO_CONTROLLER){
        targetAlert = new TargetAlert(new ControllerAlert);
    }
    if(alertTarget == TO_EMAIL){
        targetAlert = new TargetAlert(new EmailAlert);
    }
    return targetAlert;
}
