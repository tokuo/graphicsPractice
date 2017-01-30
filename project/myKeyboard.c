#include "./red_bull.h"
#include <math.h>

//
// Keyboard
//
static int keyx = 0;
static int keyy = 0;

int s=0;//アニメーションを制御する変数
int f=0;//表示方法切り替えを制御する変数

void
myKeyboard(unsigned char key,  /* キーボードから打ち込まれた文字 */
		int x,         /* キーボードが打ち込まれたときのマウスの位置 */ 
	        int y)
	
{
#ifdef KEYBOARD_FUNCTION 
	keyx = x;
	keyy = y;
	myKeyboard0(key, x, y);
#endif	
	/*
	 再描画イベントを起こすための関数
		glutDisplayFuncで登録された関数がコールバックされる
	*/
	glutPostRedisplay();	
}


void
myKeyboard0(unsigned char key,  /* キーボードから打ち込まれた文字 */
		int x,          /* キーボードが打ち込まれたときのマウスの位置 */ 
	        int y)
	
{
	switch(key) {
		case 'q': {
			exit(EXIT_FAILURE);
			break;
		}
		  //キーボード機能の追加
	        case 'Q': {
			exit(EXIT_FAILURE);
			break;
		}	
	  
		case 's': {
		  if(s==0){
		    s=1;//アニメーション起動
		  }else if(s==1){
		    s=0;//アニメーション停止
		  }break;
		}
		case '1': {
		    f=0;//表示方法1
		    break;
		}
	        case '2': {
		    f=1;//表示方法2
		    break;
		}
		  //キーボード機能の追加ここまで
		case 'x': {
			myCameraRotateX(1.0/M_PI);
			//operationModeSet(xrotation);
			//myOperation.c はいらないから上記一文もいらない
			break;
		}
		case 'y': {
			myCameraRotateY(1.0/M_PI);
			//operationModeSet(yrotation);
			//myOperation.c はいらないから上記一文もいらない
			break;
		}
		case 'z': {
			myCameraRotateZ(1.0/M_PI);
			//operationModeSet(zrotation);
			//myOperation.c はいらないから上記一文もいらない
			break;
		}
		default: { /* 定義されていないキーが入力された時には、何もしない。 */
			break;
		}
	}	

}
