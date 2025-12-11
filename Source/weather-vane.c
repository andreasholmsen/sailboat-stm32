#include "weather-vane.h"

/**
 * Variables for the incremental encoder -> girouette
 */
#define ENCODER_TIM TIM2
#define ENCODER_TIM_NUM 2
#define MAX_ENCODER_VALUE 1440 // it is the ARR for ENCODER_TIM

/**
 * Variables for the PWM -> servo moteur
 */
#define PWM_TIM TIM4
#define PWM_TIM_NUM 4
#define PWM_OUT_CHANNEL 1
#define PWM_ARR 1439
#define PWM_PSC 999



/* only a global variable to watch the duty value in the debugger. */
float watched_duty = 0.0;

/**
 *  * Returns the new duty cycle depending on the ENCODER value.
 * The value of the ENCODER->CNT is between 0 and 1440. It divides it by 4 to
 *  get the degree of the encoder.
 *  then it applies the function :
 *  f : x -> {
 *      0 if x in [0, 45]||[315, 360]
 *      Ax + b if x in [45, 180]
 *      -Ax + b if x in [180, 315]
 *  }
 *  f([0, 360]) = [0, 1] !!!
 *  so finally it apply theta such as :
 *  - theta convert the value between [0, 1] to [0.05, Ø.1]
 *  - theta([0, 1]) = [0.05, 0.1]
 *
 * @param ENCODER is the timer where the incremental encoder is setup.
 * @return the new_duty
 */
float compute_duty_cycle(TIM_TypeDef *ENCODER){
	uint32_t temp = ENCODER->CNT;
	float encoder_value = temp / 4.0;
	float conversion = 0.0;
		
	if(45 <= encoder_value && encoder_value <=180){
		conversion = (encoder_value/135.0) - (1/3.0);
	}else if( 180 <= encoder_value && encoder_value <= 315){
		conversion = (7.0/3.0) - (encoder_value/135.0); 
	}
	float new_duty = (0.05 *conversion) + 0.05 ;
	watched_duty = new_duty;
	return new_duty;
}

/**
 * Updates the duty cycle of the pwm with the value of the encode.
 */

void update_duty_cycle(void){
	float new_duty = compute_duty_cycle(ENCODER_TIM);
	PWMSetDuty(PWM_TIM, new_duty, PWM_OUT_CHANNEL);
}

/**
 * It sets up the requirements for the mast control !
 *
 * - sets up the incremental encoder for the weather vane
 * - sets up the PWM for the servo motor.
 *
 * - sets up the timer interuptions for convert the encoder value to a duty cycle for the pwm
 *
 */
void setup_weather_vane(){
		// TIM SETUP
		InitTimer(PWM_TIM, PWM_ARR, PWM_PSC);
        InitTimer(ENCODER_TIM, MAX_ENCODER_VALUE, 0);
					
		// PERIPH SETUP
		setup_encoder(ENCODER_TIM);
		InitPWM(PWM_TIM, 0.05, PWM_OUT_CHANNEL); 
}

void wait_sync(GPIO_TypeDef *GPIO, const char BROCHE, TIM_TypeDef *ENCODER){
	GPIO->IDR = 0;
	while((GPIO->IDR & (1<<BROCHE)) == 0){
	}
	ENCODER->CNT = 0;
}

void InitGirouette(int WaitForSync) {
	/* GPIO for incremental encoder */
	InitGPIO(GPIOA, 0, GPIO_MODE_FLOATING_INPUT); //A
	InitGPIO(GPIOA, 1, GPIO_MODE_FLOATING_INPUT); //B
	InitGPIO(GPIOA, 6, GPIO_MODE_FLOATING_INPUT); //Index
	
	/* GPIO PWM out for servo motor */
	InitGPIO(GPIOB, 6, GPIO_MODE_AF_PP_2MHZ );
	
	setup_weather_vane();

	if (WaitForSync) wait_sync(GPIOA, 6, ENCODER_TIM);
}