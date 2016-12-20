//
//  GLUTを使ったサンプルプログラム
// 	Originated from Oshita
//	Modified by Tac 
//

// GLUTヘッダファイルのインクルード
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// グローバル変数
static int	 turn = 1;
static float   theta = 0.0;

//
//  角すいを描画ためのルーチン
//  　三角形を組み合わせることで角錐を表現する
//
void  renderPyramid1()
{
	glBegin( GL_TRIANGLES );
		// +Z方向の面
		glNormal3f( 0.0, 0.0, 1.0 );
		glVertex3f( 0.0, 1.0, 0.0 );
		glVertex3f(-1.0,-0.8, 1.0 );
		glVertex3f( 1.0,-0.8, 1.0 );

		// -Z方向の面
		glNormal3f( 0.0, 0.0,-1.0 );
		glVertex3f( 0.0, 1.0, 0.0 );
		glVertex3f( 1.0,-0.8,-1.0 );
		glVertex3f(-1.0,-0.8,-1.0 );

		// +X方向の面
		glNormal3f( 1.0, 0.0, 0.0 );
		glVertex3f( 0.0, 1.0, 0.0 );
		glVertex3f( 1.0,-0.8, 1.0 );
		glVertex3f( 1.0,-0.8,-1.0 );

		// -X方向の面
		glNormal3f(-1.0, 0.0, 0.0 );
		glVertex3f( 0.0, 1.0, 0.0 );
		glVertex3f(-1.0,-0.8,-1.0 );
		glVertex3f(-1.0,-0.8, 1.0 );

		// 底面1
		glNormal3f( 0.0,-1.0, 0.0 );
		glVertex3f( 1.0,-0.8, 1.0 );
		glVertex3f(-1.0,-0.8, 1.0 );
		glVertex3f( 1.0,-0.8,-1.0 );

		// 底面1
		glNormal3f( 0.0,-1.0, 0.0 );
		glVertex3f(-1.0,-0.8,-1.0 );
		glVertex3f( 1.0,-0.8,-1.0 );
		glVertex3f(-1.0,-0.8, 1.0 );
	glEnd();
}


//
//  ウィンドウ再描画時に呼ばれるコールバック関数
//
void  display( void )
{
	// 画面をクリア（ピクセルデータとＺバッファの両方をクリア）
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// 変換行列を設定（モデル座標系→カメラ座標系）
	//（カメラが (0.0, -2.0, -12.0) の位置にあるとする）
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( 0.0, -2.0, -12.0 );

	// 地面を描画
	glBegin( GL_POLYGON );
		glColor3f( 0.5, 0.8, 0.5 );
		glNormal3f( 0.0, 1.0, 0.0 );
		glVertex3f( 5.0, 0.0, 5.0 );
		glVertex3f( 5.0, 0.0,-5.0 );
		glVertex3f(-5.0, 0.0,-5.0 );
		glVertex3f(-5.0, 0.0, 5.0 );
	glEnd();

	//
	// glPushMatrix/glPopMatrix 
	// 　Push:ポリゴンを描きだす座標変換行列をスタックにプッシュする
	//   Pop: スタックから取り出す 
	// 中央の角すいを描画
	glPushMatrix();
		glTranslatef( 0.0, 1.0, 0.0 );
		glRotatef( theta, 0.0f, 1.0f, 0.0f );
		glColor3f( 1.0, 0.0, 0.0 );
		renderPyramid1();
	glPopMatrix(); // glTranslate/glRotateを実施しなかった状態に戻す

	// 右の角すいを描画
	glPushMatrix();
		glTranslatef( 3.0, 1.0, 0.0 );
		glRotatef( theta, 1.0f, 0.0f, 0.0f );
		glColor3f( 0.0, 1.0, 0.0 );
		renderPyramid1();
	glPopMatrix();

	// 左の角すいを描画
	glPushMatrix();
		glTranslatef(-3.0, 1.0, 0.0 );
		glRotatef( theta, 0.0f, 0.0f, 1.0f );
		glColor3f( 0.0, 0.0, 1.0 );
		renderPyramid1();
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
}


//
// マウスクリック時に呼ばれるコールバック関数
//
void  mouse( int button, int state, int mx, int my )
{
	// 右ボタンがクリックされたら回転方向を正にする
	if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) ) {
		turn = 1.0;
	// 左ボタンがクリックされたら回転方向を負にする
	} else if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_DOWN ) ) {
		turn = -1.0;
	}
}


//
//  アイドル時に呼ばれるコールバック関数
//     アイドル時とは、何のイベントもないとき。
void  idle( void )
{
	// 物体を回転
	theta += 0.3 * turn;

	// 再描画の指示を出す（この後で再描画のコールバック関数が呼ばれる）
	glutPostRedisplay();
}


//
//  環境初期化関数
//
void  initEnvironment( void )
{
	// 光源を作成する
	float  light0_position[] = { 1.0, 1.0, 1.0, 1.0 };
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

	// 物体の色情報を有効にする
	glEnable( GL_COLOR_MATERIAL );

	// Ｚテストを有効にする
	glEnable( GL_DEPTH_TEST );

	// 背面除去を有効にする
	glCullFace( GL_BACK );
	glEnable( GL_CULL_FACE );

	// 背景色を設定
	glClearColor( 0.5, 0.5, 0.8, 0.0 );
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
	glutIdleFunc( idle );

	// 環境初期化
	initEnvironment();

	// GLUTのメインループに処理を移す
	glutMainLoop();
	return 0;
}
