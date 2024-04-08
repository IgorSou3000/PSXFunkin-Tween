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
	//Divide the elapsed time by the desired time to normalize it
	fixed_t time = FIXED_DIV(tween->elapsed_time, tween->time);
	
	//Calculate the easing value based on the specified ease
	switch (tween->ease)
	{
		case EASING_LINEAR:
			//Linear easing: progress linearly with time
			return time;
		break;
		case EASING_QUAD_IN:
			//Quadratic easing in: start slowly and accelerate
			return FIXED_MUL(time, time);
		break;
		case EASING_QUAD_OUT:
			//Quadratic easing out: start quickly and decelerate
			return time * 2 - FIXED_MUL(time, time);
		break;
		case EASING_QUAD_IN_OUT:
			if (time < FIXED_UNIT >> 1)
				return FIXED_MUL(FIXED_MUL(FIXED_UNIT << 1, time), time); //Quadratic easing in
			else
				return FIXED_UNIT - FIXED_MUL(FIXED_DEC(2,1), FIXED_MUL(time - FIXED_UNIT, time - FIXED_UNIT)); //Quadratic easing out
		break;
	}
	
	return FIXED_UNIT; //Default to max value if no easing method specified
}

//Tween functions
void Tween_InitWithValue(Tween* tween, fixed_t initial_value, fixed_t final_value, fixed_t time, Eases ease, u8 flags)
{
	//Initialize tween state
	tween->value_pointer = NULL;
	tween->initial_value = initial_value;
	tween->final_value = final_value;
	tween->time = time;
	tween->ease = ease;
	tween->flags = flags;
	tween->elapsed_time = 0;
	
	//Set the current value to the initial or final value depending of the backward flag
	tween->current_value = (tween->flags & TWEEN_FLAGS_BACKWARD) ? final_value : initial_value;
}

void Tween_InitWithVariable(Tween* tween, fixed_t* valuep, fixed_t final_value, fixed_t time, Eases ease, u8 flags)
{
	Tween_InitWithValue(tween, *valuep, final_value, time, ease, flags);
	
	//Initialize tween pointers
	tween->value_pointer = valuep;
	*tween->value_pointer = tween->current_value;
}

void Tween_Tick(Tween* tween)
{
	if (tween->value_pointer != NULL)
		*tween->value_pointer = tween->current_value;
	
	//Update the current value based on the easing function
	if (tween->flags & TWEEN_FLAGS_BACKWARD)
		tween->current_value = tween->final_value + FIXED_MUL((tween->initial_value - tween->final_value), Easing_CalculateValue(tween));
	else
		tween->current_value = tween->initial_value + FIXED_MUL((tween->final_value - tween->initial_value), Easing_CalculateValue(tween));
	
	//Update the elapsed time since the tween started
	if (tween->elapsed_time != tween->time)
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

//Retrieve the current value of the tween
fixed_t Tween_GetValue(Tween* tween)
{
	return tween->current_value;
}
