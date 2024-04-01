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
 * @file      driver_tm1637_write_test.c
 * @brief     driver tm1637 write test source file
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
 
#include "driver_tm1637_write_test.h"
#include <stdlib.h>

static tm1637_handle_t gs_handle;        /**< tm1637 handle */

/**
 * @brief  write test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t tm1637_write_test(void)
{
    uint8_t res;
    uint8_t number[] = {TM1637_NUMBER_0, TM1637_NUMBER_1, TM1637_NUMBER_2,
                        TM1637_NUMBER_3, TM1637_NUMBER_4, TM1637_NUMBER_5,
                        TM1637_NUMBER_6, TM1637_NUMBER_7, TM1637_NUMBER_8, TM1637_NUMBER_9};
    tm1637_info_t info;

    /* link interface function */
    DRIVER_TM1637_LINK_INIT(&gs_handle, tm1637_handle_t); 
    DRIVER_TM1637_LINK_IIC_INIT(&gs_handle, tm1637_interface_iic_init);
    DRIVER_TM1637_LINK_IIC_DEINIT(&gs_handle, tm1637_interface_iic_deinit);
    DRIVER_TM1637_LINK_IIC_WRITE_COMMAND_CUSTOM(&gs_handle, tm1637_interface_iic_write_cmd_custom);
    DRIVER_TM1637_LINK_IIC_READ_COMMAND_CUSTOM(&gs_handle, tm1637_interface_iic_read_cmd_custom);
    DRIVER_TM1637_LINK_DELAY_MS(&gs_handle, tm1637_interface_delay_ms);
    DRIVER_TM1637_LINK_DEBUG_PRINT(&gs_handle, tm1637_interface_debug_print);
    
    /* get information */
    res = tm1637_info(&info);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        tm1637_interface_debug_print("tm1637: chip is %s.\n", info.chip_name);
        tm1637_interface_debug_print("tm1637: manufacturer is %s.\n", info.manufacturer_name);
        tm1637_interface_debug_print("tm1637: interface is %s.\n", info.interface);
        tm1637_interface_debug_print("tm1637: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1637_interface_debug_print("tm1637: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1637_interface_debug_print("tm1637: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1637_interface_debug_print("tm1637: max current is %0.2fmA.\n", info.max_current_ma);
        tm1637_interface_debug_print("tm1637: max temperature is %0.1fC.\n", info.temperature_max);
        tm1637_interface_debug_print("tm1637: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start write test */
    tm1637_interface_debug_print("tm1637: start write test.\n");
    
    /* tm1637 init */
    res = tm1637_init(&gs_handle);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: init failed.\n");
        
        return 1;
    }
    
    /* address auto increment mode */
    tm1637_interface_debug_print("tm1637: address auto increment mode.\n");
    
    /* set pulse width 14/16 */
    res = tm1637_set_pulse_width(&gs_handle, TM1637_PULSE_WIDTH_14_DIV_16);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set pulse width failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set address auto inc mode */
    res = tm1637_set_address_mode(&gs_handle, TM1637_ADDRESS_MODE_INC);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set address mode failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable test mode */
    res = tm1637_set_test_mode(&gs_handle, TM1637_BOOL_FALSE);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set test mode failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear segment */
    res = tm1637_clear_segment(&gs_handle);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: clear segment failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable display */
    res = tm1637_set_display(&gs_handle, TM1637_BOOL_TRUE);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set display failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write segment */
    res = tm1637_write_segment(&gs_handle, 0x00, &number[0], 6);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: write segment failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 5000ms */
    tm1637_interface_delay_ms(5000);
    
    /* address fix mode */
    tm1637_interface_debug_print("tm1637: address fix mode.\n");
    
    /* set address fix mode */
    res = tm1637_set_address_mode(&gs_handle, TM1637_ADDRESS_MODE_FIX);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set address mode failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write segment */
    res = tm1637_write_segment(&gs_handle, 0x00, &number[1], 6);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: write segment failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 5000ms */
    tm1637_interface_delay_ms(5000);
    
    /* set pulse width */
    tm1637_interface_debug_print("tm1637: set pulse width 12.\n");
    
    /* set pulse width 12/16 */
    res = tm1637_set_pulse_width(&gs_handle, TM1637_PULSE_WIDTH_12_DIV_16);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set pulse width failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1637_interface_delay_ms(3000);
    
    /* set pulse width */
    tm1637_interface_debug_print("tm1637: set pulse width 10.\n");
    
    /* set pulse width 12/16 */
    res = tm1637_set_pulse_width(&gs_handle, TM1637_PULSE_WIDTH_10_DIV_16);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set pulse width failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1637_interface_delay_ms(3000);
    
    /* set pulse width */
    tm1637_interface_debug_print("tm1637: set pulse width 2.\n");
    
    /* set pulse width 2/16 */
    res = tm1637_set_pulse_width(&gs_handle, TM1637_PULSE_WIDTH_2_DIV_16);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set pulse width failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1637_interface_delay_ms(3000);
    
    /* display off */
    tm1637_interface_debug_print("tm1637: display off.\n");
    
    /* disable display */
    res = tm1637_set_display(&gs_handle, TM1637_BOOL_FALSE);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set display failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    /* delay 3000ms */
    tm1637_interface_delay_ms(3000);
    
    /* display on */
    tm1637_interface_debug_print("tm1637: display on.\n");
    
    /* set pulse width 14/16 */
    res = tm1637_set_pulse_width(&gs_handle, TM1637_PULSE_WIDTH_14_DIV_16);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set pulse width failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable display */
    res = tm1637_set_display(&gs_handle, TM1637_BOOL_TRUE);
    if (res != 0)
    {
        tm1637_interface_debug_print("tm1637: set display failed.\n");
        (void)tm1637_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1637_interface_delay_ms(3000);
    
    /* finish write test */
    tm1637_interface_debug_print("tm1637: finish write test.\n");
    (void)tm1637_deinit(&gs_handle);
    
    return 0;
}
