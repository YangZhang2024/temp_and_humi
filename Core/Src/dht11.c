#include "dht11.h"
#include "stdio.h"

unsigned char read_byte() {
    unsigned char i, dat = 0, counter = 0;
    for (i = 0; i < 8; i++) {
        while (!ONE_WIRE_DQ_IN && counter < 5){
            delay_us(10);
        };
        if (counter >= 5) {
            return 0;
        }
        delay_us(30);
        dat = (dat << 1) | ONE_WIRE_DQ_IN;
        while (ONE_WIRE_DQ_IN);
    }
    return dat;
}


uint8_t get_humidity(double *temp, double *humidity) {
    ONE_WIRE_DQ_OUT(1);
    ONE_WIRE_DQ_OUT(0);
    delay_ms(20);
    ONE_WIRE_DQ_OUT(1);

    delay_us(13);

    uint8_t count = 0;
    while (!ONE_WIRE_DQ_IN && count < 10) { // 等低响应结束
        delay_us(10);
        count++;
    }
    if (count >= 10) {
        return 0;
    }

    count = 0;
    while (ONE_WIRE_DQ_IN && count < 10) {
        delay_us(10);
        count++;
    };  // 等高响应结束
    if (count >= 10) {
        return 0;
    }


    uint8_t RH, RL, TH, TL, revise;
    RH = read_byte();    //接收湿度高八位
    RL = read_byte();    //接收湿度低八位
    TH = read_byte();    //接收温度高八位
    TL = read_byte();    //接收温度低八位
    revise = read_byte(); //接收校正位

    if ((RH + RL + TH + TL) == revise)      //校正
    {
        uint8_t is_negative = 0x80 & TL;

        if (TL >= 10) {
            *temp = (TH + TL * 0.01);
        } else {
            *temp = (TH + TL * 0.1);
        }

        if (is_negative) {
            *temp = -(*temp);
        }

        is_negative = 0x80 & RL;
        if (RH >= 10) {
            *humidity = (RH + RL * 0.01);
        } else {
            *humidity = (RH + RL * 0.1);
        }
        if (is_negative) {
            *humidity = -(*humidity);
        }
        return 1;
    } else {
        return 0;
    }

}