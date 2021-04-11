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


#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xexample.h" // Contains hls example (axilite) IP macros and functions


// Define global values for HLS example IP
XExample do_hls_example;
XExample_Config *do_hls_example_cfg;


// Initialize the HLS example IP
void init_HLS_example(){

		int status;
		// Create HLS example IP pointer
		do_hls_example_cfg = XExample_LookupConfig(
		XPAR_XEXAMPLE_0_DEVICE_ID);

		if (!do_hls_example_cfg) {
			xil_printf(
					"Error loading configuration for do_hls_example_cfg \n\r");
		}


		status = XExample_CfgInitialize(&do_hls_example,
				do_hls_example_cfg);
		if (status != XST_SUCCESS) {
			xil_printf("Error initializing for do_hls_example \n\r");
		}

		XExample_Initialize(&do_hls_example,
		XPAR_XEXAMPLE_0_DEVICE_ID);
}
// Function that adds using HLS example IP
// The functions used here are defined in xexample.h
void example_hls(int a, int b) {
	unsigned int c;
	c = 0; // result output from HLS IP

	// Write inputs
	XExample_Set_a(&do_hls_example, a);
	XExample_Set_b(&do_hls_example, b);
	xil_printf("Write a: %d \n\r", a);
	xil_printf("Write b: %d \n\r", b);

	// Start HLS IP
	XExample_Start(&do_hls_example);
	xil_printf("Started HLS Example IP \n\r");

	// Wait until it is finished
	while (!XExample_IsDone(&do_hls_example))
		;

	// Get hls_multiplier returned value
	c = XExample_Get_return(&do_hls_example);

	xil_printf("HLS IP Return Value: %d\n\r", c);
	xil_printf("End of test\n\n\r");
}

int main() {
	// setup
	init_platform();
	init_HLS_example();
	int a = 0;
	int b = 0;

	while (1) {
		// Enter the HLS IP inputs - a and b (Defined in Vitis HLS)
		xil_printf("Enter value for A: ");
		scanf("%d", &a);
		xil_printf("%d\n\r", a);
		xil_printf("Enter value for B: ");
		scanf("%d", &b);
		xil_printf("%d\n\r", b);

		xil_printf("Performing HLS Addition... \n\r");

		// perform addition in HLS IP
		example_hls(a, b);
	}

	cleanup_platform();
	return 0;
}
