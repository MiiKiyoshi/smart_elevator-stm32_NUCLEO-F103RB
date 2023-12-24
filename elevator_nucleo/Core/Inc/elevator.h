#ifndef __ELEVATOR__
#define __ELEVATOR__

#define MAX_ELEMENT 50

//HEAP
typedef struct {
	int key;
	int floor;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;


// 엘레베이터 호출 시스템
void callEL(UART_HandleTypeDef *huart, HeapType* heap);

// 엘레베이터 관리 모드
void btnEL();

// 엘레베이터 모터 시스템
void motorEL();
void initializeEL();
void operationEL();
void outStepdata(uint8_t index);
uint8_t runEL(int destFloor);
void downEL(double angle);
void upEL(double angle);

// 엘레베이터 타이밍 & indicator 시스템
void startAndLedEL(HeapType* heap);
uint8_t busyEL();
void toggleIndicator();
void setIndicator();
void enqueueEL(HeapType* heap, int destFloor);
int dequeueEL(HeapType* heap);
HeapType* createHeap();
void initHeap(HeapType* heap);
void insert_min_heap(HeapType* h, element item);
element delete_min_heap(HeapType* h);

#endif 