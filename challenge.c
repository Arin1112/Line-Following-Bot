//C Headers

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


//Components

#include "MPU.h"
#include "SRA18.h"
#include "TUNING.h"

//Declare the the channel array consisting of the ADC channel inputs

adc1_channel_t channel[4] = {ADC_CHANNEL_7,ADC_CHANNEL_6,ADC_CHANNEL_0,ADC_CHANNEL_3};

int adc_reading[4];
int reading[4];

void blink_task(void *arg)
{   gpio_set_direction(LED_1,GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_2,GPIO_MODE_OUTPUT);	

	while(1)
	{
		for(int i =0;i<4;i++)
		{
			adc_reading[i] = adc1_get_raw(channel[i]);
		}	

        for(int i=0;i<4;i++)
		{
			printf("RAW:%d\t",adc_reading[i]);
		}

        for(int i=0;i<4;i++)
        {
            if (adc_reading[i]>3400)
            {
                reading[i]=true;
            }
            if(adc_reading[i]<2000)
            {
                reading[i]=false;
            }
        }
        if(!(reading[0] && reading[2] && reading[1] && reading[3]))
        {
        	gpio_set_level(LED_1,1);	//Set LED1 OFF
	        gpio_set_level(LED_2,1);	//Set LED2 OFF
            
        }

         if(reading[0] && reading[2] && reading[1] && reading[3])
        {
        	gpio_set_level(LED_1,0);	//Set LED1 ON
	        gpio_set_level(LED_2,0);	//Set LED2 ON   
        }
        for(int i=0;i<4;i++)
		{
			printf("RAW:%d\t",reading[i]);
		}
		printf("\n");

	}
	
}

void app_main()
{
	/*
		Basic Function for task creation
	*/

    xTaskCreate(&blink_task,"blink task",4096,NULL,1,NULL);
}
