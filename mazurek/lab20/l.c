#include <stdio.h>
#include <stdlib.h>
 
float systemp, millideg;
FILE *thermal;
int n;

get_temp(){
 
        thermal = fopen("/sys/class/hwmon/hwmon3/temp1_input","r");
        n = fscanf(thermal,"%f",&millideg);
        fclose(thermal);
        systemp = millideg / 1000;
 
        return printf("CPU temperature is %f degrees C\n",systemp);
}
 
int main()
{
	for(int i = 0; i < 20; i++)
    	{
        	unsigned long long next = 0, c = 0, first = 0, second = 1;
 
        	for(c = 0; c < 2000000000; c++)
        	{
            		if(c<=1)
                		next = c;
            		else
            		{
                		next = first + second;
                		first = second;
                		second = next;
            		}
        	}
 
        printf("obliczono: %lld\n\n", next);
	get_temp();
	}
}