/*
 * scheduler.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include <stdint.h>
#include <stdlib.h>

#define MAX_TASKS 20
#define ADD_TASK_ERROR -1
#define NOT_VALID_TASK_ID 0

typedef struct TaskNode {
    void (*taskFunction)(void);
    struct TaskNode *next;
    uint32_t delay;
    uint32_t period;
    uint8_t executeFlag;
    uint32_t taskID;
} TaskNode;

typedef struct {
    TaskNode *head;
    uint32_t taskCount;
} TaskScheduler;

extern TaskScheduler taskScheduler;

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t SCH_Add_Task(void (*taskFunction)(void), uint32_t delay, uint32_t period);
uint8_t SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCHEDULER_H_ */
