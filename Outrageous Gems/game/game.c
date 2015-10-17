/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Created: 8/21/2014 12:13:00 PM
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "scheduler.h" // struct task and GCD function in here
#include "game.h"
#include "endAnimation.h"

int main(void)
{
	// Set Data Direction Registers
	// Buttons PORTA[0-7], set AVR PORTA to pull down logic
	DDRB = 0xFF; PORTB = 0x00; // LED's
	DDRC = 0xF0; PORTC = 0x0F; // keypad
	DDRA = 0xFF; PORTA = 0x00; // LCD control lines
	DDRD = 0xFF; PORTD = 0x00; // LCD data lines
	
	// Initializes the LCD display
	LCD_init();
	cursorOff();
	fakeRandomNumber = 0;
	resetTitle();
	resetGame();
	
	// Period for the tasks
	unsigned long int Button_Calc = 25;
	unsigned long int Title_Calc = 175;
	unsigned long int Tutorial_calc = 100;
	unsigned long int Game_calc = 100;
	unsigned long int Time_calc = 1000;
	unsigned long int endani_calc = 150;
	
	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(tmpGCD, Button_Calc);
	tmpGCD = findGCD(tmpGCD, Title_Calc);
	tmpGCD = findGCD(tmpGCD, Tutorial_calc);
	tmpGCD = findGCD(tmpGCD, Game_calc);
	tmpGCD = findGCD(tmpGCD, Time_calc);
	tmpGCD = findGCD(tmpGCD, endani_calc);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick0_period = Button_Calc/GCD;
	unsigned long int SMTick1_period = Title_Calc/GCD;
	unsigned long int SMTick2_period = Tutorial_calc/GCD;
	unsigned long int SMTick3_period = Game_calc/GCD;
	unsigned long int SMTick4_period = Time_calc/GCD;
	unsigned long int SMTick5_period = endani_calc/GCD;

	//Declare an array of tasks
	static task task0, task1, task2, task3, task4, task5;
	task *tasks[] = { &task0, &task1, &task2, &task3, &task4, &task5};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task0.state = 0;
	task0.period = SMTick0_period;
	task0.elapsedTime = SMTick0_period;
	task0.TickFct = &getButton;
	
	task1.state = 0;
	task1.period = SMTick1_period;
	task1.elapsedTime = SMTick1_period;
	task1.TickFct = &TitleScreen;
	

	task2.state = 0;
	task2.period = SMTick2_period;
	task2.elapsedTime = SMTick2_period;
	task2.TickFct = &Tutorial;
	
	task3.state = 0;
	task3.period = SMTick3_period;
	task3.elapsedTime = SMTick3_period;
	task3.TickFct = &game;
	
	task4.state = 0;
	task4.period = SMTick4_period;
	task4.elapsedTime = SMTick4_period;
	task4.TickFct = &updateTimer;
	
	task5.state = 0;
	task5.period = SMTick5_period;
	task5.elapsedTime = SMTick5_period;
	task5.TickFct = &endAnimation;
	
	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();


	unsigned short i; // Scheduler for-loop iterator
	while(1)
	{
		// Scheduler code
		for ( i = 0; i < numTasks; i++ )
		{
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period )
			{
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	// Error: Program should not exit!
	return 0;

}