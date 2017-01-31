#include <math.h>
#include "./red_bull.h"

extern int s;
float i=0;
int o=0;
void

myIdle(void)
{
  if(s==1){
    if(o==0){
    myCameraRotateY(M_PI/500);//正方向に30度回転
    i=i+M_PI/500;
    if(i>=M_PI*2/12){
      o=1;
    }
    }
    if(o==1){
    myCameraRotateY(-1*M_PI/500);//負方向に30度回転
    i=i-M_PI/500;
    if(i<=-M_PI*2/12){
      o=0;
    }
    }
  }
  glutPostRedisplay();  
#ifdef IDLE_FUNCTION
#endif
}
