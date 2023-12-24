#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "elevator.h"

#define UP_EL 2
#define DOWN_EL 1
#define STOP_EL 0

#define UNIT_ANGLE 720
#define ANGLE2STEPS 1950

uint8_t currFloor = 4;
uint8_t destiFloor = 4;

// 엘레베이터 호출 시스템
uint8_t RXD = 0;
char TXD[500] = {0};

uint8_t updownEl = STOP_EL;
uint8_t initEl = 1;
uint8_t goOrStop = 0;

void callEL(UART_HandleTypeDef *huart, HeapType* heap)
{
  HAL_UART_Receive_IT(huart, &RXD, 1);
  if(initEl)
  { 
    switch(RXD)
    {
      case 'w':
        goOrStop = (goOrStop + 1) % 2;
        if(goOrStop)
        {
            sprintf(TXD, "\r\nelevator up\r\n\r\n");
            updownEl = UP_EL;
        }
        else
        {
            sprintf(TXD, "\r\nelevator stops\r\n\r\n");
            updownEl = STOP_EL;
        }
        break;
      case 's':
        goOrStop = (goOrStop + 1) % 2;
        if(goOrStop)
        {
            sprintf(TXD, "\r\nelevator down\r\n\r\n");
            updownEl = DOWN_EL;
        }
        else
        {
            sprintf(TXD, "\r\nelevator stops\r\n\r\n");
            updownEl = STOP_EL;
        }
        break;
      case 'f':
        sprintf(TXD, "\r\nthe current floor: %d\r\n\r\n", currFloor);
        break;
      default:
        sprintf(TXD, "\r\nPress the following key\r\nkey w: elevator up\r\nkey s: elevator down\r\nkey f: the current floor\r\n\r\n");
        break;
    }
  }
  else
  {
    switch(RXD)
    {
      case '1':
        enqueueEL(heap, 1);
        sprintf(TXD, "\r\n1층\r\n\r\n");
        break;
      case '2':
        enqueueEL(heap, 2);
        sprintf(TXD, "\r\n2층\r\n\r\n");
        break;
      case '3':
        enqueueEL(heap, 3);
        sprintf(TXD, "\r\n3층\r\n\r\n");
        break;
      case '4':
        enqueueEL(heap, 4);
        sprintf(TXD, "\r\n4층\r\n\r\n");
        break;
      case 'f':
        sprintf(TXD, "\r\n현재 %d층입니다.\r\n\r\n", currFloor);
        break;
      default:
        sprintf(TXD, "\r\nPress the following key\r\nkey 1: the first floor\r\nkey 2: the second floor\r\nkey 3: the third floor\r\nkey 4: the fourth floor\r\nkey f: the current floor\r\n\r\n");
        break;
    }
  }
  HAL_UART_Transmit(&huart2, (uint8_t const *)TXD, strlen(TXD), 10);
  TXD[0] = '\0';
}

// 엘레베이터 관리 모드

void btnEL()
{
  initEl = (initEl + 1) % 2;
  if(initEl)
  {
    updownEl = STOP_EL;
    sprintf(TXD, "\r\n엘레베이터 작동정지\r\n\r\n");
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); 
  }
  else
  {
    sprintf(TXD, "\r\n엘레베이터 작동시작\r\n\r\n");
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); 
  }
  HAL_UART_Transmit(&huart2, (uint8_t const *)TXD, strlen(TXD), 10);
  TXD[0] = '\0';
}


// 엘레베이터 모터 시스템
void motorEL()
{
    if(initEl)
        initializeEL();
    else
        operationEL();
}

uint8_t indexMotor = 0;
void initializeEL()
{
    switch(updownEl)
    {
        case UP_EL:
            outStepdata(indexMotor);
            if(indexMotor < 3) indexMotor++;
            else indexMotor = 0;
            break;
        case DOWN_EL:
            outStepdata(indexMotor);
            if(indexMotor > 0) indexMotor--;
            else indexMotor = 3;
            break;
    }
}

int steps;
void operationEL()
{
    if(steps > 0)
    {
        switch(updownEl)
        {
            case UP_EL:
                outStepdata(indexMotor);
                if(indexMotor < 3) indexMotor++;
                else indexMotor = 0;
                break;
            case DOWN_EL:
                outStepdata(indexMotor);
                if(indexMotor > 0) indexMotor--;
                else indexMotor = 3;
                break;
        }
        steps--;
    }
}

void outStepdata(uint8_t index)
{
    switch(index)
    {
        case 0:
            HAL_GPIO_WritePin(in1Step_GPIO_Port, in1Step_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(in2Step_GPIO_Port, in2Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in3Step_GPIO_Port, in3Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in4Step_GPIO_Port, in4Step_Pin, GPIO_PIN_RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(in1Step_GPIO_Port, in1Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in2Step_GPIO_Port, in2Step_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(in3Step_GPIO_Port, in3Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in4Step_GPIO_Port, in4Step_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(in1Step_GPIO_Port, in1Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in2Step_GPIO_Port, in2Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in3Step_GPIO_Port, in3Step_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(in4Step_GPIO_Port, in4Step_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(in1Step_GPIO_Port, in1Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in2Step_GPIO_Port, in2Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in3Step_GPIO_Port, in3Step_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(in4Step_GPIO_Port, in4Step_Pin, GPIO_PIN_SET);
            break;
    }
}

uint8_t arrival = 1;
uint8_t runEL(int destFloor)
{
  int destAngle = (4 - destFloor) * UNIT_ANGLE;
  int currAngle = (4 - currFloor) * UNIT_ANGLE;

  if(currAngle > destAngle){
    upEL((double)(currAngle - destAngle));
    sprintf(TXD, "\r\n%d층으로 이동합니다.\r\n\r\n", destFloor);
    arrival = 1;
  }
  else if(destAngle > currAngle){
    downEL((double)(destAngle - currAngle));
    sprintf(TXD, "\r\n%d층으로 이동합니다.\r\n\r\n", destFloor);
    arrival = 1;
  }
  else return 0;

  destiFloor = destFloor;

  HAL_UART_Transmit(&huart2, (uint8_t const *)TXD, strlen(TXD), 10);
  TXD[0] = '\0';
  return 5;
}

void downEL(double angle)
{
  updownEl = DOWN_EL;
  steps = (int) round((ANGLE2STEPS/360) * angle);
}

void upEL(double angle)
{
  updownEl = UP_EL;
  steps = (int) round((ANGLE2STEPS/360) * angle);
}


// 엘레베이터 타이밍 & indicator 시스템
uint8_t iterTim2 = 0;
uint8_t delay = 5;

void startAndLedEL(HeapType* heap)
{
  if(!initEl)
  {
    if(busyEL())
    {
      toggleIndicator();
    }
    else
    {
      setIndicator();
      if(arrival)
      {
        arrival = 0;
        currFloor = destiFloor;
        sprintf(TXD, "\r\n%d층입니다.\r\n\r\n", currFloor);
        HAL_UART_Transmit(&huart2, (uint8_t const *)TXD, strlen(TXD), 10);
        TXD[0] = '\0';
      }
      iterTim2++;
      if(iterTim2 > delay) // 이전에 dequeue해서 현재층과 다른층이 나왔을 경우 도착해서 5초가 지나면 dequeue함
      {                    // 이전에 dequeue해서 현재층과 같은층이 나왔을 경우 즉시 dequeue함
        iterTim2 = 0;
        delay = runEL(dequeueEL(heap));
      }
    }
  }
}

uint8_t busyEL()
{
    return steps != 0;
}

uint8_t toggleLed = 0;
void toggleIndicator()
{
    if(toggleLed)
    {
        switch(destiFloor)
        {
            case 1:
                HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_RESET);
                break;
            case 2:
                HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_RESET);
                break;
            case 3:
                HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_RESET);
                break;
            case 4:
                HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_SET);
                break;
        }
    }
    else
    {
        HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_RESET);
    }
  toggleLed = (toggleLed + 1) % 2;
}

void setIndicator()
{
    switch(destiFloor)
    {
        case 1:
            HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(ledFloor1_GPIO_Port, ledFloor1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor2_GPIO_Port, ledFloor2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor3_GPIO_Port, ledFloor3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ledFloor4_GPIO_Port, ledFloor4_Pin, GPIO_PIN_SET);
            break;
    }
}

int heap_num;
void enqueueEL(HeapType* heap, int destFloor){
  element call;

  call.floor = destFloor;
  
  // key = |현재 목적으로 하는 층 - 목적 층|
  if((currFloor - call.floor) < 0){
    call.key = call.floor - destiFloor;
  }
  else{
    call.key = destiFloor - call.floor;
  }

  insert_min_heap(heap, call);
  heap_num++;
}

int dequeueEL(HeapType* heap){
  if(heap_num != 0){
    element call = delete_min_heap(heap);
    heap_num--;
    return call.floor;
  }
  return currFloor;
}

// 생성 함수
HeapType* createHeap()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void initHeap(HeapType* h)
{
    memset(h, 0, sizeof(HeapType));
    h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.

// 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

// 삭제 함수
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
        
        return item;
}