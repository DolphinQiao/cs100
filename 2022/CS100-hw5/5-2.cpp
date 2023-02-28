#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <iomanip>

const double PI = 3.14159;

/***********************************************************************
* Declaration/Definition of the base-class Shape *
***********************************************************************/
class Shape {
public:
    // constructors and destructor
    Shape();
    ~Shape();
    // Accessors; you should decide which should be virtual or pure virtual.
    virtual double CalculateArea() const =0;
    virtual double CalculatePerimeter() const =0;
    virtual int NumberCorners() const =0;
private:
    // member variables;
};
std::list<Shape*> list1;
Shape::Shape(){}
Shape::~Shape(){}
/***********************************************************************
* Declaration/Definition of the child-classes *
***********************************************************************/
class Rectangle:public Shape{
public:
    int m_a,m_b;
    Rectangle(double a,double b):m_a(a),m_b(b){}
    virtual double CalculateArea()const{
        return m_a*m_b;
    }
    virtual double CalculatePerimeter() const 
    {
        return 2.0*(m_a+m_b);
    }
    virtual int NumberCorners() const
    {
        return 4;
    }
};
class Square:public Shape{
public:
    int m_a;
    Square(double a):m_a(a){}
    virtual double CalculateArea() const
    {
        return m_a*m_a;
    }
    virtsual double CalculatePerimeter() const
    
    {
        return 4.0f*m_a;
    }
    virtual int NumberCorners() const
    {
        return 4;
    }
};
class Triangle:public Shape{
public:
    int m_a,m_b;
    Triangle(double a,double b):m_a(a),m_b(b){}
    virtual double CalculateArea() const
    {
        return m_a*m_b/2.0f;
    }
    virtual double CalculatePerimeter() const
    {
        return m_a+m_b+sqrt(m_a*m_a+m_b*m_b);
    }
    virtual int NumberCorners() const
    {
        return 3;
    }
};
class Circle:public Shape{
public:
    int m_r;
    Circle(double r):m_r(r){}
    ~Circle(){};
    virtual double CalculateArea() const
    {
        return m_r*m_r*PI;
    }
    virtual double CalculatePerimeter() const
    {
        return 2.0f*m_r*PI;
    }
    virtual int NumberCorners() const
    {
        return 0;
    }
};

/************************************************************************
* Main Function which is creating/reporting database (do not change!) *
************************************************************************/
int main() {
    //initialize an empty list of shapes
    std::list<Shape*> shapeDatabase;
    //interact with the user: ask the user to enter shapes one by one
    while (1) {
        //print instructions as to how to enter a shape
        std::cout << "Enter a type (Circle, Triangle, Square, or Rectangle) ";
        std::cout << "and one or two size parameters, ";
        std::cout << "separated with blank spaces:\n";
        double size1;
        double size2;
        //check which shape has been requested and store in the database
        std::string shapeType;
        std::cin >> shapeType;
        if (shapeType == std::string("Circle")) {
            std::cin >> size1;
            shapeDatabase.push_back( new Circle(size1) );
        }
        else if (shapeType == std::string("Triangle")) {
            std::cin >> size1 >> size2;
            shapeDatabase.push_back( new Triangle(size1,size2) );
        }
        else if (shapeType == std::string("Square")) {
            std::cin >> size1;
            shapeDatabase.push_back( new Square(size1) );
        }
        else if (shapeType == std::string("Rectangle")) { 
            std::cin >> size1 >> size2;
            shapeDatabase.push_back( new Rectangle(size1,size2) );
        }
        else {
            std::cout << "Unrecognized shape!!\n";
        }
        //check if the user wants to add more shapes
        std::cout << "Do you want to add more shapes? (Enter Y or N)\n";
        std::string answer;
        std::cin >> answer;
        if (answer != std::string("Y"))
            break;
    }
    //iterate through the list and output the area, perimeter,
    //and number of corners of each entered shape
    std::list<Shape *>::iterator it = shapeDatabase.begin();
    int shapeCounter = 0;
    while (it != shapeDatabase.end()) {   
        std::cout << "Properties of shape " << shapeCounter++ << ":\n";
        std::cout << "Area: " << std::setprecision(5) << (*it)->CalculateArea() << "\n";
        std::cout << "Perimeter: " << std::setprecision(5) << (*it)->CalculatePerimeter() << "\n";
        std::cout << "Corners: " << (*it)->NumberCorners() << "\n";
        std::cout << std::endl;
        it++;
    }

    it = shapeDatabase.begin();
    while (it != shapeDatabase.end()) {
        delete (*it);
        it = shapeDatabase.erase(it);
    }
    
    return 0;
}