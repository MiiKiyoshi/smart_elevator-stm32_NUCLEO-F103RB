# smart_elevator-stm32_NUCLEO-F103RB

이 엘레베이터가 smart인 이유: 엘레베이터 호출을 계속 받으면서도 동작을 함 (heap 정렬 써서 가능)

![smart_elevator](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/6e2c1d65-c3ad-47b3-a5b7-2243da03c952)

### 모드

#### 엘레베이터 위치 초기화 모드

![image](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/1385bad4-5cae-4d99-9cbf-b9f59e34ba79)

초기 엘레베이터 위치가 4층이기 때문에 

리셋되었을때 엘레베이터가 4층에 위치하지 않는다면 4층으로 이동해야 한다.

엘레베이터 위치 초기화 모드를 통해 엘레베이터의 위치를 수동으로 조작할 수 있다.



#### 엘레베이터 작동 모드

![image](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/14f2da67-5cd9-48ad-847d-2d6508d35a79)

숫자키(1~4)를 누르면 알아서 이동한다.

#### 모드 바꾸는 법

![image](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/eb951727-19c8-4d60-95cb-c214d4de89ac)

nucleo보드에 달린 버튼(리셋 버튼 말고) 누르면 모드가 바뀐다.

### 엘레베이터 모형 사진

![image](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/0cc49afc-9273-49fa-a37a-716bfdaf5d3c)

![image](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/4adbffcd-7082-4bcf-b674-10d45b2d288b)

![image](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/35538560-9c16-4633-a1bf-8013fab8a24a)

![image](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/7e31ab0f-c272-4a6e-a071-154bc946e86e)
