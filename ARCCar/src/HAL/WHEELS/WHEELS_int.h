#ifndef HAL_WHEELS_WHEELS_int_H_
#define HAL_WHEELS_WHEELS_int_H_

#include "../../LIB/std_types.h"

// ---------------------------------------- Enums ---------------------------------------- //

// Movement Direction
typedef enum
{
    WHEELS_DIRECTION_FORWARD,
    WHEELS_DIRECTION_BACKWARD,
    WHEELS_DIRECTION_LEFT,
    WHEELS_DIRECTION_RIGHT
} WHEELS_ENUM_Directions;

// ---------------------------------------- Functions ---------------------------------------- //

void WHEELS_Init(u8 Copy_InitialSpeed);

void WHEELS_Move(WHEELS_ENUM_Directions Copy_Direction);
void WHEELS_SetRightSpeed(u8 Copy_Speed);
void WHEELS_SetLeftSpeed(u8 Copy_Speed);
void WHEELS_SetSpeed(u8 Copy_Speed);
void WHEELS_Stop();

#endif
