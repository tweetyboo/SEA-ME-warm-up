#include <iostream>
#include <string>
#include <memory>

class Car
{
public:
    Car(std::string _car_make, std::string _car_model, int _model_year) : car_make(_car_make), car_model(_car_model), model_year(_model_year) {}

    ~Car() = default;

    // void drive()
    // {
    //     std::cout << "Car Make: " << car_make << "\nCar Model: " << car_model << "\nRelease Year: " << model_year;
    //     std::cout << std::endl;
    // }

    // Getters
    // const is used to ensure that the getter function does not alter the object
    // std::string get_car_make() const
    // {
    //     return car_make;
    // }

    // std::string get_car_model() const
    // {
    //     return car_model;
    // }

    // int get_model_year() const
    // {
    //     return model_year;
    // }

    // Setters
    // void set_car_make(std::string car_make)
    // {
    //     this->car_make = car_make;
    // }

    // void set_car_model(std::string car_model)
    // {
    //     this->car_model = car_model;
    // }

    // void set_model_year(int model_year)
    // {
    //     this->model_year = model_year;
    // }

protected:
    std::string car_make;
    std::string car_model;
    int model_year;
};

class SportCar : public Car
{
public:
    SportCar(std::string _car_make, std::string _car_model, int _model_year, int _top_speed) : Car(_car_make, _car_model, _model_year), top_speed(_top_speed) {}

    //  void drive()
    // {
    //     Car::drive();
    //     std::cout << "Top_Speed: " << top_speed;
    //     std::cout << std::endl;
    // }

    // Getter for the derived class member
    int get_top_speed() const
    {
        return top_speed;
    }

    // Setter for the derived class member
    void set_top_speed(int top_speed)
    {
        this->top_speed = top_speed;
    }

    // Getters for the base class member
    std::string get_car_make() const
    {
        return car_make;
    }

    std::string get_car_model() const
    {
        return car_model;
    }

    int get_model_year() const
    {
        return model_year;
    }

    // Setters for the base class member
    void set_car_make(std::string car_make)
    {
        this->car_make = car_make;
    }

    void set_car_model(std::string car_model)
    {
        this->car_model = car_model;
    }

    void set_model_year(int model_year)
    {
        this->model_year = model_year;
    }

    ~SportCar() = default;

private:
    int top_speed;
};

int main()
{
    std::unique_ptr<SportCar> ptr1 = std::make_unique<SportCar>("Ferrari", "F8", 2022, 340);
    // Address of the pointer
    std::cout << "uniquePtr1 address: " << ptr1.get() << std::endl;

    // Getters and setters of the derived class can access the base class protected and public members.
    std::cout << "Car Make: " << ptr1->get_car_make() << "\nCar Model: " << ptr1->get_car_model() << "\nModel_Year: "
              << ptr1->get_model_year() << "\nTop_Speed: " << ptr1->get_top_speed();

    // Unique pointer can only move the ownership and cannot be shared. 
    std::unique_ptr<SportCar> ptr2 = std::move(ptr1);
    std::cout << "uniquePtr2 address: " << ptr2.get() << std::endl;

    // Once the pointer is moved or out of scope, it is set as null pointer
    if (ptr1 == nullptr)
        std::cout << "\nptr1 is nullptr" << std::endl;

    ptr2->set_car_make("Toyota");
    ptr2->set_car_model("Corolla");
    ptr2->set_model_year(2020);
    ptr2->set_top_speed(200);

    // The pointer 1 is destructed and memory is freed. This request leads to segmentation fault
    // ptr1->set_car_make("Toyota");
    // ptr1->set_car_make("Corolla");
    // ptr1->set_car_make("2020");
    // ptr1->set_car_make("200");

    std::cout << "Car Make: " << ptr2->get_car_make() << "\nCar Model: " << ptr2->get_car_model() << "\nModel_Year: "
              << ptr2->get_model_year() << "\nTop_Speed: " << ptr2->get_top_speed();
    std::cout << std::endl;

    // Shared Pointers shares the ownership and the pointer destroys only when all the instances are out of scope.
    std::shared_ptr<SportCar> ptr3 = std::make_shared<SportCar>("Ferrari", "F8", 2022, 340);
    std::cout << "sharedPtr3 address: " << ptr3.get() << std::endl;
    std::cout << "Car Make: " << ptr3->get_car_make() << "\nCar Model: " << ptr3->get_car_model() << "\nModel_Year: "
              << ptr3->get_model_year() << "\nTop_Speed: " << ptr3->get_top_speed() << std::endl;

    {
        std::shared_ptr<SportCar> ptr4 = ptr3;
        std::cout << "sharedPtr4 address: " << ptr4.get() << std::endl;
        std::cout << "ptr1 use count: " << ptr3.use_count() << std::endl;
        std::cout << "ptr2 use count: " << ptr4.use_count() << std::endl;
        ptr4->set_car_make("Toyota");
        ptr4->set_car_model("Corolla");
        ptr4->set_model_year(2020);
        ptr4->set_top_speed(200);
    }
    // Accessing ptr4 here will lead to segmentation fault
    std::cout << "Car Make: " << ptr3->get_car_make() << "\nCar Model: " << ptr3->get_car_model() << "\nModel_Year: "
              << ptr3->get_model_year() << "\nTop_Speed: " << ptr3->get_top_speed();

    std::cout << "\nptr1 use count after ptr2 is out of scope: " << ptr3.use_count() << std::endl;

    return 0;
}
