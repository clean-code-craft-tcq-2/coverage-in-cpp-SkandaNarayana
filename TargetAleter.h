//
// Created by nsk8kor on 24/02/22.
//

#ifndef COVERAGE_IN_CPP_SKANDANARAYANA_TARGETALETER_H
#define COVERAGE_IN_CPP_SKANDANARAYANA_TARGETALETER_H

#include "BreachTypeAlert.h"
class ITargetAlert{
public:
    virtual void sendToTarget(BreachType breachType) = 0;
};

class TargetAlert{
    ITargetAlert *targetAlert;
public:
    TargetAlert(ITargetAlert *targetAlert1): targetAlert(targetAlert1){}
    ~TargetAlert(){
        delete targetAlert;
    }

    void alertTheTarget(BreachType breachType){
        targetAlert->sendToTarget(breachType);
    }
};

class ControllerAlert: public ITargetAlert{
public:
    void sendToTarget(BreachType breachType){
        const unsigned short header = 0xfeed;
        std::cout<< header << ", " << breachType << std::endl;
    }
};

class EmailAlert:public ITargetAlert{
public:
    void sendToTarget(BreachType breachType){
        std::string recipient = "a.b@c.com";
        BreachAlert *alert;
        if (breachType == TOO_LOW) {
            alert = new BreachAlert(new LowBreachType);
        }
        if(breachType == TOO_HIGH){
            alert = new BreachAlert(new HighBreachType);
        }
        if(breachType == NORMAL){
            alert = new BreachAlert(new NormalBreachType);
        }
        alert->outputAlert(recipient);
    }
};

#endif //COVERAGE_IN_CPP_SKANDANARAYANA_TARGETALETER_H
