#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define D 256 /* total charachter number as ASCII */

char to_upper (char c) {return 'a' <= c && c <= 'z' ? c - 'a' + 'A' : c;}

void search (char * t, char * p, int q)	/* select q as prime to better distribution */
{
	int i, j, k = 1, n, h_t, h_p,
		len_t = strlen(t), len_p = strlen(p);

	for (i = 0; i < len_p - 1; ++i)	/* k is the digit value of most significant digit for exp: 234 k = 200 in 10 based */
		k = (k * D) % q;

	/* calculate the hash codes */
	for (i = h_t = h_p = 0; i < len_p; ++i) 
	{
		/* multiply the previos value by D and add the new charachter, to do not exceed int limit apply modulus op */
		h_p = ((h_p * D) + p[i]) % q; 
		h_t = ((h_t * D) + t[i]) % q; 
	}

	for (i = 0, n = len_t - len_p + 1; i < n; ++i)
	{
		/* same hashCodes but we also check if they are really same or just a collision */
		if (h_t == h_p)
		{
			for (j = 0; j < len_p; ++j)
				if (to_upper(t[i + j]) != to_upper(p[j]))
					break;

			if (j == len_p)
				printf("Found at index %d\n", i);
		}

		if (i < n)
		{
			h_t = ((h_t - k * t[i]) * D + t[i + len_p]) % q;

			if (h_t < 0) /* sometimes hash value can be resulted negaive !! */
				h_t += q;
		}
	}
}

int main (void) 
{
	char * text = "asbasbas";
	char * pattern = "as";

	search(text, pattern, 17);
}