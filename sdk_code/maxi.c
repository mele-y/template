/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xcore.h"
#include "xil_io.h"
XCore instance;
XCore_Config *cfgPtr;
#include "xil_cache.h"
int main()
{
    init_platform();
    //Xil_DCacheDisable();
    XCore_Initialize(&instance,XPAR_CORE_0_DEVICE_ID);
    print("Hello World\n\r");
    u32 feature_in_addr=0x00000000;
    u32 feature_out_addr=0x10000000;
    u32 *inPtr=(u32*)feature_in_addr;
    u32 *outPtr=(u32*)feature_out_addr;
    for(int i=0;i<15;i++)
    {
    	inPtr[i]=i+10;
    }
    XCore_Set_feature_in(&instance,feature_in_addr);
    XCore_Set_feature_out(&instance,feature_out_addr);
    XCore_Set_length_r(&instance,10);
    XCore_Start(&instance);
    while(!XCore_IsDone(&instance));
    printf("%x\n\r",XCore_Get_feature_out(&instance));
    for(int i=0;i<10;i++)
    {
    	printf("result is :%d\n\r",Xil_In32(outPtr+i));
    }
    //Xil_ICacheDisable();
    cleanup_platform();
    return 0;
}
