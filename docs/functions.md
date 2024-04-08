# Tween Functions
#### Tween_InitWithValue(Tween* tween, fixed_t initial_value, fixed_t final_value, fixed_t duration, Eases ease, u8 flags)
Initializes the necessary values for the tween
- `tween` - The tween structure that will store the values
- `initial_value` - The initial value of the Tween
- `final_value` - The final value of the Tween
- `duration` - The duration of the tween in seconds. For example, `FIXED_DEC(5,10)` represents 0.5 seconds.
- `ease` - The easing method used, such as `EASING_LINEAR`
- `flags` -  The flags used, for example, `TWEEN_FLAGS_LOOP`. This indicates that the tween will run in a loop.

#### Tween_InitWithVariable(Tween* tween, fixed_t* valuep, fixed_t final_value, fixed_t duration, Eases ease, u8 flags)
Initializes the necessary values for the tween and stores the initial value in a pointer so that it can be directly changed.
- `tween` - The tween structure that will store the values
- `valuep` - A pointer to the initial value of the tween. This allows direct manipulation of the variable instead of using the `Tween_GetValue()` function.
- `final_value` - The final value of the Tween
- `duration` - The duration of the tween in seconds. For example, `FIXED_DEC(5,10)` represents 0.5 seconds.
- `ease` - The easing method used, such as `EASING_LINEAR`
- `flags` -  The flags used, for example, `TWEEN_FLAGS_LOOP`. This indicates that the tween will run in a loop.

#### Tween_Tick(Tween* tween)
Performs the tween. This function should only be called when you want to execute the tween.
- `tween` - The tween structure that stores the needed values

#### Tween_GetValue(Tween* tween)
Retrieve the current value of the tween
- `tween` - The tween structure that stores the needed values
