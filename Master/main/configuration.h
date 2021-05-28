#ifndef CONFIGURATION_H
#define CONFIGURATION_H
	#define DEVICES 				20
	#define COLOR_VALUE_LIMIT 		0.8
	#define STASSID 				"vnmhome"
	#define STAPSK  				"vnm159wifi"
	#define REMOTE_PORT 			8888
//buttons
	#define BUTTON_PROGRAM00_PIN		5 //D1

//base position program
	#define BASE_COLOR_H 			0.15
	#define BASE_COLOR_S			1.0
	#define BASE_COLOR_V 			COLOR_VALUE_LIMIT

//wakeup program
	#define WAKEUP_MAX_RANDOM_T			300
	#define WAKEUP_V_SPEED 				0.004
	#define WAKEUP_H_SPEED 				0.004
	#define WAKEUP_WARM_HUE 			BASE_COLOR_H
	#define WAKEUP_BLUE_LIGHT_H 		0.5

//wakeup nap program
	#define WAKEUP_NAP_MAX_RANDOM_T			WAKEUP_MAX_RANDOM_T
	#define WAKEUP_NAP_V_SPEED 				0.003
	#define WAKEUP_NAP_H_SPEED 				0.004
	#define WAKEUP_NAP_WARM_HUE 			WAKEUP_WARM_HUE
	#define WAKEUP_NAP_BLUE_LIGHT_H 		WAKEUP_BLUE_LIGHT_H
	#define WAKEUP_NAP_SIN_DIV				24.0
	#define WAKEUP_NAP_SIN_ATT_SPEED		0.000015
	#define WAKEUP_NAP_SIN_ATT_START		0.5

//applause program
	#define APLLAUSE_COLOR_H	WAKEUP_BLUE_LIGHT_H
	#define APLLAUSE_COLOR_S	1.0
	#define APLLAUSE_SIN_DIV	10.0

//rhytm program
	#define RHYTM_COLOR_H		WAKEUP_BLUE_LIGHT_H
	#define RHYTM_COLOR_S		1.0
	#define RHYTM_SIN_DIV		2.0

//crazy_time program
	#define CRAZY_TIME_COLOR_S		1.0
	#define CRAZY_TIME_SPEED		0.02

//countdown program
	#define COUNTDOWN_COLOR_H 		WAKEUP_BLUE_LIGHT_H
	#define COUNTDOWN_COLOR_S		1.0
	#define COUNTDOWN_LOW_V			0.3
	#define COUNTDOWN_COUNT			10
	#define COUNTDOWN_SINE_DIV		24.0

//dualogue program
	#define DIALOGUE_COLOR_H	WAKEUP_BLUE_LIGHT_H
	#define DIALOGUE_COLOR_S	1.0
	#define DIALOGUE_V_SPEED	0.02
	#define DIALOGUE_MAX_V		COLOR_VALUE_LIMIT
	#define DIALOGUE_PAUSE		90	

//lamp program
	#define LAMP_COLOR_H	0.08
	#define LAMP_COLOR_S	1.0
	#define LAMP_COLOR_V	COLOR_VALUE_LIMIT

//ten program
	#define TEN_FIRSTLAMP_H				0.55
	#define TEN_FIRSTLAMP_S				1.0
	#define TEN_MAX_RANDOM_T			WAKEUP_MAX_RANDOM_T

	#define TEN_OTHERLAMP_H				TEN_FIRSTLAMP_H
	#define TEN_OTHERLAMP_S				TEN_FIRSTLAMP_S
	#define TEN_OTHERLAMP_V_SPEED		0.001

	#define TEN_FIRSTLAMP_V_SPEED			0.033
	#define TEN_FIRSTLAMP_H_FLOAT_T			255 //frames
	#define TEN_FIRSTLAMP_H_FLOAT_AMP		0.05
	#define TEN_FIRSTLAMP_H_FLOAT_SIN_DIV	15.0 //must be float

#endif