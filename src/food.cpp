#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>



#include "food.h"


// for trinalge, generate middle point
// then down, right for right, inverse for left vertex and up for top vertex


food generate_food(ShapeType shape) {
    // generate random x and y
    srand(time(0));
    float random_point_x = rand() / (float)RAND_MAX;
    // int random_sign = rand() % 2;
    // float random_y = rand() / (float)RAND_MAX;
    // if (random_sign == 0 && random_point_x != 0) {
    //     random_point_x *= -1;
    // }

    float random_point_y = rand() / (float)RAND_MAX;
    // random_sign = rand() % 2;
    // if (random_sign == 0 && random_point_y != 0) {
    //     random_point_y *= -1;
    // }

    // random_sign = rand() % 2;
    // if (random_sign == 0) {
    //     random_y *= -1;
    // }

    // in case point generates at total edge of x or y axis
    if (random_point_x == -1.0f) {
        random_point_x += 0.1;
    } else if (random_point_x == 1.0f) {
        random_point_x -= 0.1;
    }
    if (random_point_y == -1.0f) {
        random_point_y += 0.1;
    } else if (random_point_y == 1.0f) {
        random_point_y -= 0.1;
    }

    

    cout << "random_point_x is " << random_point_x <<" and random_point_y is " << random_point_y << endl;



    food new_food;
    new_food.shape = shape;
    new_food.center[0] = random_point_x;
    new_food.center[1] = random_point_y;

    if (shape == TRIANGLE) {
        // float *f = new_food.food_coords;
        new_food.food_coords = (float *)malloc(sizeof(float) * 9);
        //bottom left
        new_food.food_coords[0] = random_point_x - 0.1;
        new_food.food_coords[1] = random_point_y - 0.1;
        new_food.food_coords[2] = 1.0;
        cout << "bottom left is " << new_food.food_coords[0] << " " << new_food.food_coords[1] << endl;
        //top
        new_food.food_coords[3] = random_point_x;
        new_food.food_coords[4] = random_point_y + 0.1;
        new_food.food_coords[5] = 1.0;
        cout << "top is " << new_food.food_coords[3] << " " << new_food.food_coords[4] << endl;
        //bottom right
        new_food.food_coords[6] = random_point_x + 0.1;
        new_food.food_coords[7] = random_point_y + 0.1;
        new_food.food_coords[8] = 1.0;
        cout << "bottom right is " << new_food.food_coords[6] << " " << new_food.food_coords[7] << endl;
    } else if(shape == SQUARE) {
        new_food.food_coords = (float *)malloc(sizeof(float) * 12);
        //top left
        new_food.food_coords[0] = random_point_x - 0.1;
        new_food.food_coords[1] = random_point_y + 0.1;
        new_food.food_coords[2] = 1.0f;
        //top right
        new_food.food_coords[3] = random_point_x + 0.1;
        new_food.food_coords[4] = random_point_y + 0.1;
        new_food.food_coords[5] = 1.0f;
        //bottom left
        new_food.food_coords[6] = random_point_x - 0.1;
        new_food.food_coords[7] = random_point_y - 0.1;
        new_food.food_coords[8] = 1.0f;
        //bottom right
        new_food.food_coords[9] = random_point_x + 0.1;
        new_food.food_coords[10] = random_point_y - 0.1;
        new_food.food_coords[11] = 1.0f;
        
        // new_food.center
    }
    return new_food;
}


void print_food_details(food f) {
    cout << "Shape of food is ";
    switch(f.shape) {
        case TRIANGLE:
        cout << "Triangle";
        break;
        case SQUARE:
        cout << "Square";
        break;
        case CIRCLE:
        cout << "Circle";
        break;
    }
    cout << endl;
    cout << "Coords of the shape are:\t";
    if (f.shape == TRIANGLE) {
        for (int i = 0; i < 9; i++) {
            cout << f.food_coords[i] << "\t";
        }
        cout << endl;
    }
}