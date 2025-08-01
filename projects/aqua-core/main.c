//--------------------------------------------------
// IR Distance Sensor:                              |
//      1. Red = +5V                                |
//      2. Black = GND                              |
//      3. Orange = PB_5 (Analog Input)             |
//                                                  |
// Non-Contact Liquid Sensor:                       |
//      1. Red = +5V                                |
//      2. Black = GND                              |
//      3. Green = PB_0 (Digital Input)             |
//      4. Blue = PB_1 (Digital Output)             |
//                                                  |
// 4-Pin Adapter:                                   |
//      1. Brown = VOUT                             |
//      2. Blue = GND                               |
//      3. Black = IO1                              |
//      4. Yellow = IO2                             |
//                                                  |
// Temperature Sensor:                              |
//      1. Red = +5V                                |
//      2. Green = GND                              |
//      3. Yellow = PB_2 (I2C SCL)                  |
//      4. Blue = PB_3 (I2C SDA)                    |
//                                                  |
// Motor Driver Board:                              |
//      1. STEP = PC_4 (Digital Output)             |
//      2. DIR = PC_5 (Digital Output)              |
//      3. MS1 = PC_6 (Digital Output)              |
//      4. MS2 = PC_7 (Digital Output)              |
//      5. ENABLE = PD_6 (Digital Output)           |
//      6. A+ = Green (Stepper Motor)               |
//      7. A- = Red (Stepper Motor)                 |
//      8. B+ = Blue (Stepper Motor)                |
//      9. B- = Yellow (Stepper Motor)              |
//      10. M+ = +12V                               |
//      11. GND = GND                               |
//                                                  |
// Solenoid Valve:                                  |
//      1. Red = +5V                                |
//      2. Black = GND                              |
//      3. Green = PD_2 (Digital Output)            |
//                                                  |
// Relay Module:                                    |
//      1. NC = Blue                                |
//      2. NO = Red                                 |
//      3. COM = +12V                               |
//      4. Yellow = GND                             |
//--------------------------------------------------
// Microstep Select Resolution Truth Table          |
//      MS1     MS2     Microstep Resolution        |
//       L       L       Full Step (2 Phase)        |
//       H       L       Half Step                  |
//       L       H       Quarter Step               |
//       H       H       Eigth Step                 |
//--------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include <driverlib/pin_map.h>
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"

#define ADC0_DITHER (*((volatile unsigned long *)0x40038038))
#define SHT20_I2C_ADDR  0x40
#define TRIGGER_TEMP_MEASURE_HOLD  0xE3

bool printFlag = false;
uint32_t rawADC0;
uint8_t liquidLevel;
float realDistance, realTemperature;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------
// This is the ADC0_Handler function:               |
//      This function is responsible for gathering  |
//      the current ADC value and triggering the    |
//      next ADC value.                             |
//--------------------------------------------------

void ADC0_Handler(void)
{
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, &rawADC0);
    ADCProcessorTrigger(ADC0_BASE, 3);
} // end ADC0_Handler()

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------
// This is the I2C0_Handler function:               |
//      This function is responsible for writing    |
//      the current run mode to the correct         |
//      register.                                   |
//                                                  |
//      This function is responsible for reading    |
//      from the correct register.                  |
//                                                  |
//      This function is responsible for gathering  |
//      the current temperature.                    |
//--------------------------------------------------

uint16_t I2C0_Handler()
{
    uint16_t data;

    I2CMasterSlaveAddrSet(I2C0_BASE, SHT20_I2C_ADDR, false);
    I2CMasterDataPut(I2C0_BASE, TRIGGER_TEMP_MEASURE_HOLD);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while (I2CMasterBusy(I2C0_BASE));
    I2CMasterSlaveAddrSet(I2C0_BASE, SHT20_I2C_ADDR, true);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while (I2CMasterBusy(I2C0_BASE));
    data = (I2CMasterDataGet(I2C0_BASE) << 8);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while (I2CMasterBusy(I2C0_BASE));
    data |= I2CMasterDataGet(I2C0_BASE);

    return data;
} // end I2C0_Handler()

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------
// This is the SysTick_Handler function:            |
//      This function is responsible for setting    |
//      the printFlag true.                         |
//--------------------------------------------------

void SysTick_Handler(void)
{
    printFlag = true;
} // end SysTick_Handler()

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------
// This is the Timer0A_Handler function:            |
//      This function is responsible for            |
//      controlling the ENABLE, DIR, and STEP       |
//      of the motor control board.                 |
//--------------------------------------------------

void Timer0A_Handler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Clear TIMER0A interrupt

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00); // ENABLE '0' => turn on motor

    if(rawADC0 > 1450) // ~10cm or ~4in
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5); // DIR '1' => CW rotation
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); // STEP '1' then '0' to rotate
        SysCtlDelay(53);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x00);
    }

    else if(rawADC0 < 775) // ~20cm or ~8in
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x00); // DIR '0' => CCW rotation
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); // STEP '1' then '0' to rotate
        SysCtlDelay(53);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x00);
    }

    else
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6); // ENABLE '1' => turn off motor
    }
} // end Timer0A_Handler()

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------
// This is the Timer1A_Handler function:            |
//      This function is responsible for            |
//      controlling the solenoid valve.             |
//--------------------------------------------------

void Timer1A_Handler(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    uint8_t liquidLevel = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, (liquidLevel == 1) ? GPIO_PIN_2 : 0x00);
} // end Timer1A_Handler()

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------
// This is the config function:                     |
//      This function is responsible for            |
//      configuring the Tiva C board Ports, Timers, |
//      ADC, and I2C needed.                        |
//--------------------------------------------------

void config(void)
{
    // Port B Config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0); // Digital-In: Pin(s) 0
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1); // Digital-Out: Pin(s) 1
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, false); // Set mode to '0'
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2); // SCL: Pin(s) 2
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3); // SDA: Pin(s) 3
    GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5); // ADC: Pin(s) 5

    // Port C Config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, 0xF0); // Pin(s) 4, 5, 6, 7

    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6); // MS1 [H]
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7); // MS2 [H]

//    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x00); // MS1 [L]
//    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x00); // MS2 [L]

    // Port D Config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0x44); // Pin(s) 2 & 6

    // SysTick Config (printf Control Timer)
    SysTickPeriodSet(16000000);
    SysTickIntRegister(SysTick_Handler);
    SysTickEnable();
    SysTickIntEnable();

    // Timer 0 Config (Motor Control Timer)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, 20000);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0A_Handler);
    TimerEnable(TIMER0_BASE, TIMER_A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Timer 1 Config (Solenoid Control Timer)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, 160000);
    TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1A_Handler);
    TimerEnable(TIMER1_BASE, TIMER_A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // ADC0 Config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    ADC0_DITHER |= 0x00000040;
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 2);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH11);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCProcessorTrigger(ADC0_BASE, 3);
    ADCIntRegister(ADC0_BASE, 3, ADC0_Handler);
    ADCIntEnable(ADC0_BASE, 3);

    // I2C 0 Config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    I2CMasterInitExpClk(I2C0_BASE, 16000000, false);
} // end config()

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------
// This is the main function:                       |
//      This function is responsible for running    |
//      the config function and entering a while    |
//      loop that will convert rawADC0 to           |
//      realDistance, get the liquidLevel, write    |
//      to the CTRL_REG on the temperature sensor,  |
//      and get the realTemperature from the I2C    |
//      sensor.                                     |
//                                                  |
//      The commented print section blocks the      |
//      stepper motor because printf is a blocking  |
//      action on the CPU. Only use this if needed  |
//      for debugging.                              |
//--------------------------------------------------

void main(void)
{
    config();

    while(true)
    {
        float Vo = 3.3 * rawADC0 / 4095.0;
        realDistance = 13 / Vo;
        liquidLevel = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0);
        uint16_t rawTemperature = I2C0_Handler();
        float tempTemperature = rawTemperature * (175.72 / 65536.0);
        realTemperature = tempTemperature - 46.85;

//        if(printFlag)
//        {
//            printf("Valve %s: %d\n", (liquidLevel == 1) ? "Open" : "Closed", liquidLevel);
//            printf("Distance: %.2f [cm]\n", realDistance);
//            printf("Temperature: %.2f [°C]\n", realTemperature);
//            printFlag = false;
//        }
    }
} // end main()
