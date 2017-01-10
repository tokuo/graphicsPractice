//
//  GLUTを使ったサンプルプログラム4
// 	Originated from Oshita
//	Modified by Tac
//


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// 自分たちが定義したOpenGLのための関数の呼び出し
#include "myGUI.h"

// 物体の回転のための変数
int     turn = 1;
float   theta = 0.0;

// カメラの回転のための変数
float   camera_yaw      = -45.0; // Ｙ軸を中心とする回転角度
float   camera_pitch    = -30.0; // Ｘ軸を中心とする回転角度
float   camera_roll     =   0.0; // Ｘ軸を中心とする回転角度
float   camera_distance =  15.0; // 中心からカメラの距離

// マウスのドラッグのための変数
int     drag_mouse_l = 0; // 左ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
int     drag_mouse_m = 0; // 中ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
int     drag_mouse_r = 0; // 右ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
int     last_mouse_x, last_mouse_y; // 最後に記録されたマウスカーソルの座標
int     beginx;

// rotation control(ex3)
int		movable = 1;
float	velocity = 1;
 

// ウィンドウのサイズ
int     win_width, win_height;

//
const int numCyl = 20; 
//
//  角すいの全頂点配列
//

const int  num_full_vertices = 18;

static float  pyramid_full_vertices[][ 3 ] = {
        { 0.0, 1.0, 0.0 }, {-1.0,-0.8, 1.0 }, { 1.0,-0.8, 1.0 },   // +Z方向の面
        { 0.0, 1.0, 0.0 }, { 1.0,-0.8,-1.0 }, {-1.0,-0.8,-1.0 },   // -Z方向の面
        { 0.0, 1.0, 0.0 }, { 1.0,-0.8, 1.0 }, { 1.0,-0.8,-1.0 },   // +X方向の面
        { 0.0, 1.0, 0.0 }, {-1.0,-0.8,-1.0 }, {-1.0,-0.8, 1.0 },   // -X方向の面
        { 1.0,-0.8, 1.0 }, {-1.0,-0.8, 1.0 }, { 1.0,-0.8,-1.0 },   // 底面1
        {-1.0,-0.8,-1.0 }, { 1.0,-0.8,-1.0 }, {-1.0,-0.8, 1.0 } }; // 底面1

static float  pyramid_full_normals[][ 3 ] = {
	{ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 },   // +Z方向の面
	{ 0.0, 0.0,-1.0 }, { 0.0, 0.0,-1.0 }, { 0.0, 0.0,-1.0 },   // -Z方向の面
	{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },   // +X方向の面
	{-1.0, 0.0, 0.0 }, {-1.0, 0.0, 0.0 }, {-1.0, 0.0, 0.0 },   // -X方向の面
	{ 0.0,-1.0, 0.0 }, { 0.0,-1.0, 0.0 }, { 0.0,-1.0, 0.0 },   // 底面1
	{ 0.0,-1.0, 0.0 }, { 0.0,-1.0, 0.0 }, { 0.0,-1.0, 0.0 } }; // 底面1


//
//  角すいの頂点配列＋三角面インデックス配列
//
const int  num_vertices = 5;
const int  num_triangles = 6;

//  角すいを描画5（頂点配列を使う方法）
//
void  renderPyramid5()
{
	glVertexPointer( 3, GL_FLOAT, 0, pyramid_full_vertices );
	glNormalPointer( GL_FLOAT, 0, pyramid_full_normals );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	glDrawArrays( GL_TRIANGLES, 0, num_full_vertices );
}


//
//  ウィンドウ再描画時に呼ばれるコールバック関数
//
void  display( void )
{
	// 画面をクリア（ピクセルデータとＺバッファの両方をクリア）
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// 変換行列を設定（モデル座標系→カメラ座標系）
	//（カメラが (0.0, 1.0, camera_distance) の位置にあるとする）
    glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( 0.0,  0.0, - camera_distance );
	glRotatef( - camera_roll,  0.0, 0.0, 1.0 );
	glRotatef( - camera_yaw,   0.0, 1.0, 0.0 );
	glRotatef( - camera_pitch, 1.0, 0.0, 0.0 );

	// 地面を描画
	glBegin( GL_POLYGON );
		glColor3f( 0.5, 0.8, 0.5 );
		glNormal3f( 0.0, 1.0, 0.0 );
		glVertex3f( 5.0, 0.0, 5.0 );
		glVertex3f( 5.0, 0.0,-5.0 );
		glVertex3f(-5.0, 0.0,-5.0 );
		glVertex3f(-5.0, 0.0, 5.0 );
	glEnd();
	glBegin( GL_POLYGON );
		glColor3f( 0.8, 0.5, 0.5 );
		glNormal3f( 0.0, -1.0, 0.0 );
		glVertex3f( 5.0, 0.0, 5.0 );
		glVertex3f(-5.0, 0.0, 5.0 );
		glVertex3f(-5.0, 0.0,-5.0 );
		glVertex3f( 5.0, 0.0,-5.0 );
	glEnd();

	// 中央の角すいを描画
	glPushMatrix();
		glTranslatef( 0.0, 0.0, 0.0 );
		glRotatef( theta, 0.0f, 1.0f, 0.0f );
		glColor3f( 1.0, 0.0, 0.0 );
		renderPyramid5();
	glPopMatrix();

	// 球 
	glPushMatrix();
		glTranslatef( 3.0, 0.0, 0.0 );
		glRotatef( theta, 1.0f, 0.0f, 0.0f );
		glColor3f( 0.0, 1.0, 0.0 );
		glutSolidSphere(1.0, 20, 20);
	glPopMatrix();

	// 棒 
	glPushMatrix();
	{ 
		int i;
   	  	double angle;		
	  	double dangle;

		dangle = 2.0*M_PI / numCyl;
		glTranslatef(-3.0, 0.0, 0.0 );
		glRotatef( theta, 0.0f, 0.0f, 1.0f );

		glColor3f( 0.0, 0.0, 1.0 );
		// 側面
		for(i=0; i<numCyl; i++) { 
			angle = i*dangle;  
			glBegin(GL_POLYGON);
				glNormal3f(cos(angle), sin(angle), 0);
				glVertex3f(cos(angle), sin(angle), -1);
				glNormal3f(cos(angle+dangle), sin(angle+dangle), 0);
				glVertex3f(cos(angle+dangle), sin(angle+dangle), -1);
				glNormal3f(cos(angle+dangle), sin(angle+dangle), 0);
				glVertex3f(cos(angle+dangle), sin(angle+dangle), 1);
				glNormal3f(cos(angle), sin(angle), 0);
				glVertex3f(cos(angle), sin(angle), 1);
			glEnd();
		}
		// 上面	
		glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);
			for(i=0; i<numCyl; i++) { 
				angle = i*dangle;  
				glVertex3f(cos(angle), sin(angle), 1);
			}
		glEnd();
		// 下面
		glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			for(i=0; i<numCyl; i++) { 
				angle = -i*dangle;  
				glVertex3f(cos(angle), sin(angle), -1);
			}
		glEnd();
	}
	glPopMatrix();

	// バックバッファに描画した画面をフロントバッファに表示
    glutSwapBuffers();
}


//
//  ウィンドウサイズ変更時に呼ばれるコールバック関数
//
void  reshape( int w, int h )
{
	// ウィンドウ内の描画を行う範囲を設定（ここではウィンドウ全体に描画）
    glViewport(0, 0, w, h);
	
	// カメラ座標系→スクリーン座標系への変換行列を設定
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, (double)w/h, 1, 500 );
    //glOrtho(-5*w/h, 5*w/h, -5, 5, 1, 500);	
    gluLookAt(0, 0, camera_distance, 0, 0, 0, 0, 1, 0); 	

    // ウィンドウのサイズを記録（テキスト描画処理のため）
	win_width = w;
	win_height = h;
}


//
//  アイドル時に呼ばれるコールバック関数
//
void  idle( void )
{
	// 物体を回転
	//theta += 0.3 * turn;
	theta += movable*turn*velocity;

	// 再描画の指示を出す（この後で再描画のコールバック関数が呼ばれる）
	glutPostRedisplay();
}

//
//  環境初期化関数
//
void  initEnvironment( void )
{
	// 光源を作成する
	float  light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
	float  light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float  light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float  light0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light0_diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light0_specular );
	glLightfv( GL_LIGHT0, GL_AMBIENT, light0_ambient );
	glEnable( GL_LIGHT0 );

	// 光源計算を有効にする
	glEnable( GL_LIGHTING );
	glShadeModel(GL_FLAT); // GL_SMOOTH or GL_FLAT
	// 物体の色情報を有効にする
	glEnable( GL_COLOR_MATERIAL );

	// Ｚテストを有効にする
	glEnable( GL_DEPTH_TEST );

	// 背面除去を有効にする
	glCullFace( GL_BACK );
	glEnable( GL_CULL_FACE );

	// 背景色を設定
	glClearColor( 0.5, 0.5, 0.8, 0.0 );

    	glOrtho(-5, 5, -5, 5, 1, 500);	
    	gluLookAt(0, 0, camera_distance, 0, 0, 0, 0, 1, 0); 	
}

//
//  メイン関数（プログラムはここから開始）
//
int  main( int argc, char ** argv )
{
	// GLUTの初期化
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( 320, 320 );
	glutInitWindowPosition( 0, 0 );
    glutCreateWindow("GLUT sample program");
	
	// コールバック関数の登録
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
	glutMouseFunc( mouse );
	glutMotionFunc( motion );
	glutKeyboardFunc( key );
	glutIdleFunc( idle );

	// 環境初期化
	initEnvironment();

	// GLUTのメインループに処理を移す
    glutMainLoop();
    return 0;
}
