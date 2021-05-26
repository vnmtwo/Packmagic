#ifndef CONFIGURATION_H
#define CONFIGURATION_H
	#define DEVICES 				20
	#define COLOR_VALUE_LIMIT 		0.8
	#define STASSID 				"vnmhome"
	#define STAPSK  				"vnm159wifi"
	#define REMOTE_PORT 			8888

//base position program
	#define BASE_COLOR_H 			0.15
	#define BASE_COLOR_S			1
	#define BASE_COLOR_V 			COLOR_VALUE_LIMIT

//wakeup program
	#define WAKEUP_MAX_RANDOM_T	300
	#define WAKEUP_V_SPEED 		0.004
	#define WAKEUP_H_SPEED 		0.004
	#define WAKEUP_WARM_HUE 	BASE_COLOR_H
	#define WAKEUP_BLUE_LIGHT_H 0.5
#endif