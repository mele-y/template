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
#include "xbram_vector_plus.h"
#include "xparameters.h"
#include "xbram.h"
XBram_vector_plus_Config *cfgPtr;
XBram_vector_plus instance;
int * aVec = (int *)XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR;
int * cVec = (int *)XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR;
int init_ip();
int main()
{
    init_platform();
    init_ip();
    //int aVec[8];
    XBram_vector_plus_Set_b(&instance,1);
    int b=XBram_vector_plus_Get_b(&instance);
    xil_printf("b is:%d\n",b);
    for(int index=0;index<8;index++)
    {
    	aVec[index]=index+1;
    }
   // XBram_WriteReg(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR,0x00,5);
   // XBram_WriteReg(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR,0x04,6);
   // XBram_vector_plus_Start(&instance);
   // while(!XBram_vector_plus_IsDone(&instance))
    //print("calculation is done");
    int temp;
    u8 address=0x00;
    for(int i=0;i<8;i++)
    {
     temp=XBram_ReadReg(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR,address);
    printf("%x:%d\n",address,temp);
    address=address+0x04;
    }
    XBram_vector_plus_Start(&instance);
    while(!XBram_vector_plus_IsDone(&instance));
    for(int i=0;i<8;i++)
    {
    	xil_printf("c at %x is %d\n\r",cVec+i,cVec[i]);
    }
    cleanup_platform();
    return 0;
}
int init_ip(){
	int status;
	cfgPtr=XBram_vector_plus_LookupConfig(XPAR_BRAM_VECTOR_PLUS_0_DEVICE_ID);
	if(!cfgPtr){
		print("ERROR: Lookup of acclerator configuration failed\n\r");
		return XST_FAILURE;
	}
	status = XBram_vector_plus_CfgInitialize(&instance,cfgPtr);
	if(status!=XST_SUCCESS)
	{
		print("ERROR:Could not initialize accelerator.\n\r");
		return XST_FAILURE;
	}
	return status;
}
