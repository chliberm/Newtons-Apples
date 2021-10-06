#include "graphics.h"
#include "triangle.h"
#include <iostream>
using namespace std;


Triangle::Triangle() : Shape(), size({0, 0}) {
}

Triangle::Triangle(dimensions size) : Shape() {
    setSize(size);
}

Triangle::Triangle(color fill) : Shape(fill), size({0, 0}) {
}

Triangle::Triangle(point2D center) : Shape(center), size({0, 0}) {
}

Triangle::Triangle(color fill, point2D center) : Shape(fill, center), size({0, 0}) {
}

Triangle::Triangle(double red, double green, double blue, double alpha) : Shape(red, green, blue, alpha), size({0, 0}) {
}

Triangle::Triangle(double x, double y) : Shape(x, y), size({0, 0}) {
}

Triangle::Triangle(double red, double green, double blue, double alpha, double x, double y) : Shape(red, green, blue, alpha, x, y), size({0, 0}) {
}

Triangle::Triangle(color fill, double x, double y) : Shape(fill, x, y), size({0, 0}) {
}

Triangle::Triangle(double red, double green, double blue, double alpha, point2D center) : Shape(red, green, blue, alpha, center), size({0, 0}) {
}

Triangle::Triangle(color fill, dimensions size) : Shape(fill) {
    setSize(size);
}

Triangle::Triangle(point2D center, dimensions size) : Shape(center) {
    setSize(size);
}

Triangle::Triangle(color fill, point2D center, dimensions size) : Shape(fill, center) {
    setSize(size);
}

Triangle::Triangle(double red, double green, double blue, double alpha, dimensions size) : Shape(red, green, blue, alpha) {
    setSize(size);
}

Triangle::Triangle(double x, double y, dimensions size) : Shape(x, y) {
    setSize(size);
}

Triangle::Triangle(double red, double green, double blue, double alpha, double x, double y, dimensions size) : Shape(red, green, blue, alpha, x, y) {
    setSize(size);
}

Triangle::Triangle(color fill, double x, double y, dimensions size) : Shape(fill, x, y) {
    setSize(size);
}

Triangle::Triangle(double red, double green, double blue, double alpha, point2D center, dimensions size) : Shape(red, green, blue, alpha, center) {
    setSize(size);
}

dimensions Triangle::getSize() const {
    return size;
}

double Triangle::getWidth() const {
    return size.width;
}

double Triangle::getHeight() const {
    return size.height;
}

double Triangle::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Triangle::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Triangle::getTopY() const {
    return center.y - (size.height / 2.0);
}

double Triangle::getBottomY() const {
    return center.y + (size.height / 2.0);
}

void Triangle::setSize(dimensions size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Triangle::setSize(double width, double height) {
    setSize({width, height});
}

void Triangle::setWidth(double width) {
    setSize({width, size.height});
}

void Triangle::setHeight(double height) {
    setSize({size.width, height});
}

void Triangle::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Triangle::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Triangle::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}

/*
// Implement this method
bool Triangle::isOverlapping(const Triangle &r) const {
    bool overlap = true;
    // There are only two cases when rectangles are *not* overlapping:
    // 1. when one is to the left of the other
    if (getRightX() < r.getLeftX() || getLeftX() > r.getRightX()) {
        overlap = false;
    }
    // 2. when one is above the other
    if (getBottomY() < r.getTopY() || getTopY() > r.getBottomY()) {
        overlap = false;
    }
    return overlap;
}
*/

// Implement this method
void Triangle::draw() const {
    // Don't forget to set the color to the fill field
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_TRIANGLES);
    glVertex2d(getLeftX(), getBottomY());
    glVertex2d(getRightX(), getBottomY());
    glVertex2d(getCenterX() , getTopY());
    glEnd();

}