#include <stdio.h>

typedef int PIN;

typedef struct {
   PIN pinName;           // chân điều khiển
   void (*start)();       // con trỏ hàm start 
   void (*stop)();        // con trỏ hàm stop 
   void (*changeSpeed)(int speed);    // con trỏ hàm change speed  
} MotorController;


// khai báo 1 con trỏ motorCurrent 
MotorController *motorCurrent = NULL;

// Các hàm chung
void startMotor() {
   printf("Start motor at PIN %d\n", motorCurrent -> pinName);
}

void stopMotor() {
   printf("Stop motor at PIN %d\n", motorCurrent -> pinName);
}

void changeSpeedMotor(int speed) {
   printf("Change speed at PIN %d: %d\n", motorCurrent -> pinName, speed);
}

// Macro để khởi tạo GPIO và MotorController
// ví dụ nếu truyên vào INIT_MOTOR(mA, 3) 
// => pin_mA = 3; mA = {startMotor, stopMotor, changeSpeedMotor};
// khởi tạo giá trị của 3 trường tương ứng với địa chỉ của 3 hàm 

#define INIT_MOTOR(motorName, pinNumber)  \
   PIN PIN_##motorName = pinNumber;       \
   MotorController motorName = {PIN_##motorName, startMotor, stopMotor, changeSpeedMotor};

#define SET_MOTOR_CURRENT(MotorController)\
   motorCurrent = &MotorController; 

int main() {

   // Sử dụng macro để khởi tạo
   INIT_MOTOR(motorA, 1);
   INIT_MOTOR(motorB, 2);

   // Sử dụng motorA
   SET_MOTOR_CURRENT(motorA);
   motorA.start();
   motorA.changeSpeed( 50);
   motorA.stop();

   // Sử dụng motorB
   SET_MOTOR_CURRENT(motorB);
   motorB.start();
   motorB.changeSpeed(75);
   motorB.stop();

   return 0;
}
