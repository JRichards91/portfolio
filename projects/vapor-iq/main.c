#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <driverlib/adc.h>
#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>
#include <driverlib/sysctl.h>
#include <driverlib/timer.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <inc/hw_ints.h>
#include <inc/hw_timer.h>

#define ADC0_DITHER (*((volatile unsigned long *)0x40038038)) // Define ADC0_DITHER address
#define ADC1_DITHER (*((volatile unsigned long *)0x40039038)) // Define ADC1_DITHER address
#define GPIO_PORTD_ACTIVE_PINS GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 // Define Active Pins on Port D (pins 0-3)
#define GPIO_PORTE_ACTIVE_PINS GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 // Define Active Pins on Port E (pins 1-3)
#define GPIO_PORTF_ACTIVE_PINS GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 // Define Active Pins on Port F (pins 1-3)

uint8_t displayCount = 0;
uint8_t displayMode = 1;
uint32_t rawPressure, rawTemp;
int actualPressure, actualTemp, expectedPressure, percentDensity, ones, tens, hundreds;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the SwitchISR function
//
// This function will be called when the user presses the button
// in order to change the displayed information on the 7-Segment
// Display and the Display Mode LED
//
//*****************************************************************************

void SwitchISR(void)
{
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4); // Clear the Interrupt flag on Port F Pin 4
    GPIOIntDisable(GPIO_PORTF_BASE, GPIO_INT_PIN_4); // Disable the Interrupt on Port F Pin 4

    SysCtlDelay(53000); // De-bounce ~ 10ms

    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0x00) // De-bounce switch press AND switch release!!!
    {
        displayMode ++; // Add 1 to displayMode
        if (displayMode > 3) displayMode = 1; // If displayMode > 2 set it to 0

        TimerLoadSet(TIMER0_BASE, TIMER_A, 80000000); // Set Timer 0 to count down from 5s (16000000 * 5.00)
        TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Enable Interrupt for Timer 0A
    }

    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4); // Enable the Interrupt on Port F Pin 4
    } // end SwitchISR

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the TimerISR function
//
// This function will be called 5 seconds after the user presses the button
// in order to default back to display the Density %
//
//*****************************************************************************

void TimerISR(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Clear the Interrupt flag for Timer 0A
    TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Disable Timer 0A as an interrupt

    displayMode = 1; // Reset displayMode to 0
} // end TimerISR

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the DisplayISR
//
// This function is called every 1ms to update the displayed information
// to the 7-Segment Display, the Display Mode LED, and Alarm LED
//
//*****************************************************************************

void DisplayISR(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // Clear the Interrupt flag for Timer 1A

    expectedPressure = 0.17065 * (actualTemp + 233); // Calculate expectedPressure (P=sT)
    percentDensity = (actualPressure * 100) / expectedPressure; // Calculate percentDensity [(actualPressure / expectedPressure) * 100]

    //*****************************************************************************
    //
    // Update the Display Mode (hundreds, tens, ones)
    //
    // 0 = Density (green light)
    // 1 = Pressure (blue light)
    // 2 = Temperature (red light)
    //
    //*****************************************************************************

    if (displayMode == 1) // If displayMode = 1, display Density information
    {
        hundreds = (percentDensity / 100) % 10;
        tens = (percentDensity / 10) % 10;
        ones = (percentDensity / 1) % 10;
    }

    if (displayMode == 2) // If displayMode = 2, display Pressure information
    {
        hundreds = (actualPressure / 100) % 10;
        tens = (actualPressure / 10) % 10;
        ones = (actualPressure / 1) % 10;
    }

    if (displayMode == 3) // If displayMode = 3, display Temperature information
    {
        hundreds = (actualTemp / 100) % 10;
        tens = (actualTemp / 10) % 10;
        ones = (actualTemp / 1) % 10;
    }

    //*****************************************************************************
    //
    // Update the 7-Segment Display
    //
    //*****************************************************************************

    displayCount ++; // Add 1 to displayCount
    if (displayCount > 3) displayCount = 1; // If displayCount > 3 set it to 1

    if (displayCount == 3 && hundreds > 0) // If displayCount is 3 AND hundreds is greater than 0, write the hundreds value to Pin 3
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PORTD_ACTIVE_PINS, hundreds);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PORTE_ACTIVE_PINS, 8);
    }

    if (displayCount == 2 && (tens > 0 || hundreds > 0)) // If displayCount is 2 AND (tens is greater than 0 OR hundreds is greater than 0)
    {                                                    // write the tens value to Pin 2
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PORTD_ACTIVE_PINS, tens);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PORTE_ACTIVE_PINS, 4);
    }

    if (displayCount == 1) // If displayCount is 1, write the ones value to Pin 1
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PORTD_ACTIVE_PINS, ones);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PORTE_ACTIVE_PINS, 2);
    }

    //*****************************************************************************
    //
    // Update the Display Mode LED
    //
    // 0 = Density (green light)
    // 1 = Pressure (blue light)
    // 2 = Temperature (red light)
    //
    //*****************************************************************************

    if (displayMode == 1) // If displayMode is 1, turn on the green light
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0x00);
    }

    if (displayMode == 2) // If displayMode is 2, turn on the blue light
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_3, 0x00);
    }

    if (displayMode == 3) // If displayMode is 3, turn on the red light
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    }

    //*****************************************************************************
    //
    // Update the Alarm LED
    //
    //*****************************************************************************

    if (percentDensity <= 85) GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01); // If Density drops below 85%, turn on the Alarm

    if (percentDensity >= 90) GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00); // If Density rises above 90%, turn off the Alarm
} // end DisplayISR

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the PressureISR function
//
// This function is called to update the information from ADC0
// that is responsible for the Pressure information
//
//*****************************************************************************

void PressureISR(void)
{
    ADCIntClear(ADC0_BASE, 3); // Clear the Interrupt flag for ADC0
    ADCIntDisable(ADC0_BASE, 3); // Disable the Interrupt for ADC0
    ADCSequenceDataGet(ADC0_BASE, 3, &rawPressure); // Get the analog value for ADC0
    actualPressure = rawPressure / 40.95; // Calculate the Pressure
    ADCIntEnable(ADC0_BASE, 3); // Enable the Interrupt for ADC0
    ADCProcessorTrigger(ADC0_BASE, 3);
} // end PressureISR

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the TemperatureISR function
//
// This function is called to update the information from ADC1
// that is responsible for the Temperature information
//
//*****************************************************************************

void TemperatureISR(void)
{
    ADCIntClear(ADC1_BASE, 3); // Clear the Interrupt flag for ADC1
    ADCIntDisable(ADC1_BASE, 3); // Disable the Interrupt for ADC1
    ADCSequenceDataGet(ADC1_BASE, 3, &rawTemp); // Get the analog value for ADC1
    actualTemp = rawTemp / 40.95; // Calculate the Temperature
    ADCIntEnable(ADC1_BASE, 3); // Enable the Interrupt for ADC1
    ADCProcessorTrigger(ADC1_BASE, 3);
} // end TemperatureISR

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the PortB_Config function
//
// This function enables Port B Pin 0 as an output (for the alarm)
// and Pin 5 as an input (for Pressure)
//
//*****************************************************************************

void PortB_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // RCGCGPIO Port B (output LED alarm on pin 0 & input pressure sensor on pin 5)

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0); // GPIODEN Port B Pin(s) 0
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD); // GPIODIR, GPIOR4R Port B Pin(s) 0

    GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5); // GPIOADC Port B Pin(s) 5
} // end PortB_Config

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the PortD_Config function
//
// This function enables Port D Pins 0-3 as outputs (for the
// 7-Segment Display)
//
//*****************************************************************************

void PortD_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); // RCGCGPIO Port D (output to 7-Segment Display on pins 0-3)

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PORTD_ACTIVE_PINS); // GPIODEN Port D Pin(s) 0-3
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PORTD_ACTIVE_PINS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD); // GPIODIR, GPIOR4R Port D Pin(s) 0-3
} // end PortD_Config

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the PortE_Config function
//
// This function enables Port E Pins 1-3 as outputs (for the
// 7-Segment Display) and Pin 5 as an input (for Temperature)
//
//*****************************************************************************

void PortE_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // RCGCGPIO Port E (output to 7-Segment Display on pins 1-3 & input temperature sensor on pin 5)

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PORTE_ACTIVE_PINS); // GPIODEN Port E Pin(s) 1-3
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PORTE_ACTIVE_PINS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD); // GPIODIR, GPIOR2R Port E Pin(s) 1-3

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5); // GPIOADC Port E Pin(s) 5
} // end PortE_Config

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the PortF_Config function
//
// This function enables Port F Pins 1-3 as outputs (for the
// Display Mode LED) and Pin 4 as an input (for the switch)
//
//*****************************************************************************

void PortF_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // RCGCGPIO Port F (input from switch on pin 4)

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PORTF_ACTIVE_PINS); // GPIODEN Port F Pin(s) 1-3
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PORTF_ACTIVE_PINS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD); // GPIODIR, GPIOR2R Port F Pin(s) 1-3

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4); // GPIODEN Port F Pin(s) 4
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); // GPIODIR, GPIOR2R, GPIOPUR Port F
} // end PortF_Config

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the ADC0_Config function
//
// This function enables ADC0 and configures it for use as
// a data collector for the PressureISR
//
//*****************************************************************************

void ADC0_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // RCGCGPIO ADC 0
    ADCHardwareOversampleConfigure(ADC0_BASE, 64); // Average of many samples for accuracy
    ADC0_DITHER |= 0x00000040; // Enable the DITHER bit for noise reduction
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 2); // Configure ADC0
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH8); // Set ADC to Port E Pin 5
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCProcessorTrigger(ADC0_BASE, 3);
    ADCIntRegister(ADC0_BASE, 3, PressureISR); // Register PressureISR to ADC0
    ADCIntEnable(ADC0_BASE, 3); // Enable ADC0 Interrupt
} // end ADC0_Config

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the ADC1_Config function
//
// This function enables ADC1 and configures it for use as
// a data collector for the TemperatureISR
//
//*****************************************************************************

void ADC1_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1); // RCGCGPIO ADC 1
    ADCHardwareOversampleConfigure(ADC1_BASE, 64); // Average of many samples for accuracy
    ADC1_DITHER |= 0x00000040; // Enable the DITHER bit for noise reduction
    ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 2); // Configure ADC1
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH11); // Set ADC to Port B Pin 5
    ADCSequenceEnable(ADC1_BASE, 3);
    ADCProcessorTrigger(ADC1_BASE, 3);
    ADCIntRegister(ADC1_BASE, 3, TemperatureISR); // Register TemperatureISR to ADC1
    ADCIntEnable(ADC1_BASE, 3); // Enable ADC1 Interrupt
} // end ADC1_Config

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//*****************************************************************************
//
// This is the initialization function
//
// This function is responsible for setting the MOSC,
// enabling and configuring the two timers needed for
// display and delay purposes, and enabling and
// registering the GPIO Interrupt for when the user
// presses the button
//
//*****************************************************************************

void initialize(void)
{
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN); // Main Oscillator (crystal)

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); // Peripheral Enable Timer 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); // Peripheral Enable Timer 1

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // Configure Timer 0 as Full-Width Periodic Timer
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC); // Configure Timer 1 as Full-Width Periodic Timer

    TimerLoadSet(TIMER1_BASE, TIMER_A, 16000); // Set Timer 1 to count down from 1ms (16000000 * 0.001)
    TimerLoadSet(TIMER0_BASE, TIMER_A, 80000000); // Set Timer 0 to count down from 5s (16000000 * 5.00)

    TimerEnable(TIMER0_BASE, TIMER_A); // Start Timer 0
    TimerEnable(TIMER1_BASE, TIMER_A); // Start Timer 1

    TimerIntRegister(TIMER0_BASE, TIMER_A, TimerISR); // Register Timer 0A Interrupt to the function TimerISR
    TimerIntRegister(TIMER1_BASE, TIMER_A, DisplayISR); // Register Timer 1A Interrupt to the function DisplayISR

    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE); // Set Port F on Falling Edge

    GPIOIntRegister(GPIO_PORTF_BASE, SwitchISR); // Register SwitchISR to Port F Interrupt

    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // Enable Interrupt for Timer 1A

    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4); // Enable Interrupt for Port F Pin 4
} // end Initialize()

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void main(void)
{
    PortB_Config();
    PortD_Config();
    PortE_Config();
    PortF_Config();
    ADC0_Config();
    ADC1_Config();
    initialize();
    ADCProcessorTrigger(ADC0_BASE, 3);
    ADCProcessorTrigger(ADC1_BASE, 3);

    while(1)
    {
    }
} // end main
