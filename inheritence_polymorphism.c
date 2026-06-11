// gcc inheritence_polymorphism.c && ./a.out

#include <stdio.h>

struct Vehicle; // Forward declaration

// Define the interface/behavior using function pointers
typedef struct {
    void (*move)(struct Vehicle* self); // Function pointer for printing ID
} VehicleVTable;

// Base class (Parent)
typedef struct Vehicle {
    VehicleVTable* vtable; // Pointer to the virtual table
    int id;
    float weight;
} Vehicle;

void print_vehicle_id(Vehicle* vehicle) {
    printf("Vehicle ID: %d\n", vehicle->id);
}

// Derived class (Child) inheriting from Vehicle
typedef struct {
    Vehicle base; // Inheritance
    const char* name;
} Car;

// Implementation of the move function for Car
void drive(Vehicle* self) {
    Car* car = (Car*)self; // Cast to derived type
    printf("%s (CarID: %d) is driving.\n", car->name, car->base.id);
}

typedef struct {
    Vehicle base; // Inheritance
    const char* name;
} Plane;

// Implementation of the move function for Plane
void fly(Vehicle* self) {
    Plane* plane = (Plane*)self; // Cast to derived type
    printf("%s (PlaneID: %d) is flying.\n", plane->name, plane->base.id);
}

int main() {
    Car ford;
    ford.base.id = 1;
    ford.base.weight = 0.5;
    ford.name = "Ford";

    VehicleVTable car_vtable = { .move = drive };
    ford.base.vtable = &car_vtable; // Set the vtable for Car

    // 1. Direct Access
    printf("Car Name: %s\n", ford.name);

    // 2. Simulating Upcasting (Passing derived to a base function)
    print_vehicle_id((Vehicle*)&ford);

    // 3. Polymorphic Behavior (Calling the move function through the vtable)
    Vehicle* vehicle_ptr = (Vehicle*)&ford; // Upcast to Vehicle
    vehicle_ptr->vtable->move(vehicle_ptr); // Call the move function through the vtable

    Plane boeing;
    boeing.base.id = 2;
    boeing.base.weight = 1000.0;
    boeing.name = "Boeing";

    VehicleVTable plane_vtable = { .move = fly };
    boeing.base.vtable = &plane_vtable; // Set the vtable for Plane

    printf("Plane Name: %s\n", boeing.name);
    print_vehicle_id((Vehicle*)&boeing);

    vehicle_ptr = (Vehicle*)&boeing; // Upcast to Vehicle
    vehicle_ptr->vtable->move(vehicle_ptr); // Call the move function through the vtable

    return 0;
}