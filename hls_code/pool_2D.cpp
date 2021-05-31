#include "pool_2D.h"
void pool_2D(hls::stream<S_TYPE> &stream_in,hls::stream<S_TYPE> &stream_out,
	int height_in,int width_in,int height_out,int width_out,int sx,int sy)
{
#pragma HLS INTERFACE axis  port=stream_out
#pragma HLS INTERFACE axis  port=stream_in
#pragma HLS INTERFACE s_axilite port=height_out
#pragma HLS INTERFACE s_axilite port=width_in
#pragma HLS INTERFACE s_axilite port=sy
#pragma HLS INTERFACE s_axilite port=sx
#pragma HLS INTERFACE s_axilite port=height_in
#pragma HLS INTERFACE s_axilite port=width_out
#pragma HLS INTERFACE s_axilite port=return
	#pragma HLS DATAFLOW
	static hls::stream<S_TYPE> stream_temp;
	pool_s1(stream_in,stream_temp,height_in,width_in,sx);
	pool_s2(stream_temp,stream_out,height_in,width_out,sy);

}
void pool_s1(hls::stream<S_TYPE> &stream_in,hls::stream<S_TYPE> &stream_temp,int height_in,int width_in,int sx)
{
	for(int i=0;i<height_in;i++)
	{
#pragma HLS LOOP_TRIPCOUNT min=20 max=20 avg=20
		for(int j=0;j<width_in;j++)
{
#pragma HLS LOOP_TRIPCOUNT min=20 max=20 avg=20

			#pragma HLS PIPELINE
			S_TYPE data_in;
			S_TYPE data_out;
			S_TYPE data_temp;
			data_in=stream_in.read();
			if(j%sx==0)
				data_out=data_in;
			else
			{
				if(data_in.data>data_out.data)
					data_out=data_in;
			}
			if((j+1)%sx==0)
			{
				stream_temp.write(data_out);
			}
		}
	}
}
void pool_s2(hls::stream<S_TYPE> &stream_temp,hls::stream<S_TYPE> &stream_out,int height_in,int width_out,int sy)
{
	static S_TYPE buf[BUF_DEPTH];
	for(int i=0;i<height_in;i++)
	{
#pragma HLS LOOP_TRIPCOUNT min=20 max=20 avg=20
	for(int j=0;j<width_out;j++)
	{

#pragma HLS LOOP_TRIPCOUNT min=10 max=10 avg=10
	#pragma HLS PIPELINE
			S_TYPE data_in;
			data_in=stream_temp.read();
			if(i%sy==0)
				//data_in=stream_temp.read();
			{
			//	data_temp=data_in;
				buf[j]=data_in;
			}
			else
			{
				if(data_in.data>buf[j].data)
					buf[j]=data_in;
				else
					data_in=buf[j];
			}
			if((i+1)%sy==0)
				stream_out.write(data_in);

		}
	}
}
