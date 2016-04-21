#ifndef REGISTERDEFINES_H_
#define REGISTERDEFINES_H_

//Servo registers:
#define SERVO_SET_ANGLE			0
#define SERVO_SET_ANGLE_ALL		1
#define SERVO_SET_MIN_PULSE		2
#define SERVO_SET_MAX_PULSE		3
#define SERVO_SET_PERIOD		4
#define SERVO_GET_POS			5
#define SERVO_GET_POS_ALL		6
#define SERVO_GET_INFO			7
#define SERVO_GET_INFO_ALL		8

//Stepper:
#define STEPPER_SET_POS			20
#define STEPPER_SET_FREQ		21
#define STEPPER_SET_HOLD_PWM	22
#define STEPPER_SET_MOVE_PWM	23
#define STEPPER_GET_POS			24
#define STEPPER_STEPS			25
#define STEPPER_INC				26
#define STEPPER_DEC				27
#define STEPPER_READY			28
#define STEPPER_GET_INFO		29

//Misc:
#define SHOW_LOG				69


#endif