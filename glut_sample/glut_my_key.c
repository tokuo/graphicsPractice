#include <stdio.h>
#include <stdlib.h>
#include "myGUI.h"


//
// Keyboard
//
void key(unsigned char c, int x, int y)
{
	switch(c) {
		case 'q': {
			exit(EXIT_FAILURE);
			break;
		}
	}
}