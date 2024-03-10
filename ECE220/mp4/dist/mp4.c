#include <stdint.h>
#include <stdio.h>

#include "mp4.h"

void plan_swim_meet (int32_t pref_A, int32_t pref_B, int32_t pref_C, int32_t pref_D)
{
	// your code goes here
	//order 00 01 10 11
	//line  01 01 01 00
	int order = 27, line = 84;
	if ((pref_A | pref_B) == 3 && (pref_C | pref_D) == 3)
		//order 00 01 10 11
		//line  00 01 00 00
		order = 27, line = 16;
	else if ((pref_A | pref_C) == 3 && (pref_B | pref_D) == 3)
		//orfer 00 10 01 11
		//line  00 01 00 00
		order = 39, line = 16;
	else if ((pref_A | pref_B) == 3)
		//order 00 01 10 11
		//line  00 01 01 00
		order = 27, line = 20;
	else if ((pref_A | pref_C) == 3)
		//order 00 10 01 11
		//line  00 01 01 00
		order = 39, line = 20;
	else if ((pref_A | pref_D) == 3)
		//order 00 11 01 10
		//line  00 01 01 00
		order = 54, line = 20;
	for (int i = 3; i >= 0; --i)
	{
		printf("%c", 'A' + ((order & (3 << (i * 2))) >> (i * 2)));
		((line & (3 << (i * 2))) >> (i * 2)) * 47 == 0 ? line = line: printf("/");
	}
	printf("\n");
}
