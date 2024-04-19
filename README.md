# ahrs_stm32

hardware:
- mcu: stm32l431rct6
- peripherals: imu, baro, eeprom
- stlink

toolchain:
- code generation: stm32cube MX
- editor: vscode
- compiler: arm-none-eabi
- build: cmake, ninja
- debug: cortex-debug vscode extension, openocd, stm32cube Monitor