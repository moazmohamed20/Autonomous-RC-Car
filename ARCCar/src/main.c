#include <avr/io.h>
#include <util/delay.h>

// MCAL
#include "MCAL/G_INT/G_INT_int.h"
#include "MCAL/USART/USART_int.h"
#include "MCAL/EXT_INT/EXT_INT_int.h"
#include "MCAL/WATCHDOG/WATCHDOG_int.h"

// HAL
#include "HAL/PORT/PORT_int.h"
#include "HAL/WHEELS/WHEELS_int.h"
#include "HAL/BLUETOOTH/BLUETOOTH_int.h"
#include "HAL/ULTRASONIC/ULTRASONIC_int.h"

void ISR_ModeSelect();
void BluetoothSuperLoop();
void AutonomousSuperLoop();

int main(int argc, char const *argv[])
{
  WATCHDOG_Stop(); // 1) Good Practice At Startup, To Prevent MCU From Entering Reset Loop
  G_INT_Enable();  // 2) Enable Global Interrupt
  PORT_Init();     // 3) Initialize Port's Pins (Input, Output)

  EXT_INT_Enable(EXT_INT_INT0, EXT_INT_TRIGGER_ANY_CHANGE, ISR_ModeSelect); // 4) Enable External Interrupt 0: To ReLaunch The MCU In Different Mode

  if (PORT_GetPinValue(DIO_PORTD, DIO_PIN2))
  {
    ULTRASONIC_Init(EXT_INT_INT1, TIMER_TIMER1); // Initialize Ultrasonic Sensor (Pins, Interrupt, Timer)
    WHEELS_Init(255);                            // Initialize Wheels (Motors' Pins, PWM)
    AutonomousSuperLoop();                       // SuperLoop
  }
  else
  {
    BLUETOOTH_Init_2X(9600, USART_CHAR_SIZE_8_BIT, USART_PARITY_NONE, USART_STOP_BITS_ONE); // Initialize Bluetooth Module (UART)
    WHEELS_Init(0);                                                                         // Initialize Wheels (Motors' Pins, PWM)
    BluetoothSuperLoop();                                                                   // SuperLoop
  }

  return 0;
}

void BluetoothSuperLoop()
{
  u8 command;
  u8 speed = 0;
  while (TRUE)
  {
    command = BLUETOOTH_Receive();
    BLUETOOTH_TransmitChar(command); // Echo To Ensure That Command Received Successfully

    switch (command)
    {
    case 'F':
      WHEELS_Move(WHEELS_DIRECTION_FORWARD);
      WHEELS_SetSpeed(speed);
      break;

    case 'B':
      WHEELS_Move(WHEELS_DIRECTION_BACKWARD);
      WHEELS_SetSpeed(speed);
      break;

    case 'L':
      WHEELS_Move(WHEELS_DIRECTION_LEFT);
      WHEELS_SetSpeed(speed);
      break;

    case 'R':
      WHEELS_Move(WHEELS_DIRECTION_RIGHT);
      WHEELS_SetSpeed(speed);
      break;

    case 'G':
      WHEELS_Move(WHEELS_DIRECTION_FORWARD);
      WHEELS_SetLeftSpeed(speed / 1.3);
      WHEELS_SetRightSpeed(speed);
      break;

    case 'I':
      WHEELS_Move(WHEELS_DIRECTION_FORWARD);
      WHEELS_SetLeftSpeed(speed);
      WHEELS_SetRightSpeed(speed / 1.3);
      break;

    case 'H':
      WHEELS_Move(WHEELS_DIRECTION_BACKWARD);
      WHEELS_SetLeftSpeed(speed / 1.3);
      WHEELS_SetRightSpeed(speed);
      break;

    case 'J':
      WHEELS_Move(WHEELS_DIRECTION_BACKWARD);
      WHEELS_SetLeftSpeed(speed);
      WHEELS_SetRightSpeed(speed / 1.3);
      break;

    case 'S':
      WHEELS_Stop();
      WHEELS_SetSpeed(0);
      break;

    case 'D':
      WHEELS_Stop();
      WHEELS_SetSpeed(0);
      break;

    default:
      if (command == 'q')
      {
        speed = 255;
        WHEELS_SetSpeed(speed);
      }
      else if ((command >= '0') && (command <= '9'))
      {
        speed = (command - '0') * 25;
        WHEELS_SetSpeed(speed);
      }
      else
      {
        WHEELS_Stop();
      }
    }
  }
}

void AutonomousSuperLoop()
{
  f32 distance;

  while (TRUE)
  {
    distance = ULTRASONIC_GetDistanceCM();
    if (distance == 0 || distance >= 30)
    {
      WHEELS_Move(WHEELS_DIRECTION_FORWARD);
    }
    else
    {
      // Move A Little Backward
      WHEELS_Move(WHEELS_DIRECTION_BACKWARD);
      _delay_ms(500);
      WHEELS_Stop();

      // Measure Distance At Right
      WHEELS_Move(WHEELS_DIRECTION_RIGHT);
      _delay_ms(250);
      WHEELS_Stop();
      float rightDistance = ULTRASONIC_GetDistanceCM();

      // Measure Distance At Left
      WHEELS_Move(WHEELS_DIRECTION_LEFT);
      _delay_ms(500);
      WHEELS_Stop();
      float leftDistance = ULTRASONIC_GetDistanceCM();

      // Decide Which Direction To Go
      _delay_ms(500);
      if (rightDistance > leftDistance)
      {
        WHEELS_Move(WHEELS_DIRECTION_RIGHT);
        _delay_ms(500);
        WHEELS_Stop();
      }
    }

    _delay_ms(100);
  }
}

void ISR_ModeSelect()
{
  WATCHDOG_Start(WATCHDOG_TIMEOUT_1000_ms);
}