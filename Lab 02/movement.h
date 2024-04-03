#ifndef HEADER_FILE
#define HEADER_FILE


#include "open_interface.h"


double move_forward (oi_t *sensor_data, double distance_mm);
double turn_right(oi_t *sensor_data, double degrees);
double turn_left(oi_t *sensor_data, double degrees);
double move_back (oi_t *sensor_data, double distance_mm);

#endif
