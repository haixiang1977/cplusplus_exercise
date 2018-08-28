// generate the crash log:
// g++ -g -O0 test46.cpp -o test46.out
// developer@developer-desktop:test$ ./test46.out
// pure virtual method called
// terminate called without an active exception
// Aborted

#include <stdio.h>
#include <stdlib.h>

#define PI 3.14

class Shape {
 private:
    double ValuePerSquareUnit;

 protected:
    Shape(double value) : ValuePerSquareUnit(value) {
        printf("create shape, Value %f\n", getValue());
    }

 public:
    virtual double area() const = 0;

    double getValue() const {
        return ValuePerSquareUnit * area();
    }

    virtual ~Shape() {
        printf("Shape::~Shape() is called\n");
    }

    double getValuePerSquareUnit() const {
        return ValuePerSquareUnit;
    }
};

class Rectangle : public Shape {
 private:
    double Width;
    double Height;

 public:
    Rectangle(double w, double h, double v) : Shape(v), Width(w), Height(h) {
        
    }

    virtual ~Rectangle() {
        printf("Rectangle::~Rectangle() is called\n");
    };

    virtual double area() const {
        return Width * Height;
    }
};

class Circle : public Shape {
 private:
    double Radius;

 public:
    Circle(double r, double v) : Shape(v), Radius(r) {
        
    }

    virtual ~Circle() {
        printf("Circle::~Circle() is called");
    };

    virtual double area() const {
        return PI * Radius * Radius;
    }
};

int main() {
    Rectangle* pr = new Rectangle(30, 20, 10);

    Circle* pc = new Circle(15, 10);

    //invoke Rectangle::area()
    printf("rectangle: area = %.2f, PerSquareUnit = %.2f, value = %.2f\n", 
        pr->area(), pr->getValuePerSquareUnit(), pr->getValue());

    //invoke Circle::area()
    printf("circle   : area = %.2f, PerSquareUnit = %.2f, value = %.2f\n", 
        pc->area(), pc->getValuePerSquareUnit(), pc->getValue());

    Shape* shape;
    shape = pr;
    printf("rectangle: area = %.2f, PerSquareUnit = %.2f, value = %.2f\n", 
        shape->area(), shape->getValuePerSquareUnit(), shape->getValue());
 
    shape = pc;
    printf("circle   : area = %.2f, PerSquareUnit = %.2f, value = %.2f\n", 
        shape->area(), shape->getValuePerSquareUnit(), shape->getValue());

    return 0;
}
