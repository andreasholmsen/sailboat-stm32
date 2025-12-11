#include "stm32f10x.h"
#include "incremental-encoder.h"
#include "PWM.h"
#include "interuption.h"
#include "GPIO.h"

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
#define PWM_OUT_CHANNEL 1
#define PWM_ARR 1439
#define PWM_PSC 999


float compute_duty_cycle(TIM_TypeDef *ENCODER);
void update_duty_cycle(void);
void setup_weather_vane();

void wait_sync(GPIO_TypeDef *GPIO, const char BROCHE, TIM_TypeDef *ENCODER);

void InitGirouette(int WaitForSync);