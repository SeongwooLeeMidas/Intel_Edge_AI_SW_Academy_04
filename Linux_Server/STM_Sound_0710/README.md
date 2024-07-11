## STM32를 활용한 Sound 발생 프로그램

## Circuit Diagram
![image](https://github.com/Seongwoo-Lee97/Intel04_LinuxServer2/assets/170689181/ce7662ae-74b7-49ff-b331-7868f9d30e4f)

## Which Pin to choose
![image](https://github.com/Seongwoo-Lee97/Intel04_LinuxServer2/assets/170689181/1d236fad-d05f-48ca-ac53-1523f96e14be)


PA5번을 사용하고 싶으면 타이머 2번의 채널 1을 쓸 수 있다고 나온다. 그래서 TIM2_CH1 클릭해주자.
클릭하면 노랗게 변하고, TIM2를 눌러주자.

## Check point to know
TIM2 -> Clock Source에서 Internal Clock, Channel에서 PWM Generation CH1
Configuration의 Parameter Settings 에서 Prescaler를 16-1, Counter Period 1000-1로 fix

## Develop
멜로디 코드를 제작해 한 옥타브가 반복되는 프로그램 제작
