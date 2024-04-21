# ahrs_stm32

hardware:
- mcu: stm32l431rct6
- peripherals: imu, baro, eeprom
- debugger: stlink

toolchain:
- code generation: stm32cube MX
- editor: vscode
- compiler: arm-none-eabi
- build: cmake, ninja
- debug: cortex-debug vscode extension, openocd, stm32cube Monitor



<img src=".\Documents\first_run_ok.png" alt="first_run_ok" style="zoom:100%;" />