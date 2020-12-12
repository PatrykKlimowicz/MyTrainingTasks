#include <stdio.h>
#include <stdlib.h>

float get_cpu_temperature() {
        FILE *f = fopen("/sys/class/hwmon/hwmon4/temp1_input", "r");

	float milideg;
	fscanf(f, "%f", &milideg);
        fclose(f);
        float cpu_temp = milideg / 1000;

	return cpu_temp;
}

int get_fan_1_status() {
        FILE *f = fopen("/sys/class/hwmon/hwmon4/fan1_input", "r");

        int status;
        fscanf(f, "%d", &status);
        fclose(f);

        return status;
}

int get_fan_2_status() {
        FILE *f = fopen("/sys/class/hwmon/hwmon4/fan2_input", "r");

        int status;
        fscanf(f, "%d", &status);
        fclose(f);

        return status;
}


int main() {
	printf("CPU temp: %f\n", get_cpu_temperature());
        printf("Fan1 status: %d rpm\n", get_fan_1_status());
        printf("Fan2 status: %d rpm\n", get_fan_2_status());
	for(int j = 0; j < 20; j++)
    	{
		double PI = 4;
		int flag = 0;
		for (unsigned long long i = 3; i < 2209900000; i+= 2) {
			if (flag)
				PI += 4.0 / i;
			else
				PI -= 4.0 / i;

			flag = !flag;
		}

        	printf("Gregory Lebnitz PI: %0.30f\n\n", PI);
		printf("CPU temp: %f\n", get_cpu_temperature());
		printf("Fan1 status: %d rpm\n", get_fan_1_status());
		printf("Fan2 status: %d rpm\n", get_fan_2_status());
	}
}
