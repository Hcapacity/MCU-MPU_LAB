/*
 * scheduler.c
 *
 *  Created on: Nov 22, 2025
 *      Author: Windows
 */

#include "scheduler.h"

TaskScheduler taskScheduler;

void SCH_Init(void) {
    taskScheduler.head = NULL;
    taskScheduler.taskCount = 0;
}

static uint32_t GenerateNewTaskID(void) {
    static uint32_t nextTaskID = 0;
    return ++nextTaskID;
}

static TaskNode* CreateNewTask(void (*taskFunction)(void), uint32_t delay, uint32_t period) {
    TaskNode *newTask = (TaskNode *)malloc(sizeof(TaskNode));
    if (newTask == NULL) {
        return NULL;
    }

    newTask->taskFunction = taskFunction;
    newTask->delay = delay;
    newTask->period = period;
    newTask->executeFlag = (delay == 0) ? 1 : 0;
    newTask->taskID = GenerateNewTaskID();
    newTask->next = NULL;

    return newTask;
}

void SCH_Update(void) {
    if (taskScheduler.head != NULL && taskScheduler.head->delay > 0) {
        taskScheduler.head->delay--;
    }
    if (taskScheduler.head != NULL && taskScheduler.head->delay == 0) {
        taskScheduler.head->executeFlag = 1;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    SCH_Update();
}

uint32_t SCH_Add_Task(void (*taskFunction)(void), uint32_t delay, uint32_t period) {
    // Kiểm tra điều kiện đầu vào
    if (taskFunction == NULL || taskScheduler.taskCount >= MAX_TASKS) {
        return NOT_VALID_TASK_ID;
    }

    TaskNode *newTask = CreateNewTask(taskFunction, delay, period);
    if (newTask == NULL) {
        return NOT_VALID_TASK_ID;
    }

    // Trường hợp danh sách rỗng
    if (taskScheduler.head == NULL) {
        taskScheduler.head = newTask;
        taskScheduler.taskCount++;
        return newTask->taskID;
    }

    // Tìm vị trí chèn task mới vào danh sách
    TaskNode *current = taskScheduler.head;
    TaskNode *previous = NULL;
    uint32_t accumulatedDelay = 0;

    while (current != NULL) {
        accumulatedDelay += current->delay;

        // Tìm được vị trí chèn task mới
        if (accumulatedDelay > delay) {
            // Tính delay cho task mới và điều chỉnh delay cho task hiện tại
            uint32_t newTaskDelay = delay - (accumulatedDelay - current->delay);
            uint32_t currentTaskDelay = accumulatedDelay - delay;

            newTask->delay = newTaskDelay;
            current->delay = currentTaskDelay;

            // Chèn task mới vào danh sách
            newTask->next = current;

            if (previous == NULL) {
                // Chèn ở đầu danh sách
                taskScheduler.head = newTask;
            } else {
                // Chèn ở giữa danh sách
                previous->next = newTask;
            }

            taskScheduler.taskCount++;
            return newTask->taskID;
        }

        previous = current;
        current = current->next;
    }

    // Chèn task mới ở cuối danh sách
    uint32_t remainingDelay = delay - accumulatedDelay;
    newTask->delay = remainingDelay;
    previous->next = newTask;
    taskScheduler.taskCount++;

    return newTask->taskID;
}

void SCH_Dispatch_Tasks(void) {
    if (taskScheduler.head == NULL) {
        return;
    }

    TaskNode *current = taskScheduler.head;

    // Duyệt qua tất cả các task để tìm những task tới hạn
    while (current != NULL && current->delay == 0) {
		// Thực thi task
		current->taskFunction();
		current->executeFlag = 0;

		// Lưu thông tin task trước khi xử lý
		void (*taskFunc)(void) = current->taskFunction;
		uint32_t taskPeriod = current->period;
		uint32_t taskID = current->taskID;

		// Di chuyển đến task tiếp theo trước khi xóa task hiện tại
		current = current->next;

		// Xóa task khỏi danh sách
		if (SCH_Delete_Task(taskID)) {
			// Thêm lại task nếu là task tuần hoàn
			if (taskPeriod > 0) {
				SCH_Add_Task(taskFunc, taskPeriod, taskPeriod);
			}
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    if (taskID == NOT_VALID_TASK_ID || taskScheduler.head == NULL) {
        return 0;
    }

    TaskNode *current = taskScheduler.head;
    TaskNode *previous = NULL;

    // Tìm task cần xóa
    while (current != NULL) {
        if (current->taskID == taskID) {
            // Tìm thấy task, thực hiện xóa
            if (previous == NULL) {
                // Xóa task đầu danh sách
                taskScheduler.head = current->next;
            } else {
                // Xóa task ở giữa hoặc cuối danh sách
                previous->next = current->next;
            }

            free(current);
            taskScheduler.taskCount--;
            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0; // Không tìm thấy task
}

