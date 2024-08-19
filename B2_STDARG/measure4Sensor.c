#include <stdio.h>
#include <stdarg.h>

typedef enum{
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR,
    HUMIDITY_SENSOR,
    LIGHT_SENSOR
}SensorType;


#define HANDLE_DATA(type)\
    char sensor[] = #type;\
    int numArgs = va_arg(args, int);\
    i++;\
    printf("Information about %s:\n", sensor);\
    for(i; i <= numArgs; i++)\
    {\
        if(i == 1)\
        {\
            int sensorId = va_arg(args, int);\
            printf("ID: %d\n", sensorId);\
        }\
        else if(i == 2)\
        {\
            float dataSensor = va_arg(args, double);\
            printf("DATA SENSOR: %.2f\n", dataSensor);\
        }\
        else if( i == 3)\
        {\
            char* parameter3 = va_arg(args, char*);\
            printf("parameter 3 Info: %s\n", parameter3);\
        }\
        else if(i == 4)\
        {\
            char* parameter4 = va_arg(args, char*);\
            printf("parameter 4 Info: %s\n", parameter4);\
        }\
        else if( i == 5)\
        {\
            int parameter5 = va_arg(args, int);\
            printf("parameter 5 Info: %d\n", parameter5);\
        }\
    }\
    printf("\n"); 


void processSensorData(SensorType type, ...)
{
    va_list args;
    va_start(args, type);
    int i = 0;

    switch (type)
    {
        case TEMPERATURE_SENSOR:
        {
            HANDLE_DATA(TEMPERATURE_SENSOR);
            break;
        }
        case PRESSURE_SENSOR: 
        {
            HANDLE_DATA(PRESSURE_SENSOR);
            break;
        }     

        case HUMIDITY_SENSOR: 
        {
            HANDLE_DATA(HUMIDITY_SENSOR);
            break;
        }   

        case LIGHT_SENSOR: 
        {
            HANDLE_DATA(LIGHT_SENSOR);
            break;
        }   

        default:
            break;
    }

    va_end(args);
}


int main()
{
    processSensorData(TEMPERATURE_SENSOR, 5, 1, 36.5, "Room Temperature", "floor 2", 45);
    processSensorData(PRESSURE_SENSOR, 3, 2, 101325.0, "home1");    
    processSensorData(HUMIDITY_SENSOR, 4, 40, 90.0, "home2", "yard"); 
    processSensorData(LIGHT_SENSOR, 3, 23, 90.0, "home3");
    return 0;
}