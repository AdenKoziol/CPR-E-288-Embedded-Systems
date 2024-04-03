




void main () {
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(500,500); //move forward at full speed
    while (sum < 1000) {
        oi_update(sensor_data);
        sum += sensor_data -> distance; // use -> notation since pointer
        lcd_printf(sum);
    }
    oi_setWheels(0,0); //stop
    oi_free(sensor_data); // do this once at end of main()
    }
}

