#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 20

typedef struct {
	char 	name[STRLEN];
	int 	year;
	float 	volume;
	enum {v4 = 4, v5 = 5, v6 = 6, v8 = 8} cylinders;
} engine_t;

/* allocates enough spaceses at heap and returns that address by filling the inf at txt file */
engine_t * read_engine_dynamic (char fname[])
{
	engine_t * 	e;
	FILE 	 *  infid;

	if (infid = fopen(fname, "r"))
	{
		if (e = (engine_t *)malloc(sizeof(engine_t)))
		{
			fgets(e->name, STRLEN, infid);	
			e->name[strlen(e->name) - 2] = '\0';
			
			fscanf(infid, "%d", &e->year);		
			fscanf(infid, "%f", &e->volume);
			fscanf(infid, "%u", &e->cylinders);
		
		}
	}

	return e;
}

/* to prevent useless copy-paste process, takes the address of the variable */
int read_engine (engine_t * e, char fname[])
{
	int 	err;
	FILE * 	infid;	/* input file identify */


	if (infid = fopen(fname, "r"))
	{
		/* scan the engine name, use fgets in case of name consist of multiple words */
		fgets(e->name, STRLEN, infid);
		e->name[strlen(e->name) - 2] = '\0';

		fscanf(infid, "%d", &e->year);		
		fscanf(infid, "%f", &e->volume);
		fscanf(infid, "%u", &e->cylinders);
	
		
		err = 0;
	} 
	else
		err = 1;

	return err;
}

void print_engine (const engine_t * e)
{
	char cy[3];

	switch (e->cylinders)
	{
		case 4:
			strcpy(cy, "v4");
			break;
		case 5:
			strcpy(cy, "v5");
			break;
		case 6:
			strcpy(cy, "v6");
			break;
		case 8:
			strcpy(cy, "v8");
			break;
	}

	printf("%-20s %d %-3.1f %s\n", e->name, e->year, e->volume, cy);
}	

void test ()
{
	char 	f1name[] = "engine1.txt",
			f2name[] = "engine2.txt";
	
	engine_t e1, e2;

	read_engine(&e1, f1name);
	e2 = *read_engine_dynamic(f2name);
	print_engine(&e1);
	print_engine(&e2);
}

int main(void)
{
	test();
}