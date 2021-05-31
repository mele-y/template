#ifndef _POOL_2D_H_
#define _POOL_2D_H_
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <stdio.h>
#define  BUF_DEPTH 100
typedef ap_axis<32,2,5,6> S_TYPE;
void pool_2D(hls::stream<S_TYPE> &stream_in,hls::stream<S_TYPE> &stream_out,int height_in,int width_in,int height_out,int width_out,int sx,int sy);
void pool_s1(hls::stream<S_TYPE> &stream_in,hls::stream<S_TYPE> &stream_temp,int height_in,int width_in,int sx);
void pool_s2(hls::stream<S_TYPE> &stream_temp,hls::stream<S_TYPE> &stream_out,int height_in,int width_out,int sy);
#endif
