#include<math.h>
#include"./red_bull.h"

static int pressedButton = -1;
static int pressedShift = 0;
static int last_mouse_x = 0;
static int last_mouse_y = 0;

void myMouse(int button, int state, int x, int y) {

  switch(state) {
  case GLUT_DOWN: 
    pressedButton = button;
    if(glutGetModifiers()&GLUT_ACTIVE_SHIFT)
      pressedShift = 1;
    break;
  case GLUT_UP: 
    pressedButton = -1;
    pressedShift = 0;
    break;
  default:
    break;
  }
  last_mouse_x = x;
  last_mouse_y = y;
}

void myMouseMotion(int x, int y) {
  GLdouble dummy[3], norm_x[3];
  double length;
  cameraInfo *__camera = getMyCamera();

  dummy[0] = __camera->Eye[0]-__camera->Centre[0];
  dummy[1] = __camera->Eye[1]-__camera->Centre[1];
  dummy[2] = __camera->Eye[2]-__camera->Centre[2];
  //カメラx方向単位行列
  norm_x[0] = __camera->Up[1]*dummy[2] - dummy[1]*__camera->Up[2];	
  norm_x[1] = __camera->Up[2]*dummy[0] - dummy[2]*__camera->Up[0];	
  norm_x[2] = __camera->Up[0]*dummy[1] - dummy[0]*__camera->Up[1];	 
  length = sqrt(norm_x[0]*norm_x[0]+norm_x[1]*norm_x[1]+norm_x[2]*norm_x[2]);

  switch(pressedButton) {
  case GLUT_LEFT_BUTTON:
    if(!pressedShift) {
      //回転
      myCameraRotateX((x - last_mouse_x)/length);
      myCameraRotateY((y - last_mouse_y)/length);
    } else {
      //移動
      myCameraTranslateZ((x - last_mouse_x)/length);
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    if(!pressedShift) {
      //平行移動
      myCameraTranslateX((x - last_mouse_x)/length);
      myCameraTranslateY((y - last_mouse_y)/length);
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if(pressedShift) {
      //z軸回転
      myCameraRotateZ((x-last_mouse_x)/length);
    break;
  case -1:
    break;
  default:
    break;
  }
  }
  last_mouse_x = x;
  last_mouse_y = y;
  glutPostRedisplay();
}

void myMousePassiveMotion(int x, int y) {
#ifdef PASSIVEMOTION_FUNCTION
#endif
  glutPostRedisplay();
}