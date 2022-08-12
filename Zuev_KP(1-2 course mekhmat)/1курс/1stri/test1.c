#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "zamena.h"

int main(void)
{
	FILE *input1, *output;
	if((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	if((output = fopen("output.txt", "w")) == NULL)
	{
		return -1;
	}
	zamena(input1, output);
	fclose(input1);
	fclose(output);
	return 0;
}
