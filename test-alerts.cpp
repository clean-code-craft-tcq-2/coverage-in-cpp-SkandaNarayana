#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "TargetAleter.h"
#include "TemperatureBreachClassifier.h"
#include "BreachTypeAlert.h"

TargetAlert *getAlert(const AlertTarget &alertTarget);

TEST_CASE("classifies the Breach depending for PASSIVE_COOLING type") {
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 50) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -10) == TOO_LOW);
}

TEST_CASE("classifies the Breach depending for HI_ACTIVE_COOLING type") {
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -10) == TOO_LOW);
}

TEST_CASE("classifies the Breach depending for MED_ACTIVE_COOLING type") {
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 50) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -10) == TOO_LOW);
}

TEST_CASE("infer the breach type based on limits"){
    PassiveCooling breachClassifier;
    REQUIRE(breachClassifier.inferBreach(10, 0, 20) == NORMAL);
    REQUIRE(breachClassifier.inferBreach(21, 0, 20) == TOO_HIGH);
    REQUIRE(breachClassifier.inferBreach(-1, 0, 20) == TOO_LOW);
}

TEST_CASE("gets breach type for Hi Active cooling"){
    HiActiveCooling cooling;
    REQUIRE(cooling.checkTempBreachType(40) == NORMAL);
    REQUIRE(cooling.checkTempBreachType(-20) == TOO_LOW);
    REQUIRE(cooling.checkTempBreachType(50) == TOO_HIGH);
}

TEST_CASE("gets breach type for Passive cooling"){
    PassiveCooling cooling;
    REQUIRE(cooling.checkTempBreachType(30) == NORMAL);
    REQUIRE(cooling.checkTempBreachType(-20) == TOO_LOW);
    REQUIRE(cooling.checkTempBreachType(40) == TOO_HIGH);
}

TEST_CASE("gets breach type for MedActiveCooling cooling"){
    MedActiveCooling cooling;
    REQUIRE(cooling.checkTempBreachType(30) == NORMAL);
    REQUIRE(cooling.checkTempBreachType(-20) == TOO_LOW);
    REQUIRE(cooling.checkTempBreachType(45) == TOO_HIGH);
}

TEST_CASE("classifies the type of breach"){
    TemperatureBreachClassifier *breachClassifier = new TemperatureBreachClassifier(new PassiveCooling);
    REQUIRE(breachClassifier->classifyBreach(54) == TOO_HIGH );
    REQUIRE(breachClassifier->classifyBreach(54) == TOO_HIGH );
}

TEST_CASE(" the type of breach"){
    TemperatureBreachClassifier *breachClassifier = new TemperatureBreachClassifier(new PassiveCooling);
    REQUIRE(breachClassifier->classifyBreach(54) == TOO_HIGH );
}

//TEST_CASE(" get the email alert"){
//    TargetAlert* targetAlert = new TargetAlert(new EmailAlert);
//    REQUIRE(getAlert(TO_EMAIL));
//}
//
//TEST_CASE(" get the controller alert"){
//    TargetAlert* targetAlert = new TargetAlert(new EmailAlert);
//    REQUIRE(getAlert(TO_EMAIL));
//}

TEST_CASE(" the content of email when temp is too low"){
    LowBreachType lowBreach;
    REQUIRE(lowBreach.printBreachTypeInfo("admin") == "To: admin Hi, the temperature is too low\n");
}

TEST_CASE(" the content of email when temp is too high"){
    HighBreachType highBreach;
    REQUIRE(highBreach.printBreachTypeInfo("admin") == "To: admin Hi, the temperature is too high\n");
}

TEST_CASE("alert required to email when temperature is low"){
    EmailAlert emailAlert;
    REQUIRE(emailAlert.sendToTarget(TOO_LOW) == ALERT_REQUIRED);
}

TEST_CASE("alert required to email when temperature is high"){
    EmailAlert emailAlert;
    REQUIRE(emailAlert.sendToTarget(TOO_HIGH) == ALERT_REQUIRED);
}

TEST_CASE("alert not required to email when temperature is normal"){
    EmailAlert emailAlert;
    REQUIRE(emailAlert.sendToTarget(NORMAL) == ALERT_NOT_REQUIRED);
}

TEST_CASE("alert not required to message sent to controller"){
    ControllerAlert controllerAlert;
    REQUIRE(controllerAlert.sendToTarget(NORMAL) == ALERT_NOT_REQUIRED);
}

TEST_CASE("valid output from checkAndAlert"){
    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;
    REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 45) == ALERT_NOT_SENT);
}

TEST_CASE("test output for checkAndAlert PASSIVE_COOLING to controller"){
    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;
    REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 45) == ALERT_NOT_SENT);
}

TEST_CASE("test output for checkAndAlert PASSIVE_COOLING to email"){
    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;
    REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 45) == ALERT_SENT);
}