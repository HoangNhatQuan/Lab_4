/*
 * scheduler.c
 *
 *  Created on: Dec 4, 2022
 *      Author: Asus
 */

#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Delete_Task(unsigned char TASK_INDEX){

	  for(unsigned int i = TASK_INDEX+1; i<SCH_MAX_TASKS; i++){
		  //shift left
		  	SCH_tasks_G[i-1].pTask = SCH_tasks_G[i].pTask;
			SCH_tasks_G[i-1].Delay = SCH_tasks_G[i].Delay ;
			SCH_tasks_G[i-1].Period = SCH_tasks_G[i].Period ;
			SCH_tasks_G[i-1].RunMe = SCH_tasks_G[i].RunMe ;


	  }
	  SCH_tasks_G[SCH_MAX_TASKS-1].pTask = 0x0000 ;
	  SCH_tasks_G[SCH_MAX_TASKS-1].Delay = 0 ;
	  SCH_tasks_G[SCH_MAX_TASKS-1].Period = 0 ;
	  SCH_tasks_G[SCH_MAX_TASKS-1].RunMe = 0 ;
 }
void SCH_Delete_Task1(unsigned char TASK_INDEX){

	  SCH_tasks_G[TASK_INDEX].pTask = 0x0000 ;
	  SCH_tasks_G[TASK_INDEX].Delay = 0 ;
	  SCH_tasks_G[TASK_INDEX].Period = 0 ;
	  SCH_tasks_G[TASK_INDEX].RunMe = 0 ;

 }
void SCH_Init(){
	unsigned char i;
	for(i = 0; i<SCH_MAX_TASKS; i++){
		SCH_Delete_Task1(i);
	}
}
 void SCH_Update(void){
	 	unsigned char index = 0;;
	 	 if(SCH_tasks_G[index].pTask){
			  if(SCH_tasks_G[index].Delay <= 0){
				  SCH_tasks_G [index].RunMe += 1;
			  }else{
				  SCH_tasks_G[index].Delay -= 1;
			  }
		  }
}
void SCH_Add_Task(void(*pFunction )(), unsigned int DELAY, unsigned int PERIOD){
	unsigned int pos = 0;
	unsigned int pos2 = 0;

	for(pos = 0; pos<SCH_MAX_TASKS; pos++){
		if(SCH_tasks_G[pos].pTask ==0){
			break;
		}
	}
	if(pos==SCH_MAX_TASKS) return;

	if(SCH_tasks_G[0].pTask==0){ //queue ban dau rong
		SCH_tasks_G[0].pTask = pFunction;
		SCH_tasks_G[0].Delay = DELAY;
		SCH_tasks_G[0].Period = PERIOD;
		SCH_tasks_G[0].RunMe = 0;
	}else{
		unsigned int valDelay = DELAY;
			for(int i = 0; i<=pos; i++){
				if(SCH_tasks_G[i].Delay <= valDelay && SCH_tasks_G[i].pTask){ // cu nho hon bang moi
					valDelay -= SCH_tasks_G[i].Delay ;
				}else{
					pos2 = i;
					if (SCH_tasks_G[i].pTask)
						SCH_tasks_G[i].Delay -= valDelay;
					break;
				}
			}
			for(int j = pos; j>pos2; j--){
				SCH_tasks_G[j].pTask = SCH_tasks_G[j-1].pTask;
				SCH_tasks_G[j].Delay = SCH_tasks_G[j-1].Delay;
				SCH_tasks_G[j].Period = SCH_tasks_G[j-1].Period;
				SCH_tasks_G[j].RunMe = SCH_tasks_G[j-1].RunMe;
			}
			SCH_tasks_G[pos2].pTask = pFunction;
			SCH_tasks_G[pos2].Delay = valDelay;
			SCH_tasks_G[pos2].Period = PERIOD;
			SCH_tasks_G[pos2].RunMe = 0;
	}
}

 void SCH_Dispatch_Tasks(void){
	 unsigned char index = 0;
	 sTask tempTask;
	 for(index = 0; index<SCH_MAX_TASKS; index++){
		 if ( SCH_tasks_G[index].RunMe > 0) {
			  (*SCH_tasks_G[index].pTask)(); // Run the task
			  SCH_tasks_G[index].RunMe -= 1; // Reset / reduce RunMe f l a g
			  //luu lai task hien tai vao tempTask
//			  tempTask.Delay = SCH_tasks_G[index].Period;
			  tempTask.Period = SCH_tasks_G[index].Period;
//			  tempTask.RunMe = SCH_tasks_G[index].RunMe;
			  tempTask.pTask = SCH_tasks_G[index].pTask;
			  //-----------------------------------//
			  SCH_Delete_Task(index) ;
			  if(tempTask.Period > 0){
				  // neu Task ko phai One Shot add vao lai array
				  //unsigned int tmpDelay = tempTask.Period;
				  SCH_Add_Task(tempTask.pTask, tempTask.Period, tempTask.Period);
			  }


		  }
	}
 }



