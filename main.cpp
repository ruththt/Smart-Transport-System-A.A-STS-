#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Passenger {
public:
    string name;
    double balance;
    Passenger(string n, double b) : name(n), balance(b) {}
};

class Vehicle {
protected:
    int capacity;
    double fare;
    vector<Passenger> onboard;
public:
    Vehicle(int cap, double f) : capacity(cap), fare(f) {}
    virtual string type() = 0;

    bool boardPassenger(Passenger p) {
        if (onboard.size() < capacity) {
            if (p.balance >= fare) {
                onboard.push_back(p);
                cout << p.name << " boarded " << type() << " paying " << fare << " ETB.\n";
                return true;
            } else {
                cout << p.name << " has insufficient balance.\n";
                return false;
            }
        } else {
            cout << type() << " is full. " << p.name << " cannot board.\n";
            return false;
        }
    }

    void tripSummary() {
        cout << type() << " carried " << onboard.size() << " passengers.\n";
    }
};

class Minibus : public Vehicle {
public:
    Minibus() : Vehicle(11, 10.0) {}
    string type() override { return "Minibus"; }
};

class Bus : public Vehicle {
public:
    Bus() : Vehicle(50, 5.0) {}
    string type() override { return "Bus"; }
};

class Train : public Vehicle {
public:
    Train() : Vehicle(200, 3.0) {}
    string type() override { return "Train"; }
};

class TransportManager {
    queue<Passenger> waitingPassengers;
public:
    void addPassenger(Passenger p) {
        waitingPassengers.push(p);
    }

    void dispatch(Vehicle &v) {
        while (!waitingPassengers.empty()) {
            Passenger p = waitingPassengers.front();
            if (!v.boardPassenger(p)) break;
            waitingPassengers.pop();
        }
        v.tripSummary();
    }
};

int main() {
    TransportManager manager;

    manager.addPassenger(Passenger("Abebe", 20));
    manager.addPassenger(Passenger("Almaz", 8));
    manager.addPassenger(Passenger("Kebede", 15));
    manager.addPassenger(Passenger("Sara", 5));
    manager.addPassenger(Passenger("Tesfaye", 50));

    Minibus minibus;
    Bus bus;
    Train train;

    cout << "\nDispatching Minibus:\n";
    manager.dispatch(minibus);

    cout << "\nDispatching Bus:\n";
    manager.dispatch(bus);

    cout << "\nDispatching Train:\n";
    manager.dispatch(train);

    return 0;
}

