#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int i;
	int j;
	int count=0;
	FILE *infile,*outfile;

	infile=fopen(argv[1],"rb");

	outfile=fopen(argv[2],"w");

	fprintf(outfile,"const unsigned char main_dict[]={\n");

	i=fgetc(infile);
	j=i;
	while ((i=fgetc(infile))!=EOF)
	{
		if (count%8==0 && count !=0)
			fprintf(outfile,"\t\n");
		count++;
		fprintf(outfile,"0x%02X, ",j);
		j=i;
	}
	fprintf(outfile,"0x%02X",j);
	fprintf(outfile,"\n};\n\n");

	fclose(infile);
	fclose(outfile);

}


