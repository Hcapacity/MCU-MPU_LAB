#include "scheduler.h"

static uint32_t num_task = 0;
sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(){
	for(int i = 0; i < SCH_MAX_TASKS; i++){
		SCH_tasks_G[i].pTask = 0;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
	}
}

void SCH_Update(void)
{
    if (SCH_tasks_G[0].pTask != 0)
    {
        if (SCH_tasks_G[0].Delay == 0)
        {
            SCH_tasks_G[0].RunMe += 1;
        }
        else
        {
            SCH_tasks_G[0].Delay -= 1;
        }
    }
}

unsigned char SCH_Add_Task(void (* pFunction) (), unsigned int DELAY, unsigned int PERIOD)
{
    unsigned char i = 0;
    unsigned int accumulated = 0;
    num_task++;

    while (i < SCH_MAX_TASKS && SCH_tasks_G[i].pTask != 0 && accumulated + SCH_tasks_G[i].Delay < DELAY)
    {
        accumulated += SCH_tasks_G[i].Delay;
        i++;
    }

    if (i == SCH_MAX_TASKS)
    {
        return RETURN_ERROR;
    }

    for (unsigned char j = num_task - 1; j > i; j--)
    {
        SCH_tasks_G[j] = SCH_tasks_G[j - 1];
    }

    SCH_tasks_G[i].pTask = pFunction;
    SCH_tasks_G[i].Period = PERIOD;
    SCH_tasks_G[i].RunMe = 0;
    SCH_tasks_G[i].Delay = DELAY - accumulated;

    if(SCH_tasks_G[i + 1].pTask != 0){
    	SCH_tasks_G[i + 1].Delay -= SCH_tasks_G[i].Delay;
    }

    return i;
}

void SCH_Dispatch_Tasks(void)
{
    while (SCH_tasks_G[0].RunMe > 0)
    {
        (*SCH_tasks_G[0].pTask)();
        SCH_tasks_G[0].RunMe = 0;

        sTask temp = SCH_tasks_G[0];

        SCH_Delete_Task(0);

        if (temp.Period != 0)
        {
            SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
        }

        if (SCH_tasks_G[0].Delay == 0 && SCH_tasks_G[0].pTask != 0)
        {
            SCH_tasks_G[0].RunMe++;
        }
    }

}

unsigned char SCH_Delete_Task(const tByte TASK_INDEX)
{
    if (SCH_tasks_G[TASK_INDEX].pTask == 0 || num_task == 0)
    {
        return RETURN_ERROR;
    }

    unsigned char i = TASK_INDEX;

    if (SCH_tasks_G[i + 1].pTask != 0)
    {
        SCH_tasks_G[i + 1].Delay += SCH_tasks_G[i].Delay;
    }

    for (; i < num_task - 1; i++)
    {
        SCH_tasks_G[i].pTask = SCH_tasks_G[i + 1].pTask;
        SCH_tasks_G[i].Delay = SCH_tasks_G[i + 1].Delay;
        SCH_tasks_G[i].Period = SCH_tasks_G[i + 1].Period;
        SCH_tasks_G[i].RunMe = SCH_tasks_G[i + 1].RunMe;
    }

    SCH_tasks_G[num_task - 1].pTask = 0;
    SCH_tasks_G[num_task - 1].Delay = 0;
    SCH_tasks_G[num_task - 1].Period = 0;
    SCH_tasks_G[num_task - 1].RunMe = 0;

    num_task--;

    return RETURN_NORMAL;
}

