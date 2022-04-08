#include <iostream>
#include <string>
#include <set>

enum CoffeeMachineStates { money, pour, ready };

class CoffeeMachine {
    static const std::string machineStart;
    static const std::string machineCost;
    static const std::string machineBalance;
    static const std::string machineShutdown;
    static const std::string machineInvalidMoney;
    static const std::string machineNotMoney;
    static const std::string machineDoNotReturn;
    static const std::string machineMoney;
    static const std::string machinePourCoffee;
    static const std::string machineDidNotWait;
    static const std::string machineCoffeDone;
    static const std::string machineDidNotTake;
    static const std::string machineError;
    static const std::string machineMoneyBack;

    static const std::string keyWordShutdown;
    static const std::string keyWordWait;
    static const std::string keyWordTake;

    static const std::set<int> coins;

    int price;
    int balance = 0;
    CoffeeMachineStates state = money;
    std::string line;

    void moneyBack();

    void processMoneyState();

    void processPourState();

    void processReadyState();

public:
    CoffeeMachine(int price = 25);

    bool start();
}; 
