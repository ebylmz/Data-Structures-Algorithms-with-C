#include <stdio.h>
#include <stdlib.h>

/* 	this is not efficient way, because copy pasting is expensive process 	*/

/* 	scans as many number as user enter, every iteration function copy whole 
	previous entires to new allocated array after copying free the previos 
	allocated memory,and continue till user enter nonpositive number 		*/
int * get_many_numbers() 
{
	int 	i,
			n,
			count = 0,
			val;

	int 	* curp, 
			* prep;

	do {
		scanf("%d", &val);	
		++count;

		/* allocate enough memory for new sized array */
		curp = (int *)calloc(count, sizeof(int));

		if (curp != NULL)
		{
			/* copy pre values to new array, first time there is no element to copy therefore count - 1 */
			for (i = 0, n = count - 1; i < n; ++i)
				curp[i] = prep[i];

			/* add the new value scanned from user */
			curp[count - 1] = val;

			/* after copy, we wont use any time previos allocated array so */
			free(prep);

			/* to copy values next iteration, keep the new allocated addres */
			prep = curp;
		}
		else
		{
			printf("There is no enough memory\n");
			break;
		}
	} while (val > 0);

	printf("Scanned values: ");

	for (i = 0; i < count; ++i)
		printf("%d  ", curp[i]);
	printf("\n");

	/* do not forget to free when your process done */
	return curp;
}

int main(void)
{
	int * arr;
	printf("Enter your numbers\n");
	printf(">> ");
	arr = get_many_numbers();

	free(arr);
}