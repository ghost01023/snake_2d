#ifndef FOOD_H
#define FOOD_H


#include <iostream>
using namespace std;

enum ShapeType {SQUARE, CIRCLE, TRIANGLE};

typedef struct {
    float *food_coords;
    float center[6];
    int size;
    ShapeType shape;
} food;


food generate_food(ShapeType shape);

void print_food_details(food f);

#endif // FOOD_H