#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "def.h"

int main(void)
{
	FILE *input1, *output, *input2;
	if((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	if((output = fopen("output.txt", "w")) == NULL)
	{
		return -1;
	}
	def(input1, output, "#define", "#undef");
	fclose(input1);
	fclose(output);
	return 0;
}
