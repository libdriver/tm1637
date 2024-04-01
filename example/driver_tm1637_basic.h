/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_tm1637_basic.h
 * @brief     driver tm1637 basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-03-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/03/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_TM1637_BASIC_H
#define DRIVER_TM1637_BASIC_H

#include "driver_tm1637_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tm1637_example_driver tm1637 example driver function
 * @brief    tm1637 example driver modules
 * @ingroup  tm1637_driver
 * @{
 */

/**
 * @brief tm1637 basic example default definition
 */
#define TM1637_BASIC_DEFAULT_ADDRESS_MODE        TM1637_ADDRESS_MODE_INC          /**< auto increment 1 mode */
#define TM1637_BASIC_DEFAULT_PULSE_WIDTH         TM1637_PULSE_WIDTH_14_DIV_16     /**< 14/16 */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t tm1637_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tm1637_basic_deinit(void);

/**
 * @brief     basic example write
 * @param[in] addr is the start address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t tm1637_basic_write(uint8_t addr, uint8_t *data, uint8_t len);

/**
 * @brief      basic example read
 * @param[out] *seg points to a seg buffer
 * @param[out] *k points to a k buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t tm1637_basic_read(uint8_t *seg, uint8_t *k);

/**
 * @brief  basic example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t tm1637_basic_clear(void);

/**
 * @brief  basic example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t tm1637_basic_display_on(void);

/**
 * @brief  basic example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t tm1637_basic_display_off(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
