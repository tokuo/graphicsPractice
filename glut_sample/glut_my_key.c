#include "myGUI.h"

void key(unsigned char c, int x, int y)
{
	switch(c) {
		case 'q': {
			fprintf(stdout,"key:%c mouse_x:%d mouse_%d\n",c,x,y);
			exit(EXIT_FAILURE);
			break;
		}
		case 'Q': {
			fprintf(stdout,"key:%c mouse_x:%d mouse_%d\n",c,x,y);
			exit(EXIT_FAILURE);
			break;
		}
		case 's': {
			fprintf(stdout,"key:%c mouse_x:%d mouse_%d\n",c,x,y);
			movable = 1-movable;
			break;
		}
		case 'r': {
			fprintf(stdout,"key:%c mouse_x:%d mouse_%d\n",c,x,y);
			turn *= -1;
			break;
		}
	}
}
