#include "CoffeeMachine.hpp"

using std::string;
using std::cout, std::cin, std::flush;
using std::getline;
using std::invalid_argument;
using std::map;

const string CoffeeMachine::machineStart{"Starting..."};
const string CoffeeMachine::machineCost{"Coffee cost: "};
const string CoffeeMachine::machineBalance{"Your balance: "};
const string CoffeeMachine::machineShutdown{"Shuting down..."};
const string CoffeeMachine::machineInvalidMoney{"Not valid coin."};
const string CoffeeMachine::machineNotMoney{"That's not money."};
const string CoffeeMachine::machineDoNotReturn{"I do not return"};
const string CoffeeMachine::machineMoney{"Give me money for coffee."};
const string CoffeeMachine::machinePourCoffee{"Wait, pouring coffee."};
const string CoffeeMachine::machineDidNotWait{"Just wait..."};
const string CoffeeMachine::machineCoffeDone{"Coffee done. Take it."};
const string CoffeeMachine::machineDidNotTake{"You didn't take the coffee."};
const string CoffeeMachine::machineError{"Something went wrong."};
const string CoffeeMachine::machineMoneyBack{"Here is money back: "};
const string CoffeeMachine::machineNoMoreMoney{"I'm have to more money to give you back."};

const string CoffeeMachine::keyWordShutdown{"shutdown"};
const string CoffeeMachine::keyWordWait{"wait"};
const string CoffeeMachine::keyWordTake{"take"};

const map<int, int> CoffeeMachine::default_coins{{1,0}, {2,0}, {5,0}, {10,0}, {20,0}};

void CoffeeMachine::moneyBack() {
    int times;
    cout << machineMoneyBack;
    for (auto it = coins.rbegin(); it != coins.rend(); ++it) {
        if (! it->second) continue;
        times = balance / it->first;
        if (times) {
            if (times >= it->second) {
                cout << it->second << "x" << it->first << " ";
                balance -= it->second * it->first;
                it->second = 0;
            } else {
                cout << times << "x" << it->first << " ";
                balance %= it->first;
                it->second -= times;
            }    
        }
    }
    cout << "\n";
    if (balance) {
        balance = 0;
        cout << machineNoMoreMoney << "\n";
    }
}

void CoffeeMachine::processMoneyState() {
    int coin;
    try {
        coin = stoi(line);
    } catch (const invalid_argument &e) {
        cout << machineNotMoney << "\n"; 
    }
    if(!coins.contains(coin)){
        cout << machineInvalidMoney << "\n";
    } else {
        balance += coin;
        ++coins[coin];
        if (balance >= price){
            balance -= price;
            moneyBack();
            state = pour;
            cout << machinePourCoffee << "\n";
            return;
        }
    }
    cout << machineMoney << "\n";
    if(balance > 0)
        cout << machineBalance << balance << "\n";
}

void CoffeeMachine::processPourState() {
    if(line == keyWordWait) {
        state = ready;
        cout << machineCoffeDone << "\n";
        return;
    }
    cout << machineDidNotWait << "\n";
    cout << machinePourCoffee << "\n";
}

void CoffeeMachine::processReadyState() {
    if(line == keyWordTake) {
        state = money;
        cout << machineMoney << "\n";
        return;
    }
    cout << machineDidNotTake << "\n";
    cout << machineCoffeDone << "\n";
}

CoffeeMachine::CoffeeMachine(int price) : coins(default_coins), price(price) { }

bool CoffeeMachine::start() {
    cout << machineStart << "\n";
    cout << machineMoney << "\n";
    while (getline(cin, line)) {
        cout << "Start: ";
        for (const auto &[key, value] : coins)
            cout << key << " " << value << " | ";
        cout << "\n";
        cout << "\n";
        if (line == keyWordShutdown)
            break; 

        switch (state) {
            case money:
                processMoneyState();
                break;
            case pour:
                processPourState();
                break;
            case ready:
                processReadyState();
                break;
            default:
                cout << machineError << "\n";
                return false;
        }
        cout << flush;
    cout << "End:   ";
    for (const auto &[key, value] : coins)
        cout << key << " " << value << " | ";
    cout << "\n";
    }
    cout << machineShutdown << "\n";
    return true;
}
