#include "CoffeeMachine.hpp"

using std::string;
using std::cout, std::cin, std::flush;
using std::getline;
using std::invalid_argument;
using std::set;

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

const string CoffeeMachine::keyWordShutdown{"shutdown"};
const string CoffeeMachine::keyWordWait{"wait"};
const string CoffeeMachine::keyWordTake{"take"};

const set<int> CoffeeMachine::coins{1, 2, 5, 10, 20};

void CoffeeMachine::moneyBack() {
    int times;
    cout << machineMoneyBack;
    for (auto it = coins.rbegin(); it != coins.rend(); ++it) {
        times = balance / *it;
        if (times) {
            cout << times << "x" << *it << " ";
            balance %= *it;
        }
    }
    cout << "\n";
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

CoffeeMachine::CoffeeMachine(int price) : price(price) {}

bool CoffeeMachine::start() {
    cout << machineStart << "\n";
    cout << machineMoney << "\n";
    while (getline(cin, line)) {
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
    }
    cout << machineShutdown << "\n";
    return true;
}
