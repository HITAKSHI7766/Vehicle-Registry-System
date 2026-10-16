#include <iostream>
using namespace std;

class Vehicle
{
protected:
    int vehicleID;
    string manufacturer, model;
    int year;

public:
    static int totalVehicles;

    Vehicle(int id, string manufacturer, string model, int year)
    {
        this->vehicleID = id;
        this->manufacturer = manufacturer;
        this->model = model;
        this->year = year;
        totalVehicles++;
    }

    int getID()
    {
        return vehicleID;
    }

    void setID(int id)
    {
        vehicleID = id;
    }

    virtual void display()
    {
        cout << "ID: " << vehicleID << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }

    virtual ~Vehicle()
    {
        cout << "Vehicle deleted" << endl;
    }
};

int Vehicle::totalVehicles = 0;

// Single Inheritance
class Car : public Vehicle
{
protected:
    string fuelType;

public:
    Car(int id, string m, string mo, int y, string fuel)
        : Vehicle(id, m, mo, y)
    {
        fuelType = fuel;
    }

    void display()
    {
        Vehicle::display();
        cout << "Fuel: " << fuelType << endl;
    }
};

// Multilevel Inheritance
class ElectricCar : public Car
{
protected:
    int batteryCapacity;

public:
    ElectricCar(int id, string m, string mo, int y,
                string fuel, int battery)
        : Car(id, m, mo, y, fuel)
    {
        batteryCapacity = battery;
    }

    void display()
    {
        Car::display();
        cout << "Battery: " << batteryCapacity << endl;
    }
};

class SportsCar : public ElectricCar
{
public:
    int topSpeed;

    SportsCar(int id, string m, string mo, int y,
              string fuel, int battery, int speed)
        : ElectricCar(id, m, mo, y, fuel, battery)
    {
        topSpeed = speed;
    }

    void display()
    {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << endl;
    }
};

// Hierarchical Inheritance
class Sedan : public Car
{
public:
    Sedan(int id, string m, string mo, int y, string fuel)
        : Car(id, m, mo, y, fuel) {

        }
};

class SUV : public Car
{
public:
    SUV(int id, string m, string mo, int y, string fuel)
        : Car(id, m, mo, y, fuel) {

        }
};

// Multiple Inheritance
class Aircraft
{
protected:
    int flightRange;

public:
    Aircraft(int range)
    {
        flightRange = range;
    }
};

class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar(int id, string m, string mo, int y,
              string fuel, int range)
        : Car(id, m, mo, y, fuel), Aircraft(range) {
            
        }

    void display()
    {
        Car::display();
        cout << "Flight Range: " << flightRange << endl;
    }
};

// Vehicle Registry
class VehicleRegistry
{
public:
    Vehicle* vehicles[100];
    int count;

    VehicleRegistry()
    {
        count = 0;
    }

    void addVehicle(Vehicle* v)
    {
        if (count < 100)
        {
            vehicles[count] = v;
            count++;
            cout << "Vehicle Added!" << endl;
        }
        else
        {
            cout << "Registry Full!" << endl;
            delete v;
        }
    }

    void displayAll()
    {
        for (int i = 0; i < count; i++)
        {
            vehicles[i]->display();
            cout << endl;
        }
    }

    void searchByID(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (vehicles[i]->getID() == id)
            {
                vehicles[i]->display();
                return;
            }
        }

        cout << "Vehicle Not Found!" << endl;
    }

    ~VehicleRegistry()
    {
        for (int i = 0; i < count; i++)
        {
            delete vehicles[i];
        }
    }
};

int main()
{
    VehicleRegistry r;
    int choice, id, year, battery, speed, range;
    string manufacturer, model, fuel;

    do
    {
        cout << "\n1. Add Car";
        cout << "\n2. Add Electric Car";
        cout << "\n3. Add Sports Car";
        cout << "\n4. Add Sedan";
        cout << "\n5. Add SUV";
        cout << "\n6. Add Flying Car";
        cout << "\n7. Display All";
        cout << "\n8. Search Vehicle";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 6)
        {
            cout << "Enter ID, Manufacturer, Model, Year: ";
            cin >> id >> manufacturer >> model >> year;

            if (choice == 1)
            {
                cout << "Enter Fuel: ";
                cin >> fuel;
                r.addVehicle(new Car(id, manufacturer, model, year, fuel));
            }
            else if (choice == 2)
            {
                cout << "Enter Fuel and Battery: ";
                cin >> fuel >> battery;
                r.addVehicle(new ElectricCar(id, manufacturer, model, year,
                                             fuel, battery));
            }
            else if (choice == 3)
            {
                cout << "Enter Fuel, Battery and Speed: ";
                cin >> fuel >> battery >> speed;
                r.addVehicle(new SportsCar(id, manufacturer, model, year,
                                           fuel, battery, speed));
            }
            else if (choice == 4)
            {
                cout << "Enter Fuel: ";
                cin >> fuel;
                r.addVehicle(new Sedan(id, manufacturer, model, year, fuel));
            }
            else if (choice == 5)
            {
                cout << "Enter Fuel: ";
                cin >> fuel;
                r.addVehicle(new SUV(id, manufacturer, model, year, fuel));
            }
            else if (choice == 6)
            {
                cout << "Enter Fuel and Flight Range: ";
                cin >> fuel >> range;
                r.addVehicle(new FlyingCar(id, manufacturer, model, year,
                                           fuel, range));
            }
        }
        else if (choice == 7)
        {
            r.displayAll();
        }
        else if (choice == 8)
        {
            cout << "Enter Vehicle ID: ";
            cin >> id;
            r.searchByID(id);
        }
        else if (choice == 0)
        {
            cout << "Thank You!" << endl;
        }
        else
        {
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}

