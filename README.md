# smart_elevator-stm32_NUCLEO-F103RB

이 엘레베이터가 smart인 이유: 엘레베이터 호출을 계속 받으면서도 동작을 함 (heap 정렬 써서 가능)

![smart_elevator](https://github.com/MiiKiyoshi/smart_elevator-stm32_NUCLEO-F103RB/assets/121929511/6e2c1d65-c3ad-47b3-a5b7-2243da03c952)

### 모드

#### 엘레베이터 위치 초기화 모드

![image-20231224185809722](.\README.assets\image-20231224185809722.png)

초기 엘레베이터 위치가 4층이기 때문에 

리셋되었을때 엘레베이터가 4층에 위치하지 않는다면 4층으로 이동해야 한다.

엘레베이터 위치 초기화 모드를 통해 엘레베이터의 위치를 수동으로 조작할 수 있다.



#### 엘레베이터 작동 모드

![image-20231224190302760](.\README.assets\image-20231224190302760.png)

숫자키(1~4)를 누르면 알아서 이동한다.

#### 모드 바꾸는 법

![image-20231224185924649](.\README.assets\image-20231224185924649.png)

nucleo보드에 달린 버튼(리셋 버튼 말고) 누르면 모드가 바뀐다.

### 엘레베이터 모형 사진

![image-20231224191035607](.\README.assets\image-20231224191035607.png)

![image-20231224191047426](.\README.assets\image-20231224191047426.png)

![image-20231224191058997](.\README.assets\image-20231224191058997.png)

![image-20231224191106538](.\README.assets\image-20231224191106538.png)
