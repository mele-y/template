#include "pool_2D.h"
int main(){
	hls::stream<S_TYPE> stream_in,stream_out;
	int height_in=20;
	int width_in=20;
	int	sx=2;
	int	sy=2;
	int	height_out=10;
	int width_out=10;
	for(int i=0;i<height_in;i++)
	{
		for(int j=0;j<width_in;j++)
		{
			S_TYPE valIn;
			valIn.data=i*height_in+j;
			valIn.keep=1;
			valIn.strb=1;
			valIn.user=1;
			valIn.dest=0;
			valIn.id=0;
			printf("inVal[%d][%d]=%d \n\r",i,j,(int)valIn.data);
			stream_in.write(valIn);
		}
	}
	pool_2D(stream_in, stream_out, height_in, width_in, height_out, width_out, sx, sy);
	for(int i=0;i<width_out*height_out;i++)
	{
		S_TYPE valOut=stream_out.read();
		printf("outVal[%d]=%d \n\r",i,(int)valOut.data);

	}
	return 0;
}
