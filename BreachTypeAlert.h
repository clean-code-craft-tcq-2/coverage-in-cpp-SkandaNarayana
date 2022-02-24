//
// Created by nsk8kor on 24/02/22.
//

#ifndef COVERAGE_IN_CPP_SKANDANARAYANA_BREACHTYPEALERT_H
#define COVERAGE_IN_CPP_SKANDANARAYANA_BREACHTYPEALERT_H

class IBreachType{
public:
    virtual void printBreachTypeInfo(std::string recipient) = 0;
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
    void printBreachTypeInfo(std::string recipient){
        std::cout << "To: "<< recipient <<"\n";
        std::cout <<"Hi, the temperature is too low\n";
    }
};

class HighBreachType: public IBreachType{
public:
    void printBreachTypeInfo(std::string recipient) {
        std::cout << "To: "<< recipient <<"\n";
        std::cout <<"Hi, the temperature is too high\n";
    }
};

class NormalBreachType: public IBreachType{
public:
    void printBreachTypeInfo(std::string recipient) {
        std::cout << "To: "<< recipient <<"\n";
        std::cout <<"Hi, the temperature is normal\n";
    }
};
#endif //COVERAGE_IN_CPP_SKANDANARAYANA_BREACHTYPEALERT_H
