include(../../../cmake/ArmDirectories)

include_directories(
        ${ARM_LIBS_DIR}/Drivers/CMSIS/Include
        ${ARM_LIBS_DIR}/Drivers/CMSIS/Device/ST/STM32F0xx/Include
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Inc
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy
)

set(HAL
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dac.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_exti.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_utils.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_usart.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_usart.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_i2c.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rcc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dma.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_pwr.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_iwdg.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cec.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crs.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_irda.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_wwdg.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_comp.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_can.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tsc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2s.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_comp.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_adc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_gpio.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_spi.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_tim.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smbus.c
        ${ARM_LIBS_DIR}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rtc.c
)

set(ARM_LIBS_SOURCES ${HAL})

