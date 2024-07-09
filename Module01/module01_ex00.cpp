#include<iostream>
#include<string>

class Car
{

    public:
    std::string name;
    int speed;

    Car(std::string _name, int _speed);
    Car(Car& object);
    Car& operator=(const Car& other);
    ~Car() = default;
};

Car::Car(std::string _name, int _speed)
{
    name =_name;
    speed = _speed;
    std::cout << "Constructor is called\n";
    std::cout << "Name: " << name ;
    std::cout << "\nSpeed: " << speed;
    std::cout << std::endl;
}

Car::Car(Car& object)
{
    name = object.name;
    speed = object.speed;
    std::cout << "Copy Constructor is called\n";
    std::cout << "Name: " << name ;
    std::cout << "\nSpeed: " << speed;
    std::cout << std::endl;
}

Car& Car::operator=(const Car& other)
{
    name = other.name;
    speed = other.speed;
    std::cout << "Copy Assignment Operator is called\n";
    std::cout << "Name: " << name ;
    std::cout << "\nSpeed: " << speed;
    std::cout << std::endl;
    return *this;
}

int main()
{
    Car a("a", 200);
    Car b (a);
    b = a;
    return 0;
}