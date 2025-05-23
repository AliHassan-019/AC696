/**
 * @file gpio.h
 * @brief
 * @author @zh-jieli.com
 * @version 1.0.0
 * @date 2018-10-11
 */

#ifndef  __JL_GPIO_H__
#define  __JL_GPIO_H__
#include "user_gpio.h"
#include "typedef.h"
enum {
    CH0_UT0_TX,
    CH0_UT1_TX,
    CH0_T0_PWM_OUT,
    CH0_T1_PWM_OUT,
    CH0_RTOSH_CLK,
    CH0_BTOSC_CLK,
    CH0_PLL_12M,
    CH0_UT2_TX,
    CH0_CH0_PWM_H,
    CH0_CH0_PWM_L,
    CH0_CH1_PWM_H,
    CH0_CH1_PWM_L,
    CH0_CH2_PWM_H,
    CH0_CH2_PWM_L,
    CH0_T2_PWM_OUT,
    CH0_T3_PWM_OUT,

    CH1_UT0_TX = 0x10,
    CH1_UT1_TX,
    CH1_T0_PWM_OUT,
    CH1_T1_PWM_OUT,
    CH1_RTOSL_CLK,
    CH1_BTOSC_CLK,
    CH1_PLL_24M,
    CH1_UT2_TX,
    CH1_CH0_PWM_H,
    CH1_CH0_PWM_L,
    CH1_CH1_PWM_H,
    CH1_CH1_PWM_L,
    CH1_CH2_PWM_H,
    CH1_CH2_PWM_L,
    CH1_T2_PWM_OUT,
    CH1_T3_PWM_OUT,

    CH2_UT0_RTS = 0x20,
    CH2_UT1_TX,
    CH2_T0_PWM_OUT,
    CH2_T1_PWM_OUT,
    CH2_PLNK_SCLK,
    CH2_BTOSC_CLK,
    CH2_PLL_24M,
    CH2_UT2_TX,
    CH2_CH0_PWM_H,
    CH2_CH0_PWM_L,
    CH2_CH1_PWM_H,
    CH2_CH1_PWM_L,
    CH2_CH2_PWM_H,
    CH2_CH2_PWM_L,
    CH2_T2_PWM_OUT,
    CH2_T3_PWM_OUT,
};


enum {
    INPUT_CH0,
    INPUT_CH1,
    INPUT_CH2,
    INPUT_CH3,
};

enum gpio_op_mode {
    GPIO_SET = 1,
    GPIO_AND,
    GPIO_OR,
    GPIO_XOR,
};
enum gpio_direction {
    GPIO_OUT = 0,
    GPIO_IN = 1,
};
struct gpio_reg {
    volatile unsigned int out;
    volatile unsigned int in;
    volatile unsigned int dir;
    volatile unsigned int die;
    volatile unsigned int pu;
    volatile unsigned int pd;
    volatile unsigned int hd0;
    volatile unsigned int hd;
    volatile unsigned int dieh;
};

struct gpio_platform_data {
    unsigned int gpio;
};

#define GPIO_PLATFORM_DATA_BEGIN(data) \
	static const struct gpio_platform_data data = { \


#define GPIO_PLATFORM_DATA_END() \
	};
#if 0
#define     IO_DEBUG_0(i,x)       {JL_PORT##i->DIR &= ~BIT(x), JL_PORT##i->OUT &= ~BIT(x);}
#define     IO_DEBUG_1(i,x)       {JL_PORT##i->DIR &= ~BIT(x), JL_PORT##i->OUT |= BIT(x);}
#define     IO_DEBUG_TOGGLE(i,x)  {JL_PORT##i->DIR &= ~BIT(x), JL_PORT##i->OUT ^= BIT(x);}


#else
#define     IO_DEBUG_0(i,x)         {}
#define     IO_DEBUG_1(i,x)         {}
#define     IO_DEBUG_TOGGLE(i,x)    {}

#endif
/**
 * @brief usb_iomode
 *
 * @param enable 1，使能；0，关闭
 */
void usb_iomode(u32 enable);
/**
 * @brief gpio_direction_input
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param dir 1，输入；0，输出
 *
 * @return
 */
int gpio_set_direction(u32 gpio, u32 dir);


/**
 * @brief gpio_direction_input
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，输出1,  0，输出0
 *
 * @return
 */
int gpio_set_output_value(u32 gpio, u32 dir);

/**
 * @brief gpio_dir
 *
 * @param gpio [GPIOA GPIOB GPIOC GPIOD GPIOR GPIOUSB]
 * @param start [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param len  [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param dat 1，输入；0，输出
 *
 * @return
 */
u32 gpio_dir(u32 gpio, u32 start, u32 len, u32 dat, enum gpio_op_mode op);

/**
 * @brief gpio_direction_output
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，输出1；0，输出0
 *
 * @return
 */
int gpio_direction_output(u32 gpio, int value);

/**
 * @brief gpio_out
 *
 * @param gpio [GPIOA GPIOB GPIOC GPIOD GPIOR GPIOUSB]
 * @param start [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param len  [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param dat 1，输入；0，输出
 *
 * @return
 */
u32 gpio_out(u32 gpio, u32 start, u32 len, u32 dat);

/**
 * @brief gpio_set_pull_up
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，上拉；0，不上拉
 *
 * @return
 */
int gpio_set_pull_up(u32 gpio, int value);


/**
 * @brief gpio_set_pu
 *
 * @param gpio [GPIOA GPIOB GPIOC GPIOD GPIOR GPIOUSB]
 * @param start [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param len  [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param dat 1，上拉；0，不上拉
 *
 * @return
 */
u32 gpio_set_pu(u32 gpio, u32 start, u32 len, u32 dat, enum gpio_op_mode op);

/**
 * @brief gpio_set_pull_down
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，下拉；0，不下拉
 *
 * @return
 */
int gpio_set_pull_down(u32 gpio, int value);

/**
 * @brief gpio_set_pd
 *
 * @param gpio [GPIOA GPIOB GPIOC GPIOD GPIOR GPIOUSB]
 * @param start [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param len  [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param dat 1，下拉；0，不下拉
 *
 * @return
 */
u32 gpio_set_pd(u32 gpio, u32 start, u32 len, u32 dat, enum gpio_op_mode op);

/**
 * @brief gpio_set_hd0
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，增强输出；0，不增强输出
 *
 * @return
 */
u32 gpio_set_hd0(u32 gpio, u32 value);

/**
 * @brief gpio_set_hd
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，增强输出；0，不增强输出
 *
 * @return
 */
int gpio_set_hd(u32 gpio, int value);

/**
 * @brief gpio_set_die
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，IO普通输入；0，IO模拟输入
 *
 * @return
 */
int gpio_set_die(u32 gpio, int value);

/**
 * @brief gpio_set_dieh
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，IO普通输入；0，IO模拟输入
 *
 * @return
 */
u32 gpio_set_dieh(u32 gpio, u32 value);

/**
 * @brief gpio_die
 *
 * @param gpio [GPIOA GPIOB GPIOC GPIOD GPIOR GPIOUSB]
 * @param start [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param len  [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param dat 1，IO普通输入；0，IO模拟输入
 *
 * @return
 */
u32 gpio_die(u32 gpio, u32 start, u32 len, u32 dat, enum gpio_op_mode op);

/**
 * @brief gpio_dieh
 *
 * @param gpio [GPIOA GPIOB GPIOC GPIOD GPIOR GPIOUSB]
 * @param start [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param len  [0-15]，GPIOR[0-3]，GPIOUSB[0-1]
 * @param dat 1，IO普通输入；0，IO模拟输入
 *
 * @return
 */
u32 gpio_dieh(u32 gpio, u32 start, u32 len, u32 dat, enum gpio_op_mode op);

/**
 * @brief gpio_set_output_channle
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param clk 参考枚举CHx_UTx_TX，如CH0_UT0_TX
 *
 * @return
 */
u32 gpio_output_channle(u32 gpio, u32 clk);

/**
 * @brief gpio_read
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 *
 * @return
 */
int gpio_read(u32 gpio);

/**
 * @brief gpio_in
 *
 * @param gpio [GPIOA GPIOB GPIOC GPIOD GPIOR GPIOUSB]
 *
 * @return
 */
u32 gpio_in(u32 gpio);
/**
 * @brief gpio_write
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param value 1，输出1；0，输出0
 *
 * @return
 */
u32 gpio_write(u32 gpio, u32 value);

/**
 * @brief gpio_wakeup0 use IN_CHNL0_SEL
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 *
 * @return
 */
u32 gpio_wakeup0(u32 gpio);

/**
 * @brief gpio_irflt_in use IN_CHNL1_SEL
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 *
 * @return
 */
u32 gpio_irflt_in(u32 gpio);

/**
 * @brief gpio_cap_mux use IN_CHNL2_SEL
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 *
 * @return
 */
u32 gpio_cap_mux(u32 gpio);


/**
 * @brief gpio_uart_rx_input
 *
 * @param gpio
 * @param ut
 * @param ch
 *
 * @return
 */
u32 gpio_uart_rx_input(u32 gpio, u32 ut, u32 ch);

/**
 * @brief
 *
 * @return
 */
u32 gpio_close_uart0(void);

/**
 * @brief
 *
 * @return
 */
u32 gpio_close_uart1(void);

/**
 * @brief
 *
 * @return
 */
u32 gpio_close_uart2(void);

/**
 * @brief gpio_set_uart0
 *
 * @param ch 0:3 选择对应IO br22
 *         |ch|tx|rx|
 *         |- |- |- |
 *         |0|PA5_TX|PA6_RX|
 *         |1|PB7_TX|PB8_RX|
 *         |2|PA7_TX|PA8_RX|
 *         |3|预留|预留|
 *         |-1|关闭对应的IO口串口功能|no|
 *
 * @return
 */
u32 gpio_set_uart0(u32 ch);
/**
 * @brief gpio_set_uart1
 *
 * @param ch 0:3 选择对应IO  br22
 *         |ch|tx|rx|
 *         |- |- |- |
 *         |0|PB5_TX|PB6_RX|
 *         |1|预留|预留|
 *         |2|PA1_TX|PA2_RX|
 *         |3|USBDP |USBDM |
 *         |-1|关闭对应的IO口串口功能|no|
 *
 * @return
 */
u32 gpio_set_uart1(u32 ch);
/**
 * @brief gpio_set_uart2
 *
 * @param ch 0:3 选择对应IO  br22
 *         |ch|tx|rx|
 *         |- |- |- |
 *         |0|PA3_TX|PA4_RX|
 *         |1|预留|预留|
 *         |2|预留|预留|
 *         |3|PA9_TX|PA10_RX|
 *         |-1|关闭对应的IO口串口功能|no|
 *
 * @return
 */
u32 gpio_set_uart2(u32 ch);

enum {
    IRFLT_LSB,
    IRFLT_RC,
    IRFLT_OSC,
    IRFLT_PLL48M,
};
enum {
    IRFLT_DIV1,
    IRFLT_DIV2,
    IRFLT_DIV4,
    IRFLT_DIV8,
    IRFLT_DIV16,
    IRFLT_DIV32,
    IRFLT_DIV64,
    IRFLT_DIV128,
    IRFLT_DIV256,
    IRFLT_DIV512,
    IRFLT_DIV1024,
    IRFLT_DIV2048,
    IRFLT_DIV4096,
    IRFLT_DIV8192,
    IRFLT_DIV16384,
    IRFLT_DIV32768,
};
/* u32 irflt_config(u32 osc, u32 div); */

/**
 * @brief gpio_irflt_to_timer
 *
 * @param t: [0-3]
 *
 * @return
 */
u32 gpio_irflt_to_timer(u32 t);


u32 get_gpio(const char *p);


#endif  /*GPIO_H*/
