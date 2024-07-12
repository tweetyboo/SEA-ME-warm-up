#include<iostream>
#include<string>
#include<memory>
#include<array>
using namespace std;

class Part {
public:
    virtual void print() = 0; // Pure virtual function to be overridden by derived classes
    virtual ~Part() = default;
};

class Engine : public Part {
public:
    void print() override {
        cout << "Engine part\n";
    }
};

class Wheel : public Part {
public:
    void print() override {
        cout << "Wheel part\n";
    }
};

class Brake : public Part {
public:
    void print() override {
        cout << "Brake part\n";
    }
};

class Transmission : public Part {
public:
    void print() override {
        cout << "Transmission part\n";
    }
};

class Infotainment_System : public Part {
public:
    void print() override {
        cout << "Infotainment System\n";
    }
};

class Chassis : public Part {
public:
    void print() override {
        cout << "Chassis\n";
    }
};

class ZCU : public Part {
public:
    void print() override {
        cout << "ZCU\n";
    }
};

class Car {
public:
    Car() {
        engine_ = make_unique<Engine>();
        for (int i = 0; i < 4; ++i) {
            wheels_[i] = make_unique<Wheel>();
            brakes_[i] = make_unique<Brake>();
            zcu_[i] = make_unique<ZCU>();
        }
        transmission_ = make_unique<Transmission>();
        info_ = make_unique<Infotainment_System>();
        chassis_ = make_unique<Chassis>();
    }
    
    void printParts() {
        engine_->print();
        for (int i = 0; i < 4; ++i) {
            wheels_[i]->print();
            brakes_[i]->print();
            zcu_[i]->print();
        }
        transmission_->print();
        info_->print();
        chassis_->print();

    }
    
    ~Car() = default;

private:
    unique_ptr<Engine> engine_;
    array<unique_ptr<Wheel>, 4> wheels_;
    array<unique_ptr<Brake>, 4> brakes_;
    unique_ptr<Transmission> transmission_;
    unique_ptr<Infotainment_System> info_;
    unique_ptr<Chassis> chassis_;
    array<unique_ptr<ZCU>, 4> zcu_;
};

int main() {
    Car myCar;
    myCar.printParts();
    return 0;
}