/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "tween.h"

#include "timer.h"

//Easing functions
static fixed_t Easing_CalculateValue(Tween* tween)
{
	//Normalize the elapsed time to use delta time in seconds
	fixed_t normalized_time = FIXED_DIV(tween->elapsed_time, tween->time);
	
	//Calculate the easing value based on the specified easing method
	switch (tween->method)
	{
		case EASING_LINEAR:
			//Linear easing: progress linearly with time
			return normalized_time;
		break;
		case EASING_IN:
			//Quadratic easing in: start slowly and accelerate
			return FIXED_MUL(normalized_time, normalized_time);
		break;
		case EASING_OUT:
			//Quadratic easing out: start quickly and decelerate
			return FIXED_UNIT - FIXED_MUL(FIXED_UNIT - normalized_time, FIXED_UNIT - normalized_time);
		break;
	}
	
	return FIXED_UNIT; //Default to max value if no easing method specified
}

//Tween functions
void Tween_Init(Tween* tween, fixed_t initial_value, fixed_t final_value, fixed_t time, EasingsMethod method, u8 flags)
{
	//Initialize tween state
	tween->initial_value = initial_value;
	tween->final_value = final_value;
	tween->time = time;
	tween->method = method;
	tween->flags = flags;
	tween->elapsed_time = 0;
	
	//Set the current value to the initial or final value depending of the backward flag
	tween->current_value = (tween->flags & TWEEN_FLAGS_BACKWARD) ? final_value : initial_value;
}

void Tween_Update(Tween* tween)
{
	//Update the current value based on the easing function
	if (tween->flags & TWEEN_FLAGS_BACKWARD)
		tween->current_value = tween->final_value + FIXED_MUL((tween->initial_value - tween->final_value), Easing_CalculateValue(tween));
	else
		tween->current_value = tween->initial_value + FIXED_MUL((tween->final_value - tween->initial_value), Easing_CalculateValue(tween));
	
	//Update the elapsed time since the tween started
	tween->elapsed_time += timer_dt;
	
	//Reset the elapsed time if the loop flag is set, otherwise stop updating the tween
	if (tween->elapsed_time > tween->time)
	{
		if (tween->flags & TWEEN_FLAGS_LOOP)
			tween->elapsed_time = 0;
		else
			tween->elapsed_time = tween->time;
	}
}
