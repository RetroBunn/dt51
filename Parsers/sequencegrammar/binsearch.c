#include <stdio.h>

int A[] = { 2,4, 7, 8, 9, 12, 16,  21, 80, 87, 99};
int num=11;


int binsearch(int Num, int n, int *A)
{
    int found;
    int hi,lo;
    int adr;

    hi = n-1;
    lo = 0;
    found = 0;

/* linear search for small array */
    if (n<8)
    {
	for (adr=0;adr<n;adr++)
	{
	    if (A[adr] == Num) return adr;
	}
	return (-1);
    }
    
/* otherwise binary search */

    while(found==0 && ( hi >= lo))
    {
	adr = (hi+lo)>>1;
	if (A[adr] == Num) 
	{
	    found = 1;
	    return adr;
	}
	if (Num > A[adr]) lo = adr+1;
	else hi = adr-1;
    }
    if (found) return adr;
    else return (-1);
}

	
main(int argc, char *argv[])
{
    printf("argv[1]=%s\n",argv[1]);
    printf("res = %d\n",binsearch(atoi(argv[1]),num,A));
}
