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
 * @file      driver_tm1637.c
 * @brief     driver tm1637 source file
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

#include "driver_tm1637.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Titan Micro Electronics TM1637"        /**< chip name */
#define MANUFACTURER_NAME         "Titan Micro Electronics"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.3f                                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                                    /**< chip max supply voltage */
#define MAX_CURRENT               200.0f                                  /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                                  /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                                  /**< chip max operating temperature */
#define DRIVER_VERSION            1000                                    /**< driver version */

/**
 * @brief chip command definition
 */
#define TM1637_COMMAND_DATA           (1 << 6)        /**< data command setting */
#define TM1637_COMMAND_DISPLAY        (2 << 6)        /**< display and control command setting */
#define TM1637_COMMAND_ADDRESS        (3 << 6)        /**< address command setting */

/**
 * @brief     high low shift
 * @param[in] data is the input data
 * @return    output data
 * @note      none
 */
static uint8_t a_high_low_shift(uint8_t data)
{
    uint8_t output;

    output = (data << 4) | (data >> 4);                              /* part 1 */
    output = ((output << 2) & 0xCC) | ((output >> 2) & 0x33);        /* part 2 */
    output = ((output << 1) & 0xAA) | ((output >> 1) & 0x55);        /* part 3 */

    return output;                                                   /* return output */
}

/**
 * @brief     iic write
 * @param[in] *handle points to a tm1637 handle structure
 * @param[in] cmd is the set command
 * @param[in] *buf points to a data buffer
 * @param[in] len is the buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_tm1637_write(tm1637_handle_t *handle, uint8_t cmd, uint8_t *buf, uint16_t len)
{
    uint8_t inner_buffer[16];
    uint16_t i;

    if (len > 16)                                                                       /* check len */
    {
        return 1;                                                                       /* return error */
    }
    for (i = 0; i < len; i++)                                                           /* loop all */
    {
        inner_buffer[i] = a_high_low_shift(buf[i]);                                     /* shift */
    }
    if (handle->iic_write_cmd_custom(a_high_low_shift(cmd), inner_buffer, len) != 0)    /* write data */
    {
        return 1;                                                                       /* return error */
    }

    return 0;                                                                           /* success return 0 */
}

/**
 * @brief      iic read
 * @param[in]  *handle points to a tm1637 handle structure
 * @param[in]  cmd is the set command
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_tm1637_read(tm1637_handle_t *handle, uint8_t cmd, uint8_t *buf, uint16_t len)
{
    uint16_t i;

    if (handle->iic_read_cmd_custom(a_high_low_shift(cmd), buf, len) != 0)    /* read data */
    {
        return 1;                                                             /* return error */
    }
    for (i = 0; i < len; i++)                                                 /* loop all */
    {
        buf[i] = a_high_low_shift(buf[i]);                                    /* shift */
    }

    return 0;                                                                 /* success return 0 */
}

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
uint8_t tm1637_init(tm1637_handle_t *handle)
{
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->debug_print == NULL)                                        /* check debug_print */
    {
        return 3;                                                           /* return error */
    }
    if (handle->iic_init == NULL)                                           /* check iic_init */
    {
        handle->debug_print("tm1637: iic_init is null.\n");                 /* iic_init is null */

        return 3;                                                           /* return error */
    }
    if (handle->iic_deinit == NULL)                                         /* check iic_deinit */
    {
        handle->debug_print("tm1637: iic_deinit is null.\n");               /* iic_deinit is null */

        return 3;                                                           /* return error */
    }
    if (handle->iic_write_cmd_custom == NULL)                               /* check iic_write_cmd_custom */
    {
        handle->debug_print("tm1637: iic_write_cmd_custom is null.\n");     /* iic_write_cmd_custom is null */

        return 3;                                                           /* return error */
    }
    if (handle->iic_read_cmd_custom == NULL)                                /* check iic_read_cmd_custom */
    {
        handle->debug_print("tm1637: iic_read_cmd_custom is null.\n");      /* iic_read_cmd_custom is null */

        return 3;                                                           /* return error */
    }
    if (handle->delay_ms == NULL)                                           /* check delay_ms */
    {
        handle->debug_print("tm1637: delay_ms is null.\n");                 /* delay_ms is null */

        return 3;                                                           /* return error */
    }

    if (handle->iic_init() != 0)                                            /* iic init */
    {
        handle->debug_print("tm1637: iic init failed.\n");                  /* iic init failed */

        return 4;                                                           /* return error */
    }
    handle->data_conf = 0x00;                                               /* init 0 */
    handle->display_conf = 0x00;                                            /* init 0  */
    handle->inited = 1;                                                     /* flag inited */

    return 0;                                                               /* success return 0 */
}

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
uint8_t tm1637_deinit(tm1637_handle_t *handle)
{
    uint8_t res;
    uint8_t cmd;

    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }

    handle->display_conf &= ~(1 << 3);                          /* clear settings */
    cmd = TM1637_COMMAND_DISPLAY | handle->display_conf;        /* set the command */
    if (a_tm1637_write(handle, cmd, NULL, 0) != 0)              /* write the command */
    {
        handle->debug_print("tm1637: power down failed.\n");    /* power down failed */

        return 4;                                               /* return error */
    }

    res = handle->iic_deinit();                                 /* close iic */
    if (res != 0)                                               /* check the result */
    {
        handle->debug_print("tm1637: iic deinit failed.\n");    /* iic deinit failed */

        return 1;                                               /* return error */
    }
    handle->inited = 0;                                         /* flag close */

    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1637_set_pulse_width(tm1637_handle_t *handle, tm1637_pulse_width_t width)
{
    uint8_t cmd;

    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }

    handle->display_conf &= ~(7 << 0);                          /* clear settings */
    handle->display_conf |= width;                              /* set display conf */
    cmd = TM1637_COMMAND_DISPLAY | handle->display_conf;        /* set the command */
    if (a_tm1637_write(handle, cmd, NULL, 0) != 0)              /* write the command */
    {
        handle->debug_print("tm1637: write failed.\n");         /* write failed */

        return 1;                                               /* return error */
    }

    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1637_get_pulse_width(tm1637_handle_t *handle, tm1637_pulse_width_t *width)
{
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }

    *width = (tm1637_pulse_width_t)(handle->display_conf & 0x7);        /* get width */

    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1637_set_display(tm1637_handle_t *handle, tm1637_bool_t enable)
{
    uint8_t cmd;

    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }

    handle->display_conf &= ~(1 << 3);                          /* clear settings */
    handle->display_conf |= enable << 3;                        /* set display conf */
    cmd = TM1637_COMMAND_DISPLAY | handle->display_conf;        /* set the command */
    if (a_tm1637_write(handle, cmd, NULL, 0) != 0)              /* write the command */
    {
        handle->debug_print("tm1637: write failed.\n");         /* write failed */

        return 1;                                               /* return error */
    }

    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1637_get_display(tm1637_handle_t *handle, tm1637_bool_t *enable)
{
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }

    *enable = (tm1637_bool_t)((handle->display_conf >> 3) & 0x01);      /* get bool */

    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1637_set_address_mode(tm1637_handle_t *handle, tm1637_address_mode_t mode)
{
    uint8_t cmd;

    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }

    handle->data_conf &= ~(1 << 2);                             /* clear settings */
    handle->data_conf |= mode << 2;                             /* set address mode */
    cmd = TM1637_COMMAND_DATA | handle->data_conf;              /* set the command */
    if (a_tm1637_write(handle, cmd, NULL, 0) != 0)              /* write the command */
    {
        handle->debug_print("tm1637: write failed.\n");         /* write failed */

        return 1;                                               /* return error */
    }

    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1637_get_address_mode(tm1637_handle_t *handle, tm1637_address_mode_t *mode)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }

    *mode = (tm1637_address_mode_t)((handle->data_conf >> 2) & 0x01);        /* get address mode */

    return 0;                                                                /* success return 0 */
}

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
uint8_t tm1637_set_test_mode(tm1637_handle_t *handle, tm1637_bool_t enable)
{
    uint8_t cmd;

    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }

    handle->data_conf &= ~(1 << 3);                             /* clear settings */
    handle->data_conf |= enable << 3;                           /* set test mode */
    cmd = TM1637_COMMAND_DATA | handle->data_conf;              /* set the command */
    if (a_tm1637_write(handle, cmd, NULL, 0) != 0)              /* write the command */
    {
        handle->debug_print("tm1637: write failed.\n");         /* write failed */

        return 1;                                               /* return error */
    }

    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1637_get_test_mode(tm1637_handle_t *handle, tm1637_bool_t *enable)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }

    *enable = (tm1637_bool_t)((handle->data_conf >> 3) & 0x01);        /* get test mode */

    return 0;                                                          /* success return 0 */
}

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
uint8_t tm1637_write_segment(tm1637_handle_t *handle, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t i;
    uint8_t cmd;

    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    if (addr + len > 6)                                                 /* check range */
    {
        handle->debug_print("tm1637: addr + len > 6.\n");               /* addr + len > 6 */

        return 4;                                                       /* return error */
    }

    cmd = TM1637_COMMAND_DATA | handle->data_conf;                      /* set the command */
    if (a_tm1637_write(handle, cmd, NULL, 0) != 0)                      /* write the command */
    {
        handle->debug_print("tm1637: write failed.\n");                 /* write failed */

        return 1;                                                       /* return error */
    }
    if ((handle->data_conf & (1 << 2)) != 0)                            /* fixed address mode */
    {
        for (i = 0; i < len; i++)                                       /* loop all */
        {
            cmd = TM1637_COMMAND_ADDRESS | (addr + i);                  /* set the command */
            if (a_tm1637_write(handle, cmd, &data[i], 1) != 0)          /* write the command */
            {
                handle->debug_print("tm1637: write failed.\n");         /* write failed */

                return 1;                                               /* return error */
            }
        }
    }
    else                                                                /* auto increment 1 mode */
    {
        cmd = TM1637_COMMAND_ADDRESS | addr;                            /* set the command */
        if (a_tm1637_write(handle, cmd, data, len) != 0)                /* write the command */
        {
            handle->debug_print("tm1637: write failed.\n");             /* write failed */

            return 1;                                                   /* return error */
        }
    }

    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1637_clear_segment(tm1637_handle_t *handle)
{
    uint8_t i;
    uint8_t cmd;
    uint8_t data[6] = {0};

    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }

    cmd = TM1637_COMMAND_DATA | handle->data_conf;                      /* set the command */
    if (a_tm1637_write(handle, cmd, NULL, 0) != 0)                      /* write the command */
    {
        handle->debug_print("tm1637: write failed.\n");                 /* write failed */

        return 1;                                                       /* return error */
    }
    if ((handle->data_conf & (1 << 2)) != 0)                            /* fixed address mode */
    {
        for (i = 0; i < 6; i++)                                         /* loop all */
        {
            cmd = TM1637_COMMAND_ADDRESS | i;                           /* set the command */
            if (a_tm1637_write(handle, cmd, data + i, 1) != 0)          /* write the command */
            {
                handle->debug_print("tm1637: write failed.\n");         /* write failed */

                return 1;                                               /* return error */
            }
        }
    }
    else                                                                /* auto increment 1 mode */
    {
        cmd = TM1637_COMMAND_ADDRESS;                                   /* set the command */
        if (a_tm1637_write(handle, cmd, data, 6) != 0)                  /* write the command */
        {
            handle->debug_print("tm1637: write failed.\n");             /* write failed */

            return 1;                                                   /* return error */
        }
    }

    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1637_read_segment(tm1637_handle_t *handle, uint8_t *seg, uint8_t *k)
{
    uint8_t cmd;
    uint8_t data;

    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }

    cmd = TM1637_COMMAND_DATA | handle->data_conf | (1 << 1);        /* set the command */
    if (a_tm1637_read(handle, cmd, &data, 1) != 0)                   /* read the command */
    {
        handle->debug_print("tm1637: read failed.\n");               /* read failed */

        return 1;                                                    /* return error */
    }
    *seg = data & 0x7;                                               /* get seg */
    *k = (data >> 3) & 0x03;                                         /* get k */

    return 0;                                                        /* success return 0 */
}

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
uint8_t tm1637_set_reg(tm1637_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }

    if (a_tm1637_write(handle, cmd, data, len) != 0)           /* write the command */
    {
        handle->debug_print("tm1637: write failed.\n");        /* write failed */

        return 1;                                              /* return error */
    }

    return 0;                                                  /* success return 0 */
}

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
uint8_t tm1637_get_reg(tm1637_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len)
{
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    if (handle->inited != 1)                                  /* check handle initialization */
    {
        return 3;                                             /* return error */
    }

    if (a_tm1637_read(handle, cmd, data, len) != 0)           /* read the command */
    {
        handle->debug_print("tm1637: read failed.\n");        /* read failed */

        return 1;                                             /* return error */
    }

    return 0;                                                 /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a tm1637 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1637_info(tm1637_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }

    memset(info, 0, sizeof(tm1637_info_t));                         /* initialize tm1637 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */

    return 0;                                                       /* success return 0 */
}
