//
// Created by nsk8kor on 24/02/22.
//

#ifndef COVERAGE_IN_CPP_SKANDANARAYANA_BREACHTYPEALERT_H
#define COVERAGE_IN_CPP_SKANDANARAYANA_BREACHTYPEALERT_H

class IBreachType{
public:
    virtual std::string printBreachTypeInfo(std::string recipient) = 0;
};

class BreachAlert{
public:
    IBreachType *breachType;
    BreachAlert(IBreachType *breach) : breachType(breach){}
    ~BreachAlert()
    {
        delete this->breachType;
    }
    void outputAlert(std::string recipient){
        breachType->printBreachTypeInfo(recipient);
    }
};

class LowBreachType : public IBreachType{
public:
    std::string printBreachTypeInfo(std::string recipient){
        std::string emailContent = {"To: " +recipient};
        emailContent += " Hi, the temperature is too low\n";
        return emailContent;
    }
};

class HighBreachType: public IBreachType{
public:
    std::string printBreachTypeInfo(std::string recipient) {
        std::string emailContent = "To: " + recipient;
        emailContent += " Hi, the temperature is too high\n";
        return emailContent;
    }
};

class NormalBreachType: public IBreachType{
public:
    std::string printBreachTypeInfo(std::string recipient) {
        std::string emailContent = "To: " + recipient;
        emailContent += " Hi, the temperature is normal\n";
        return emailContent;
    }
};
#endif //COVERAGE_IN_CPP_SKANDANARAYANA_BREACHTYPEALERT_H
