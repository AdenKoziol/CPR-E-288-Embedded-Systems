#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "uart.h"
#include "Timer.h"
#include "lcd.h"
#include <math.h>
#include <movement.h>
#include <open_interface.h>

/**
 * main.c
 */
int main(void)
{
    int ir1, ir2, ir3;
    int averages[180];
    int angles[180];
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data);
	timer_init();
	lcd_init();
	cyBOT_init_Scan(0b0111);
	//cyBOT_SERVO_cal();
	right_calibration_value = 248500;
	left_calibration_value = 1214500;
    oi_free(sensor_data);



	int i;

	cyBOT_Scan_t scan;

	for(i=0; i <= 180; i += 3){
	    cyBOT_Scan(i, &scan);
	    ir1 = scan.IR_raw_val;
	    cyBOT_Scan(i, &scan);
        ir2 = scan.IR_raw_val;
        cyBOT_Scan(i, &scan);
        ir3 = scan.IR_raw_val;
        averages[i/3] = (ir1+ir2+ir3) / 3;
        angles[i/3] = i;

	}


	int k;
    int startingAngle;
    int endingAngle;
    int midpoints[20];
    int midpointIndex = 0;
    float dist, dist1, distAvg;
    double linearWidth[20];

    for(k = 0; k < sizeof(angles); k++)
    {
        if(averages[k] >= 800)
        {
            startingAngle = angles[k];
            endingAngle = -1;
            while(averages[k + 1] - averages[k] <= 100 && averages[k + 1] - averages[k] >= -100)
            {
                endingAngle = angles[k+1];
                k++;
            }
            if(endingAngle != -1)
            {
                if((endingAngle + startingAngle) / 2 > 0 && (endingAngle + startingAngle) / 2 < 181)
                {
                    midpoints[midpointIndex] = (endingAngle + startingAngle) / 2;
                    cyBOT_Scan(midpoints[midpointIndex], &scan);
                    dist = scan.sound_dist;
                    cyBOT_Scan(midpoints[midpointIndex], &scan);
                    dist1 = scan.sound_dist;
                    distAvg = (dist + dist1) / 2.0;
                    linearWidth[midpointIndex] = 2.0 * 3.14 * distAvg * ((double)(endingAngle - startingAngle) / 360.0) * 100.0;
                    midpointIndex++;
                }
            }
        }
    }
    int l;
    for(l = 0; l <= midpointIndex; l++)
    {
        cyBOT_Scan(midpoints[l], &scan);
    }

    double minWidth = 100000;
    int minIndex = -1;
    for(i = 0; i <= midpointIndex; i++){
        if(linearWidth[i] < minWidth){
            minWidth = linearWidth[i];
            minIndex = i;
        }

    }


    cyBOT_Scan(midpoints[minIndex], &scan);
    double distan = scan.sound_dist;

    if(midpoints[minIndex] > 90)
    {
        turn_left(sensor_data, (midpoints[minIndex] - 115));
    }
    else
    {
        turn_right(sensor_data, 75 - midpoints[minIndex]);
    }

    move_forward (sensor_data, (distan * 10.0) - 125);


	uart_init();

	char message[50];
	char message1[] = "\n\rAngle              Distance\n\r";
	int j;
	for(j = 0; j < strlen(message1); j++)
    {
        uart_sendChar(message1[j]);
    }

	for(i = 0; i <= 60; i++)
	{
	    sprintf(message, "%d                  %d\n\r", angles[i], averages[i]);
	    for(j = 0; j < strlen(message); j++)
        {
            uart_sendChar(message[j]);
        }
	}



	for(i = 0; i < midpointIndex; i++)
	    {
	        sprintf(message, "%d  %lf\n\r", midpoints[i], linearWidth[i]);
	        for(j = 0; j < strlen(message); j++)
	        {
	            uart_sendChar(message[j]);
	        }
	    }




	oi_free(sensor_data);
	return 0;


}
