#include <stdio.h>
#include <iconv.h>
#include <stdlib.h>
#include <string.h>

int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
		memset(outbuf,0,outlen);
	if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
		iconv_close(cd);
	return 0;
}

int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gbk",inbuf,inlen,outbuf,outlen);
}

int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}

int main(int argc, char *argv[])
{
	FILE *fpin, *fpout, *fphzk;
	unsigned char *listbufferu, *listbufferg;
	int listlength;
	int i;
	int verbose = 1;
	
	if(argc < 3)
	{
		fprintf(stderr, "Usage: %s <input_file> <output_file> [-v] [dot type]\n", argv[0]);
		fprintf(stderr, "	Input file must be UTF8 text file, any single byte character is ignored\n");
		fprintf(stderr, "	Output file is in C header format\n");
		fprintf(stderr, "	If you specify -v, this program will be verbose mode\n");
		fprintf(stderr, "	[dot type] can be 12/16/24/32/48, default is 16\n");
		fprintf(stderr, "Copyright 2018 Zhiyuan Wan\n");
		return -1;
	}
	fpin = fopen(argv[1], "r");
	fseek(fpin, 0, SEEK_END);
	listlength = ftell(fpin);
	printf("List length is %d bytes\n", listlength);
	fseek(fpin, 0, SEEK_SET);
	
	listbufferu = malloc(listlength);
	listbufferg = malloc(listlength); // because GBK is always shorter than UTF8
	
	fread(listbufferu, 1, listlength, fpin);
	fclose(fpin);
	
	u2g(listbufferu, listlength, listbufferg, listlength);

	fphzk = fopen("HZK16F", "rb");
	fpout = fopen(argv[2], "w+");
	
	int qu, wei, offset;
	int j = 0;
	unsigned char fontdata[32]; //FIXME: 16x16
	unsigned char fontdata_inversed[32];
		
	
	
	fprintf(fpout, "/* This header file is generated by HZK generator */\n");
	//fwrite(listbufferg, 1, strlen(listbufferg), fpout);
	fprintf(fpout, "/* Zhiyuan Wan <h@iloli.bid> 2018 */\n\n");
	fprintf(fpout, "const char font_cn[][32] = {\n"); //FIXME: 16x16
	
	int crlength = 0;
	memset(listbufferu, 0x00, listlength);
	printf("GB2312 character: %d\n", strlen(listbufferg));
#if 1	
	for(i = 0; i < strlen(listbufferg) - 2; i++)
	{
		if(!(listbufferg[i] & 0x80))
		{
			//printf("Nn = %02x\n", listbufferg[i]);
			if(listbufferg[i] == '\n')
			{
				
				listbufferu[j] = 0x01;
			}
			continue;
		}
		qu = listbufferg[i] - 0xa0;
		wei = listbufferg[i + 1] - 0xa0;
		i ++;
		offset = (94 * (qu - 1) + wei - 1) * 32; // FIXME: 16x16
		fseek(fphzk, offset, SEEK_SET);
		j ++;
		fread(fontdata, 1, 32, fphzk);
		int x, y;
		//printf("Offset = 0x%04x, Qu = 0x%02x, Wei = 0x%02x, ch = 0x%02x%02x, index = %d\n", offset, qu, wei, 
		//			(unsigned char) listbufferg[i-1],  (unsigned char) listbufferg[i], i);
		
		memset(fontdata_inversed, 0x00, sizeof(fontdata_inversed));
		for(y = 0; y < 16; y++) // FIXME: again
		{
			for(x = 0; x < 16; x++)
			{
				if(fontdata[y * 2 + x / 8] & (0x80 >> (x % 8)))
				{
					if(y < 8)
						fontdata_inversed[x] |= (0x01 << y);
					else
						fontdata_inversed[x + 16] |= (0x01 << (y - 8));
				}
			}
		}
		fprintf(fpout, "\t{");
		for(x = 0; x < 32; x++)
		{
			fprintf(fpout, "0x%02x", fontdata_inversed[x]);
			if(x != 31)
				fprintf(fpout, ", ");
			if((x + 1) % 8 == 0)
				fprintf(fpout, "\n\t");
		}
		fprintf(fpout, "}%s// Code = 0x%02x%02x\n", (i < strlen(listbufferg) - 3) ? ",": "", (unsigned char) listbufferg[i - 1], (unsigned char) listbufferg[i]);
		
		
		/*
		Output format:
		Upper 1-16
		Lower 1-16
		*/
		
	}
	fprintf(fpout, "};\n");
	fprintf(fpout, "\nconst char cr_table[] = {\n\t");
	for(i = 0; i < j; i++)
	{
		fprintf(fpout, "0x%02x", listbufferu[i]);
		if(i != (j - 1))
			fprintf(fpout, ", ");
		if((i + 1) % 8 == 0)
			fprintf(fpout, "\n\t");		
	}
	fprintf(fpout, "};\n");
	printf("'%s' file generated successfully, contains %d characters\n", argv[2], j);
	fclose(fphzk);
	fclose(fpout);
#endif
	return 0;
	
}
