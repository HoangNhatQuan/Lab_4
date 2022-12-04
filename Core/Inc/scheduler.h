/*
 * scheduler.h
 *
 *  Created on: Dec 4, 2022
 *      Author: Asus
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

typedef struct{
	 void (*pTask)(void);
	 uint32_t Delay;
	 uint8_t Period;
	 uint32_t RunMe;

	 uint32_t Task_ID;
 }sTask;

#define SCH_MAX_TASKS 5

 void SCH_Init();
 void SCH_Update(void);
 void SCH_Add_Task(void(*pFunction )(), unsigned int DELAY, unsigned int PERIOD);
 void SCH_Dispatch_Tasks(void);
 void SCH_Delete_Task(unsigned char TASK_INDEX);
 void SCH_Delete_Task1(unsigned char TASK_INDEX);


#endif /* INC_SCHEDULER_H_ */
