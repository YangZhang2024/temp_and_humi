
#ifndef DHT_11_H
#define DHT_11_H

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "delay.h"

#define ONE_WIRE_DQ_GPIO_PORT                GPIOA
#define ONE_WIRE_DQ_GPIO_PIN                 GPIO_PIN_0
#define DS18B20_DQ_GPIO_CLK_ENABLE()        do { __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define ONE_WIRE_DQ_OUT(x)   do { x ? \
                                HAL_GPIO_WritePin(ONE_WIRE_DQ_GPIO_PORT, ONE_WIRE_DQ_GPIO_PIN, GPIO_PIN_SET) : \
                                HAL_GPIO_WritePin(ONE_WIRE_DQ_GPIO_PORT, ONE_WIRE_DQ_GPIO_PIN, GPIO_PIN_RESET); \
                              } while(0)                                                       /* 数据端口输出 */
#define ONE_WIRE_DQ_IN       HAL_GPIO_ReadPin(ONE_WIRE_DQ_GPIO_PORT, ONE_WIRE_DQ_GPIO_PIN)     /* 数据端口输入 */

/**
 *
 * @param temp
 * @param humidity
 * @return 1 success 0 failed
 */
uint8_t get_humidity(double *temp, double* humidity);

#endif