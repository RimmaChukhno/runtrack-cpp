#include <iostream>
#include <string>
using namespace std;

// Classe de base
class Shape {
public:
    virtual void draw() {
        cout << "Je suis une forme." << endl;
    }
};

// Classes dérivées
class Circle : public Shape {
public:
    void draw() {
        cout << "Je suis un cercle." << endl;
    }
};

class Square : public Shape {
public:
    void draw() {
        cout << "Je suis un carré." << endl;
    }
};

class Triangle : public Shape {
public:
    void draw() {
        cout << "Je suis un triangle." << endl;
    }
};

// Classe ShapeFactory
class ShapeFactory {
public:
    static Shape* createShape(string type) {
        if (type == "circle") {
            return new Circle();
        } 
        else if (type == "square") {
            return new Square();
        } 
        else if (type == "triangle") {
            return new Triangle();
        } 
        else {
            return nullptr; // si le type n’existe pas
        }
    }
};

// Programme principal
int main() {
    Shape* s1 = ShapeFactory::createShape("circle");
    Shape* s2 = ShapeFactory::createShape("square");
    Shape* s3 = ShapeFactory::createShape("triangle");
    Shape* s4 = ShapeFactory::createShape("hexagon"); // type inconnu

    if (s1) s1->draw();
    if (s2) s2->draw();
    if (s3) s3->draw();

    if (!s4)
        cout << "Type de forme inconnu." << endl;

    // Libération mémoire
    delete s1;
    delete s2;
    delete s3;

    return 0;
}
