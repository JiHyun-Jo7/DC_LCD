# Simple Airfan (간단한 선풍기)
---
### 개발 환경 (IDE)
- Tool : STM32CubeIDE 1.13.1
- Board : STM32F411RET
---
### Port Setting
![Setup](https://github.com/JiHyun-Jo7/DC_LCD/assets/141097551/5868322a-918e-4195-9929-24e68d4239bd)
---

<details>
	<summary>Start</summary>
  	<div markdown="1">

![01_stop_to_speed1](https://github.com/JiHyun-Jo7/DC_LCD/assets/141097551/c708ba7c-0f5b-4951-996a-cfb9e87413da)

```
  lcd_init();
  lcd_put_cur(0,0);
  lcd_send_string("Ready to Start");
  HAL_Delay(1000);
  lcd_put_cur(1,0);
  lcd_send_string("Press the Button");
```

- 
- 전원이 들어오면 버튼을 누르기 전까지 메세지가 출력된 상태로 대기한다

```
 if(!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)))		// Button C10 - LED A5 ON
	  {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  flag1 = 1;
		  flag2 = 0;
		  flag3 = 0;

		  TIM3->CCR1 = 500;		// motor speed 1

		  lcd_init();			// LCD Initialization
		  HAL_Delay(100);
		  lcd_put_cur(0,0);
		  lcd_send_string("Speed Level : 1");

	  }

```
- Press button D1 (level 1) to rotate the motor to intensity 500  
LED A5 connected to the button will turn on  
The LCD clears the previously displayed message and displays the current level
- 약풍으로 설정한 버튼 C10을 누르면 모터가 500의 강도로 돌기 시작한다  
버튼과 연결된 LED A5에 불이 켜지고, LCD에 적혀있던 텍스트는 지워지고 현재 단계가 출력된다

   </div>
</details>

<details>
	<summary>Lv1->Lv2</summary>
  	<div markdown="1">

![02_speed1_to_speed2](https://github.com/JiHyun-Jo7/DC_LCD/assets/141097551/56e346b6-99af-4334-8519-3df9efa3c3ba)

```
	  if(!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)))		// Button C11 - LED A6 ON
	  {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		  flag1 = 0;
		  flag2 = 1;
		  flag3 = 0;

		  TIM3->CCR1=750;		// motor speed 2

		  lcd_init();			// LCD Initialization
		  HAL_Delay(100);
		  lcd_put_cur(0,0);
		  lcd_send_string("Speed Level : 2");
	  }
```
- Press button C11 (level 2) to rotate the motor to an intensity of 750  
LED A5 connected to button C10 turns off and LED A6 connected to button C11 turns on  
The previously displayed message on the LCD is erased and a new message is displayed
- 중풍으로 설정한 버튼 C11을 누르면 모터가 750 세기로 돌기 시작한다  
버튼 C10과 연결된 LED A5가 꺼지고 버튼C11과 연결된 LED A6가 켜진다  
LCD에 적혀있던 텍스트는 지워지고 현재 단계가 출력된다

   </div>
</details>

<details>
	<summary>Lv2->Lv3</summary>
  	<div markdown="1">

![03_speed2_to_speed3](https://github.com/JiHyun-Jo7/DC_LCD/assets/141097551/a1772341-79f4-4863-ba0e-6fcc2aaccb59)

```
if(!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)))		// Button C12 - LED A7 ON
	  {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
		  flag1 = 0;
		  flag2 = 0;
		  flag3 = 1;

		  TIM3->CCR1=900;		// motor speed 3

		  lcd_init();
		  HAL_Delay(100);
		  lcd_put_cur(0,0);
		  lcd_send_string("Speed Level : 3");
	  }
```

- Press button C12 (level 3) to rotate the motor to intensity 900  
The LCD and LED(A7) changes are the same as in 1->2
- 강풍으로 설정한 버튼 C12를 누르면 모터가 세기 900으로 돌기 시작한다  
LED(A7)와 LCD의 변화는 1->2 에서 설명한 것과 동일하다

   </div>
</details>

<details>
	<summary>Stop</summary>
  	<div markdown="1">

![04_speed3_to_stop](https://github.com/JiHyun-Jo7/DC_LCD/assets/141097551/becc25b6-3083-4838-b45d-60f2f51a6ab6)

```
if(!(flag1==0&&flag2==0&&flag3==0))
	  {
		  if(!(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)))		// Button D2 - LED B6 ON (3 times)
		  {
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
			  flag1 = 0;
			  flag2 = 0;
			  flag3 = 0;

			  TIM3->CCR1=0;

			  for(int i=0; i<3; i++)
			  {
				  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
				  HAL_Delay(300);
				  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
				  HAL_Delay(300);
			  }
			  lcd_init();
			  HAL_Delay(100);
			  lcd_put_cur(0,0);
			  lcd_send_string("Stop");
			  HAL_Delay(1000);
			  lcd_put_cur(1,0);
			  lcd_send_string("See U Again!");
			  HAL_Delay(1000);
			  lcd_init();
		  }
	  }

```
- Pressing button D2 (set to stop) stops the motor and turns off all LEDs connected to buttons C10, 11, and 12  
LED B6 (connected to button D2) flashes three times and then turns off  
The LCD displays an exit message and disappears after 1 second
- The stop button only works when the fan is running
- 종료로 설정한 버튼 D2을 누르면 모터가 멈추고 버튼 C10, 11, 12와 연결된 LED가 꺼진다  
버튼 D2와 연결된 LED가 3회 깜빡인 후 꺼지며,
LCD 에 종료 메세지가 표시된 후 1초 후 사라진다
- 선풍기가 작동 중일때만 종료버튼은 작동한다
   </div>
</details>
