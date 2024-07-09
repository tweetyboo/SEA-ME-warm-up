#include <iostream>
#include <string>

class Car
{
public:
    std::string car_make;
    std::string car_model;
    int model_year;

    Car(std::string _car_make, std::string _car_model, int _model_year) : car_make(_car_make), car_model(_car_model), model_year(_model_year) {}

    void drive()
    {
        std::cout << "Car Make: " << car_make << "\nCar Model: " << car_model << "\nRelease Year: " << model_year;
        std::cout << std::endl;
    }
    ~Car() = default;
};

class SportCar : public Car
{
public:
    int top_speed;

    SportCar(std::string _car_make, std::string _car_model, int _model_year, int _top_speed) : Car(_car_make, _car_model, _model_year), top_speed(_top_speed) {}

    void drive()
    {
        Car::drive();
        std::cout << "Top_Speed: " << top_speed;
        std::cout << std::endl;
    }

    ~SportCar() = default;
};

int main()
{
    Car myCar("Toyota", "Corolla", 2020);
    myCar.drive();

    SportCar mySportCar("Ferrari", "F8", 2022, 340);
    mySportCar.drive();

    return 0;
}
