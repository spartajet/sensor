//
// Created by guoxi on 2019/11/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libserialport.h"
#include <windows.h>

const char *desired_port = "COM1";
struct sp_port *port;
enum sp_return;

void list_ports() {
    int i;
    struct sp_port **ports;

    enum sp_return error = sp_list_ports(&ports);
    if (error == SP_OK) {
        for (i = 0; ports[i]; i++) {
            printf("Found port: '%s'\n", sp_get_port_name(ports[i]));
        }
        sp_free_port_list(ports);
    } else {
        printf("No serial devices detected\n");
    }
    printf("\n");
}
/*
void parse_serial(char *byte_buff, int byte_num) {
    printf("%d", byte_num);
    for (int i = 0; i < byte_num; i++) {
        printf("%c", byte_buff[i]);

    }
    printf("\n");
}*/

void parse_serial(unsigned char* byte_buff,int byte_num)
{
    int i=0,k = 0;
    float SerialData[8];//时间 6通道数据 温度
    for(i=0;i<byte_num;i++)
    {
        if(byte_buff[i]==0xA5)
        {
            if((byte_num-i)<35) //小于一包数据不处理
            {
                return ;
            }

            if(byte_buff[i+35]!=0x0D) //包最后一字节不是0x0D
            {
                continue;
            }

            SerialData[0] = *(float* )&byte_buff[i+1];
            SerialData[1] = *(float* )&byte_buff[i+5];
            SerialData[2] = *(float* )&byte_buff[i+9];
            SerialData[3] = *(float* )&byte_buff[i+13];
            SerialData[4] = *(float* )&byte_buff[i+17];
            SerialData[5] = *(float* )&byte_buff[i+21];
            SerialData[6] = *(float* )&byte_buff[i+25];
            SerialData[7] = *(float* )&byte_buff[i+29];

            //memcpy(&SerialData[0],&byte_buff[i+1],32);
            /*
            for (k = 0; k < 8; k++) {
                SerialData[k] = *(float *)&byte_buff[i + 1];
                i += 4;
            }*/
            printf("时间:%f, 1数据：%f,2数据：%f,3数据：%f,4数据：%f,5数据：%f,6数据：%f,温度：%f\n",
                   SerialData[0],SerialData[1],SerialData[2],SerialData[3],SerialData[4],SerialData[5],
                   SerialData[6],SerialData[7]);


            i+=35;
        }
    }
}





int main(int argc, char *argv[]) {
    printf("start\n");

    list_ports();

    printf("Opening port '%s' \n", desired_port);
    enum sp_return error = sp_get_port_by_name(desired_port, &port);
    if (error == SP_OK) {
        error = sp_open(port, SP_MODE_READ_WRITE);
        printf("Port '%s' Opened\n", desired_port);
        if (error == SP_OK) {
            sp_set_baudrate(port, 921600);
            sp_set_parity(port,SP_PARITY_NONE);
            sp_set_bits(port,8);
            sp_set_stopbits(port,1);
            while (1) {
                Sleep(200); // can do something else in mean time
                int bytes_waiting = sp_input_waiting(port);//输入端口等待
                if (bytes_waiting > 0) {
                    printf("Bytes waiting %i\n", bytes_waiting);
                    char byte_buff[512];
                    int byte_num = 0;
                    byte_num = sp_nonblocking_read(port, byte_buff, 512);
                    parse_serial(byte_buff, byte_num);
                }
                fflush(stdout);
            }

            sp_close(port);
        } else {
            printf("Error opening serial device\n");
        }
    } else {
        printf("Error finding serial device\n");
    }
    return 0;
}