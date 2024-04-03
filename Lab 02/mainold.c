#include "open_interface.h"
#include "movement.h"


void main () {
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    // the following code could be put in function move_forward()
    move_forward(sensor_data, 2000);



    oi_free(sensor_data); // do this once at end of main()
    }
