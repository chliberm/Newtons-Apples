#ifndef GRAPHICS_OPEN_ENDED_TRIANGLE_H
#define GRAPHICS_OPEN_ENDED_TRIANGLE_H
/*
 * This is an isosceles triangle class
 */
#include "shape.h"

class Triangle : public Shape {
private:
    dimensions size;
public:
    /* Constructors */
    Triangle();
    explicit Triangle(dimensions size);
    explicit Triangle(color fill);
    explicit Triangle(point2D center);
    Triangle(color fill, point2D center);
    Triangle(double red, double green, double blue, double alpha);
    Triangle(double x, double y);
    Triangle(double red, double green, double blue, double alpha, double x, double y);
    Triangle(color fill, double x, double y);
    Triangle(double red, double green, double blue, double alpha, point2D center);
    Triangle(color fill, dimensions size);
    Triangle(point2D center, dimensions size);
    Triangle(color fill, point2D center, dimensions size);
    Triangle(double red, double green, double blue, double alpha, dimensions size);
    Triangle(double x, double y, dimensions size);
    Triangle(double red, double green, double blue, double alpha, double x, double y, dimensions size);
    Triangle(color fill, double x, double y, dimensions size);
    Triangle(double red, double green, double blue, double alpha, point2D center, dimensions size);

    /* Destructor */
    virtual ~Triangle() = default;

    /* Getters */
    dimensions getSize() const;
    double getWidth() const;
    double getHeight() const;
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    /* Setters */
    void setSize(dimensions size);
    void setSize(double width, double height);
    void setWidth(double width);
    void setHeight(double height);
    void changeSize(double deltaWidth, double deltaHeight);
    void changeWidth(double delta);
    void changeHeight(double delta);

    /* Check if two Rect objects are overlapping */
    bool isOverlapping(const Triangle &r) const;

    /* Draw */
    void draw() const override;

};


#endif //GRAPHICS_OPEN_ENDED_TRIANGLE_H
