# STM32 Autonomous Sailboat

> Autonomous sailboat on STM32: reads a weather vane and trims the sails with PWM servo control.

## About

Bare-metal firmware for an autonomous model sailboat, developed as an embedded systems project at INSA Toulouse. The board reads the wind direction from a weather vane ("girouette") fitted with an incremental quadrature encoder, and trims the sail through a hobby servo driven by PWM. A second channel receives steering commands over UART (a signed byte from −100 to +100) and translates them into a direction bit plus a PWM duty cycle for the rudder/propulsion motor driver. Everything is written directly against the STM32F1 registers — no HAL or SPL — on top of a small in-house driver layer (`Pilotes/`).

## Tech stack / Hardware

- **MCU:** STM32F103RB (ARM Cortex-M3, 8 MHz HSE, 72 MHz system clock)
- **Weather vane:** incremental encoder (1440 counts/rev, 0.25°/step) read by TIM2 in hardware encoder mode — A/B on PA0/PA1, index on PA6 for zero synchronization
- **Sail servo:** 50 Hz PWM on TIM4 CH1 (PB6), 1–2 ms pulses (5–10 % duty)
- **Steering/motor output:** direction bit on PA9 + 20 kHz PWM on TIM1 CH1 (PA8)
- **Command link:** USART3 at 9600 baud (TX PB10 / RX PB11), interrupt-driven RX
- **Scheduling:** TIM3 tick at 50 Hz polled in the main loop; navigation updated every 20 ticks
- **Toolchain:** Keil µVision 5 (MDK-ARM), Arm Compiler 6 (armclang), CMSIS + Keil `STM32F1xx_DFP` 2.4.1 device pack

### Control logic

The wind angle (encoder count ÷ 4, in degrees) is mapped to a sail-servo duty cycle:

- **0–45° and 315–360°** (facing the wind): sail held at the minimum position
- **45–180°:** linear ramp from minimum to maximum
- **180–315°:** mirrored ramp back down

The resulting value in [0, 1] is scaled to the 5–10 % duty range expected by the servo. For steering, the sign of the received UART byte sets the direction pin and its magnitude (|v|/100) sets the motor PWM duty. The weather-vane task is currently commented out in `Source/principal.c` and can be re-enabled via `InitGirouette()` / `update_duty_cycle()`.

## Build & flash

The project is a Keil µVision 5 workspace (requires the CMSIS and Keil `STM32F1xx_DFP` packs):

1. Open `Projet0.uvprojx` in µVision.
2. Pick a target:
   - **Reel** — real hardware; build, then flash/debug through ST-LINK (debug init: `reel.ini`).
   - **Simulation** — µVision software simulator, no board needed (debug init: `simu.ini`, 8 MHz oscillator).
3. Build (F7), then Download or start a debug session.

## Project structure

```
Source/                  Application code
├── principal.c          main(): clock/GPIO setup, TIM3 tick loop
├── weather-vane.c/.h    Encoder → sail-servo duty cycle mapping
└── Navigation.c/.h      UART command → direction bit + motor PWM
Pilotes/                 Register-level drivers
├── GPIO.c/.h            Pin configuration and read/write
├── timer.c/.h           Timer init, start/stop, UIF polling
├── PWM.c/.h             PWM channel setup and duty control
├── UART.c/.h            USART init and char I/O
├── incremental-encoder.c/.h  Timer encoder-mode setup
└── interuption.c/.h     NVIC setup + interrupt handler dispatch
RTE/, DebugConfig/       Keil run-time environment and debug configs
Projet0.uvprojx/.uvoptx  µVision project (targets: Reel, Simulation)
```
