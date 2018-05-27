#ifndef BIT_PACKER
#define BIT_PACKER

/* this function will take a unsigned short and bitpack 
* and write it to the file
*/
void packbits_write(unsigned short curr, unsigned short *excess,
	unsigned short *rem, FILE* output , char N);

unsigned short math_pow(unsigned base, unsigned power);

void trailwrite(unsigned short *excess, unsigned short *rem, FILE* output,
	char N );
#endif