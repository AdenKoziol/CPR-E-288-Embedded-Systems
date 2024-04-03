#include "open_interface.h"
#include "movement.h"
#include <stdio.h>

double move_forward (oi_t *sensor_data, double distance_mm){
    double sum = 0;
    oi_setWheels(250, 250);
    while (sum < distance_mm) {
            oi_update(sensor_data);
            sum += sensor_data -> distance; // use -> notation since pointer
            if(sensor_data -> bumpLeft || sensor_data -> bumpRight){
                if(sensor_data -> bumpLeft){
                    move_back(sensor_data, 150);
                    sum -= 150;
                    turn_right(sensor_data, 70);
                    move_forward(sensor_data, 200);
                    turn_left(sensor_data, 60);
                    move_forward(sensor_data, 200);
                    turn_left(sensor_data, 50);
                    move_forward(sensor_data, 75);
                    sum += 200;
                }
                else{
                    move_back(sensor_data, 150);
                    sum -= 150;
                    turn_left(sensor_data, 70);
                    move_forward(sensor_data, 200);
                    turn_right(sensor_data, 60);
                    move_forward(sensor_data, 200);
                    turn_right(sensor_data, 50);
                    move_forward(sensor_data, 75);
                    sum += 200;
                }
                oi_setWheels(250, 250);
            }

    }
    oi_setWheels(0,0);
    return 0;
}
double turn_right(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(-250, 250);
    while (sum > degrees * -1) {
            oi_update(sensor_data);
            sum += sensor_data -> angle; // use -> notation since pointer
    }
    oi_setWheels(0,0);
    return 0;
}
double turn_left(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(250, -250);
    while (sum < degrees * 1) {
            oi_update(sensor_data);
            sum += sensor_data -> angle; // use -> notation since pointer
    }
    oi_setWheels(0,0);
    return 0;
}
double move_back (oi_t *sensor_data, double distance_mm){
    double sum = 0;
    oi_setWheels(-250, -250);
    while (sum > distance_mm * -1) {
            oi_update(sensor_data);
            sum += sensor_data -> distance; // use -> notation since pointer
    }
    oi_setWheels(0,0);
    return 0;
}
