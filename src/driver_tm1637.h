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
 * @file      driver_tm1637.h
 * @brief     driver tm1637 header file
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

#ifndef DRIVER_TM1637_H
#define DRIVER_TM1637_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tm1637_driver tm1637 driver function
 * @brief    tm1637 driver modules
 * @{
 */

/**
 * @addtogroup tm1637_basic_driver
 * @{
 */

/**
 * @brief tm1637 address mode enumeration definition
 */
typedef enum
{
    TM1637_ADDRESS_MODE_INC = 0x00,        /**< auto increment 1 mode */
    TM1637_ADDRESS_MODE_FIX = 0x01,        /**< fixed address mode */
} tm1637_address_mode_t;

/**
 * @brief tm1637 bool enumeration definition
 */
typedef enum
{
    TM1637_BOOL_FALSE = 0x00,        /**< false */
    TM1637_BOOL_TRUE  = 0x01,        /**< true */
} tm1637_bool_t;

/**
 * @brief tm1637 pulse width enumeration definition
 */
typedef enum
{
    TM1637_PULSE_WIDTH_1_DIV_16  = 0x00,        /**< 1/16 */
    TM1637_PULSE_WIDTH_2_DIV_16  = 0x01,        /**< 2/16 */
    TM1637_PULSE_WIDTH_4_DIV_16  = 0x02,        /**< 4/16 */
    TM1637_PULSE_WIDTH_10_DIV_16 = 0x03,        /**< 10/16 */
    TM1637_PULSE_WIDTH_11_DIV_16 = 0x04,        /**< 11/16 */
    TM1637_PULSE_WIDTH_12_DIV_16 = 0x05,        /**< 12/16 */
    TM1637_PULSE_WIDTH_13_DIV_16 = 0x06,        /**< 13/16 */
    TM1637_PULSE_WIDTH_14_DIV_16 = 0x07,        /**< 14/16 */
} tm1637_pulse_width_t;

/**
 * @brief tm1637 number enumeration definition
 */
typedef enum
{
    TM1637_NUMBER_0 = 0x3F,        /**< 0 */
    TM1637_NUMBER_1 = 0x06,        /**< 1 */
    TM1637_NUMBER_2 = 0x5B,        /**< 2 */
    TM1637_NUMBER_3 = 0x4F,        /**< 3 */
    TM1637_NUMBER_4 = 0x66,        /**< 4 */
    TM1637_NUMBER_5 = 0x6D,        /**< 5 */
    TM1637_NUMBER_6 = 0x7D,        /**< 6 */
    TM1637_NUMBER_7 = 0x07,        /**< 7 */
    TM1637_NUMBER_8 = 0x7F,        /**< 8 */
    TM1637_NUMBER_9 = 0x6F,        /**< 9 */
} tm1637_number_t;

/**
 * @brief tm1637 handle structure definition
 */
typedef struct tm1637_handle_s
{
    uint8_t (*iic_init)(void);                                                        /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                      /**< point to an iic_deinit function address */
    uint8_t (*iic_write_cmd_custom)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write_cmd_custom function address */
    uint8_t (*iic_read_cmd_custom)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd_custom function address */
    void (*delay_ms)(uint32_t ms);                                                    /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                  /**< point to a debug_print function address */
    uint8_t inited;                                                                   /**< inited flag */
    uint8_t display_conf;                                                             /**< display configure */
    uint8_t data_conf;                                                                /**< data configure */
} tm1637_handle_t;

/**
 * @brief tm1637 information structure definition
 */
typedef struct tm1637_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} tm1637_info_t;

/**
 * @}
 */

/**
 * @defgroup tm1637_link_driver tm1637 link driver function
 * @brief    tm1637 link driver modules
 * @ingroup  tm1637_driver
 * @{
 */

/**
 * @brief     initialize tm1637_handle_t structure
 * @param[in] HANDLE points to a tm1637 handle structure
 * @param[in] STRUCTURE is tm1637_handle_t
 * @note      none
 */
#define DRIVER_TM1637_LINK_INIT(HANDLE, STRUCTURE)                  memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a tm1637 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_TM1637_LINK_IIC_INIT(HANDLE, FUC)                   (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a tm1637 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_TM1637_LINK_IIC_DEINIT(HANDLE, FUC)                 (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write_cmd_custom function
 * @param[in] HANDLE points to a tm1637 handle structure
 * @param[in] FUC points to an iic_write_cmd_custom function address
 * @note      none
 */
#define DRIVER_TM1637_LINK_IIC_WRITE_COMMAND_CUSTOM(HANDLE, FUC)   (HANDLE)->iic_write_cmd_custom = FUC

/**
 * @brief     link iic_read_cmd_custom function
 * @param[in] HANDLE points to a tm1637 handle structure
 * @param[in] FUC points to an iic_read_cmd_custom function address
 * @note      none
 */
#define DRIVER_TM1637_LINK_IIC_READ_COMMAND_CUSTOM(HANDLE, FUC)    (HANDLE)->iic_read_cmd_custom = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a tm1637 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_TM1637_LINK_DELAY_MS(HANDLE, FUC)                   (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a tm1637 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_TM1637_LINK_DEBUG_PRINT(HANDLE, FUC)                (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup tm1637_basic_driver tm1637 basic driver function
 * @brief    tm1637 basic driver modules
 * @ingroup  tm1637_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a tm1637 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1637_info(tm1637_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a tm1637 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t tm1637_init(tm1637_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a tm1637 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t tm1637_deinit(tm1637_handle_t *handle);

/**
 * @brief     clear segment
 * @param[in] *handle points to a tm1637 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear segment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1637_clear_segment(tm1637_handle_t *handle);

/**
 * @brief     write segment
 * @param[in] *handle points to a tm1637 handle structure
 * @param[in] addr is the start address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write segment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 addr + len > 6
 * @note      none
 */
uint8_t tm1637_write_segment(tm1637_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len);

/**
 * @brief      read segment
 * @param[in]  *handle points to a tm1637 handle structure
 * @param[out] *seg points to a seg buffer
 * @param[out] *k points to a k buffer
 * @return     status code
 *             - 0 success
 *             - 1 read segment failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1637_read_segment(tm1637_handle_t *handle, uint8_t *seg, uint8_t *k);

/**
 * @brief     set pulse width
 * @param[in] *handle points to a tm1637 handle structure
 * @param[in] width is the pulse width
 * @return    status code
 *            - 0 success
 *            - 1 set pulse width failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1637_set_pulse_width(tm1637_handle_t *handle, tm1637_pulse_width_t width);

/**
 * @brief      get pulse width
 * @param[in]  *handle points to a tm1637 handle structure
 * @param[out] *width points to a pulse width buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1637_get_pulse_width(tm1637_handle_t *handle, tm1637_pulse_width_t *width);

/**
 * @brief     enable or disable display
 * @param[in] *handle points to a tm1637 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set display failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1637_set_display(tm1637_handle_t *handle, tm1637_bool_t enable);

/**
 * @brief      get display status
 * @param[in]  *handle points to a tm1637 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1637_get_display(tm1637_handle_t *handle, tm1637_bool_t *enable);

/**
 * @brief     set address mode
 * @param[in] *handle points to a tm1637 handle structure
 * @param[in] mode is the address mode
 * @return    status code
 *            - 0 success
 *            - 1 set address mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1637_set_address_mode(tm1637_handle_t *handle, tm1637_address_mode_t mode);

/**
 * @brief      get address mode
 * @param[in]  *handle points to a tm1637 handle structure
 * @param[out] *mode points to an address mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1637_get_address_mode(tm1637_handle_t *handle, tm1637_address_mode_t *mode);

/**
 * @brief     enable or disable test mode
 * @param[in] *handle points to a tm1637 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set test mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1637_set_test_mode(tm1637_handle_t *handle, tm1637_bool_t enable);

/**
 * @brief      get test mode status
 * @param[in]  *handle points to a tm1637 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1637_get_test_mode(tm1637_handle_t *handle, tm1637_bool_t *enable);

/**
 * @}
 */

/**
 * @defgroup tm1637_extern_driver tm1637 extern driver function
 * @brief    tm1637 extern driver modules
 * @ingroup  tm1637_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a tm1637 handle structure
 * @param[in] cmd is the send command
 * @param[in] *data points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1637_set_reg(tm1637_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a tm1637 handle structure
 * @param[in]  cmd is the send command
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1637_get_reg(tm1637_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
