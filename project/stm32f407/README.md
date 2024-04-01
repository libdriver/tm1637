### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TM1637

#### 3.1 Command Instruction

1. Show tm1637 chip and driver information.

    ```shell
    tm1637 (-i | --information)  
    ```

2. Show tm1637 help.

    ```shell
    tm1637 (-h | --help)        
    ```

3. Show tm1637 pin connections of the current board.

    ```shell
    tm1637 (-p | --port)        
    ```

4. Run tm1637 write test.

    ```shell
    tm1637 (-t write  | --test=write )      
    ```

5. Run tm1637 read test, num means test times.

    ```shell
    tm1637 (-t read | --test=read) [--times=<num>]    
    ```

8. Run tm1637 read function.

    ```shell
    tm1637 (-e read | --example=read)    
    ```

8. Run tm1637 write function,  address is the start address and the range is 0 - 7.

    ```shell
    tm1637 (-e write | --example=write) [--addr=<address>] [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]   
    ```
    
9. Run tm1637 init function.

    ```shell
    tm1637 (-e init | --example=init)

9. Run tm1637 deinit function.

    ```shell
    tm1637 (-e deinit | --example=deinit)

9. Run tm1637 on function.

    ```shell
    tm1637 (-e on | --example=on)

9. Run tm1637 off function.

    ```shell
    tm1637 (-e off | --example=off)

#### 3.2 Command Example

```shell
tm1637 -i

tm1637: chip is Titan Micro Electronics TM1637.
tm1637: manufacturer is Titan Micro Electronics.
tm1637: interface is GPIO.
tm1637: driver version is 1.0.
tm1637: min supply voltage is 3.3V.
tm1637: max supply voltage is 5.5V.
tm1637: max current is 200.00mA.
tm1637: max temperature is 125.0C.
tm1637: min temperature is -40.0C.
```

```shell
tm1637 -p

tm1637: IIC interface SCL connected to GPIOB PIN8.
tm1637: IIC interface SDA connected to GPIOB PIN9.
```

```shell
tm1637 -t write

tm1637: chip is Titan Micro Electronics TM1637.
tm1637: manufacturer is Titan Micro Electronics.
tm1637: interface is IIC.
tm1637: driver version is 1.0.
tm1637: min supply voltage is 3.3V.
tm1637: max supply voltage is 5.5V.
tm1637: max current is 200.00mA.
tm1637: max temperature is 125.0C.
tm1637: min temperature is -40.0C.
tm1637: start write test.
tm1637: address auto increment mode.
tm1637: address fix mode.
tm1637: set pulse width 12.
tm1637: set pulse width 10.
tm1637: set pulse width 2.
tm1637: display off.
tm1637: display on.
tm1637: finish write test.
```

```shell
tm1637 -t read --times=3

tm1637: chip is Titan Micro Electronics TM1637.
tm1637: manufacturer is Titan Micro Electronics.
tm1637: interface is IIC.
tm1637: driver version is 1.0.
tm1637: min supply voltage is 3.3V.
tm1637: max supply voltage is 5.5V.
tm1637: max current is 200.00mA.
tm1637: max temperature is 125.0C.
tm1637: min temperature is -40.0C.
tm1637: start read test.
tm1637: seg: 0x02.
tm1637: k: 0x02.
tm1637: seg: 0x03.
tm1637: k: 0x02.
tm1637: seg: 0x05.
tm1637: k: 0x02.
tm1637: finish read test.
```

```shell
tm1637 -e init

tm1637: init.
```

```shell
tm1637 -e read

tm1637: seg: 0x05.
tm1637: k: 0x02.
```

```shell
tm1637 -e write --addr=0 --num=0

tm1637: write address 0 number 0.
```
```shell
tm1637 -e on

tm1637: display on.
```
```
tm1637 -e off

tm1637: display off.
```
```shell
tm1637 -e deinit

tm1637: deinit.
```
```shell
tm1637 -h

Usage:
  tm1637 (-i | --information)
  tm1637 (-h | --help)
  tm1637 (-p | --port)
  tm1637 (-t write | --test=write)
  tm1637 (-t read | --test=read) [--times=<num>]
  tm1637 (-e init | --example=init)
  tm1637 (-e deinit | --example=deinit)
  tm1637 (-e on | --example=on)
  tm1637 (-e off | --example=off)
  tm1637 (-e write | --example=write) [--addr=<address>]
         [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]
  tm1637 (-e read | --example=read)

Options:
      --addr=<address>                   Set the start address and the range is 0-7.([default: 0])
  -e <init | deinit | write | read | on | off>, --example=<init | deinit | write | read | on | off>
                                         Run the driver example.
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
  -p, --port                             Display the pin connections of the current board.
      --num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>([default: 0])
                                         Set display number.
  -t <read | write>, --test=<read | write>.
                                         Run the driver test.
      --times=<num>                      Set the running times.([default: 3])
```
