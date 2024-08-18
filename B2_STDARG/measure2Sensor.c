#include <stdio.h>
#include <stdarg.h>

typedef enum{
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR
}SensorType;

void processSensorData(SensorType type, ...)
{
    va_list args;
    va_start(args, type);
    switch (type)
    {
        case TEMPERATURE_SENSOR:
        {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            float temperature = va_arg(args, double);

            
            printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature);
            if(numArgs > 2)
            {
                // xử lí thêm tham số nếu có 
                char* additionalInfo = va_arg(args, char*);
                printf("Additional Info:%s\n", additionalInfo);
                // int additionalInfo = va_arg(args, int);
                // printf("Additional Info:%d\n", additionalInfo);
            }
            break;
        }
        case PRESSURE_SENSOR: 
        {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            int pressure = va_arg(args, int);
            printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
            if(numArgs > 2)
            {
                // Xử lý thêm tham số nếu có
                char* unit = va_arg(args, char*);
                printf("Unit: %s\n", unit);
            }
            break;
        }     

        default:
            break;
    }

    va_end(args);
}


int main()
{
    processSensorData(TEMPERATURE_SENSOR, 3, 1, 36.5, "Room Temperature", 5, 6);
    processSensorData(PRESSURE_SENSOR, 3, 2, 101325);    
    return 0;
}