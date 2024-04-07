/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef PSXF_GUARD_TWEEN_H
#define PSXF_GUARD_TWEEN_H

#include "psx.h"

#include "fixed.h"

#define TWEEN_FLAGS_LOOP		(1 << 1) //If set, the Tween will restart from the initial value after reaching the final value
#define TWEEN_FLAGS_BACKWARD	(1 << 2) //If set, the Tween will play in reverse from final value to initial value

//Easing methods enumeration
typedef enum
{
	EASING_LINEAR,	//Linear easing: progress linearly with time
	EASING_IN, 		//Quadratic easing in: start slowly and accelerate
	EASING_OUT, 	//Quadratic easing out: start quickly and decelerate
	
} EasingsMethod;

//Tween struct
typedef struct
{
	fixed_t initial_value; 	//Initial value of the tween
	fixed_t final_value; 	//Final value of the tween
	fixed_t current_value; 	//Current value of the tween
	EasingsMethod method;  	//Easing method used for the tween
	fixed_t time; 			//Total duration of the tween in seconds
	u8 flags;				//The flags of the tween
	
	//"Private" members (You probably not will need use these members)
	
	fixed_t elapsed_time;	 //Elapsed time since the tween started
} Tween;

//Tween functions
void Tween_Init(Tween* tween, fixed_t initial_value, fixed_t final_value, fixed_t time, EasingsMethod method, u8 flags);
void Tween_Update(Tween* tween);

#endif
