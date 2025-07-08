#include <iostream>
#include <memory>
#include <string>

using namespace std;

class IEngine
{
public:
    virtual string start() = 0;
    virtual ~IEngine() = default;
};

class IVehicle
{
public:
    explicit IVehicle(IEngine &engine) : m_engine(engine) {

    }
    void drive() { 
        
        string out = m_engine.start() + " " + driveVehicle() ;
        cout << "Driving " << out << endl;
    }
    virtual ~IVehicle() = default;
protected:
    virtual string driveVehicle() = 0;
private:
    IEngine &m_engine;
};


class GasEngine : public IEngine
{
    string start() override
    {
        return "Gas Engine";
    }
};

class ElectricEngine : public IEngine
{
    string start() override
    {
        return "Electric Engine";
    }
};

class HybridEngine : public IEngine
{
    string start() override
    {
        return "Hybrid Engine";
    }
};


class Car : public IVehicle
{
    public:
    Car(IEngine & engine) : IVehicle(engine) { }
    protected:
    string driveVehicle() override { return "Car";}
};

class Truck : public IVehicle
{
    public:
    Truck(IEngine & engine) : IVehicle(engine) {

    }
    protected:
    string driveVehicle() override { 
        return "Truck";
    }
};


int main()
{
    GasEngine gasEngine;
    ElectricEngine electricEngine;
    HybridEngine hybridEngine;

    const std::unique_ptr<IVehicle> vehicles[]{
        make_unique<Car>(gasEngine),
        make_unique<Car>(electricEngine),
        make_unique<Truck>(gasEngine)
    };

    for (const auto &vehicle : vehicles) {
        vehicle->drive();
    }

    return 0;
}