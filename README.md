[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1637

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1637/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TM1637 is a kind of LED (light-emitting diode display) drive control special circuit with keyboard scan interface and it's internally integrated with MCU digital interface, data latch, LED high pressure drive and keyboard scan. This product is in DIP20/SOP20 package type with excellent performance and high quality, which is mainly applicable to the display drive of induction cooker, micro-wave oven and small household electrical appliance.

LibDriver TM1637 is the full function driver of TM1637 launched by LibDriver. LibDriver TM1637 provides digital tube display, keypad scanning and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver TM1637 source files.

/interface includes LibDriver TM1637 IIC platform independent template.

/test includes LibDriver TM1637 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver TM1637 sample code.

/doc includes LibDriver TM1637 offline document.

/datasheet includes TM1637 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_tm1637_basic.h"

uint8_t res;
uint8_t seg;
uint8_t k;
uint8_t number[] = {TM1637_NUMBER_0, TM1637_NUMBER_1, TM1637_NUMBER_2,
                    TM1637_NUMBER_3, TM1637_NUMBER_4, TM1637_NUMBER_5,
                    TM1637_NUMBER_6, TM1637_NUMBER_7, TM1637_NUMBER_8, TM1637_NUMBER_9};

/* init */
res = tm1637_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* write */
res = tm1637_basic_write(0, &number[0], 6);
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

...
    
/* read */
res = tm1637_basic_read(&seg, &k);
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

/* output */
tm1637_interface_debug_print("tm1637: seg: 0x%02X.\n", seg);
tm1637_interface_debug_print("tm1637: k: 0x%02X.\n", k);

...
    
/* on */
res = tm1637_basic_display_on();
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

...
    
/* off */
res = tm1637_basic_display_off();
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

...
    
/* deinit */
(void)tm1637_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/tm1637/index.html](https://www.libdriver.com/docs/tm1637/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.