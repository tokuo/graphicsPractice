//
//  GLUTを使ったサンプルプログラム３
// 	Originated from Oshita
//	Modified by Tac
//


// GLUTヘッダファイルのインクルード
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

// 物体の回転のための変数
static int     turn = 1;
static float   theta = 0.0;

// カメラの回転のための変数
// Yaw/Pitch/Distance
static float   camera_yaw      = -30.0; // Ｙ軸を中心とする回転角度
static float   camera_pitch    = -45.0; // Ｘ軸を中心とする回転角度
static float   camera_roll     = 0.0;   // Ｚ軸を中心とする回転角度
static float   camera_distance = 15.0; // 中心からカメラの距離

// マウスのドラッグのための変数
static int     drag_mouse_l = 0; // 左ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
static int     drag_mouse_r = 0; // 右ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
static int     drag_mouse_m = 0; // 中ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
static int     last_mouse_x, last_mouse_y; // 最後に記録されたマウスカーソルの座標

// ウィンドウのサイズ
static int     win_width, win_height;


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

// 角すいの頂点座標の配列
static float  pyramid_vertices[][ 3 ] = {
	{ 0.0, 1.0, 0.0 }, 
	{ 1.0,-0.8, 1.0 }, 
	{ 1.0,-0.8,-1.0 }, 
	{-1.0,-0.8, 1.0 }, 
	{-1.0,-0.8,-1.0 } };

// 三角面インデックス（各三角面を構成する頂点の頂点番号）の配列
static int  pyramid_tri_index[][ 3 ] = {
	{ 0,3,1 }, { 0,2,4 }, { 0,1,2 }, { 0,4,3 }, { 1,3,2 }, { 4,2,3 } };

// 三角面の法線ベクトルの配列
static float  pyramid_tri_normals[][ 3 ] = {
	{ 0.0, 0.0, 1.0 }, // +Z方向の面
	{ 0.0, 0.0,-1.0 }, // -Z方向の面
	{ 1.0, 0.0, 0.0 }, // +X方向の面
	{-1.0, 0.0, 0.0 }, // -X方向の面
	{ 0.0,-1.0, 0.0 }, // 底面1
	{ 0.0,-1.0, 0.0 }}; // 底面1

// 頂点の法線ベクトルの配列（面ごとではなく頂点ごとに法線を持たせる場合に使用）
static float  pyramid_normals[][ 3 ] = {
	{ 0.0, 1.0, 0.0 }, 
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 0.0,-1.0 },
	{-1.0, 0.0, 1.0 },
	{-1.0, 0.0,-1.0 } };


//
//  角すいを描画１（頂点データを関数内に直接記述）
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
//  角すいを描画２（頂点データを配列で用意しておく方法）
//
void  renderPyramid2()
{
	int  i;

	glBegin( GL_TRIANGLES );
	for ( i=0; i<num_full_vertices; i++ )
	{
		glNormal3f( pyramid_full_normals[i][0], pyramid_full_normals[i][1], pyramid_full_normals[i][2] );
		glVertex3f( pyramid_full_vertices[i][0], pyramid_full_vertices[i][1], pyramid_full_vertices[i][2] );
	}
	glEnd();
}


//
//  角すいを描画３（頂点配列を使う方法）
//
void  renderPyramid3()
{
	glVertexPointer( 3, GL_FLOAT, 0, pyramid_full_vertices );
	glNormalPointer( GL_FLOAT, 0, pyramid_full_normals );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	glDrawArrays( GL_TRIANGLES, 0, num_full_vertices );
}


//
//  角すいを描画４（頂点の座標・法線データ＋三角面インデックスを配列で用意しておく方法）
//
void  renderPyramid4()
{
	int  i, j, v_no;

	glBegin( GL_TRIANGLES );
	for ( i=0; i<num_triangles; i++ )
	{
		for ( j=0; j<3; j++ )
		{
			v_no = pyramid_tri_index[ i ][ j ];
			glNormal3f( pyramid_normals[ v_no ][0], pyramid_normals[ v_no ][1], pyramid_normals[ v_no ][2] );
			glVertex3f( pyramid_vertices[ v_no ][0], pyramid_vertices[ v_no ][1], pyramid_vertices[ v_no ][2] );
		}
	}
	glEnd();
}


//
//  角すいを描画５（頂点配列＋三角面インデックスを使う方法）
//
void  renderPyramid5()
{
	glVertexPointer( 3, GL_FLOAT, 0, pyramid_vertices );
	glNormalPointer( GL_FLOAT, 0, pyramid_normals );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	glDrawElements( GL_TRIANGLES, num_triangles * 3, GL_UNSIGNED_INT, pyramid_tri_index );
}


//
//  角すいを描画６（頂点の座標データ＋三角面インデックス＋三角面の法線データを配列で用意しておく方法）
//
void  renderPyramid6()
{
	int  i, j;
	int  v_no;

	glBegin( GL_TRIANGLES );
	for ( i=0; i<num_triangles; i++ )
	{
		glNormal3f( pyramid_tri_normals[i][0], pyramid_tri_normals[i][1], pyramid_tri_normals[i][2] );
		for ( j=0; j<3; j++ )
		{
			v_no = pyramid_tri_index[ i ][ j ];
			glVertex3f( pyramid_vertices[ v_no ][0], pyramid_vertices[ v_no ][1], pyramid_vertices[ v_no ][2] );
		}
	}
	glEnd();
}


//
//  テキストを描画
//
int
drawMessage()
{
	// 表示するメッセージ
	static char  message[] = "Hello, World!!";
	int   i;

	// 射影行列を初期化（初期化の前に現在の行列を退避）
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0.0, win_width, win_height, 0.0 );

	// モデルビュー行列を初期化（初期化の前に現在の行列を退避）
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	// Ｚバッファ・ライティングはオフにする
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );

	// メッセージの描画
	glColor3f( 1.0, 0.0, 0.0 );
	glRasterPos2i( 8, 8 + 18 );
	for ( i=0; message[i]!='\0'; i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, message[i] );

	// 設定を全て復元
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	return 0;
}


//
//  ウィンドウ再描画時に呼ばれるコールバック関数
//
void  display( void )
{
	// 画面をクリア（ピクセルデータとＺバッファの両方をクリア）
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// 変換行列を設定（モデル座標系→カメラ座標系）
	//（カメラが (0.0, 0.0, camera_distance) の位置にあるとする）
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

	// 中央の角すいを描画
	glPushMatrix();
		glTranslatef( 0.0, 1.0, 0.0 );
		glRotatef( theta, 0.0f, 1.0f, 0.0f );
		glColor3f( 1.0, 0.0, 0.0 );
		renderPyramid1();
	glPopMatrix();

	// 右の角すいを描画
	glPushMatrix();
		glTranslatef( 3.0, 1.0, 0.0 );
		glRotatef( theta, 1.0f, 0.0f, 0.0f );
		glColor3f( 0.0, 1.0, 0.0 );
		renderPyramid2();
	glPopMatrix();

	// 左の角すいを描画
	glPushMatrix();
		glTranslatef(-3.0, 1.0, 0.0 );
		glRotatef( theta, 0.0f, 0.0f, 1.0f );
		glColor3f( 0.0, 0.0, 1.0 );
		renderPyramid3();
	glPopMatrix();

	//  テキストを描画
	drawMessage();

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

	// ウィンドウのサイズを記録（テキスト描画処理のため）
	win_width = w;
	win_height = h;
}


//
// マウスクリック時に呼ばれるコールバック関数
//
void  mouse( int button, int state, int mx, int my )
{
	// 右ボタンがクリックされたらオブジェクトの回転方向を反転する
	if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) ) 
		turn *= -1.0;

	// 右ボタンが押されたらドラッグ開始
	if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_DOWN ) )
		drag_mouse_r = 1;
	// 右ボタンが離されたらドラッグ終了
	else if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_UP ) )
		drag_mouse_r = 0;

	// 中ボタンが押されたらドラッグ開始
	if ( ( button == GLUT_MIDDLE_BUTTON ) && ( state == GLUT_DOWN ) )
		drag_mouse_m = 1;
	// 中ボタンが離されたらドラッグ終了
	else if ( ( button == GLUT_MIDDLE_BUTTON ) && ( state == GLUT_UP ) )
		drag_mouse_m = 0;

	// シフトキーを押しながら、左ボタンが押されたらドラッグ開始
	if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) && (glutGetModifiers()&GLUT_ACTIVE_SHIFT ))
		drag_mouse_l = 1;
	// シフトキーを押しながら、左ボタンが離されたらドラッグ終了
	else if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_UP ) && (glutGetModifiers()&GLUT_ACTIVE_SHIFT ) )
		drag_mouse_l = 0;

	// 現在のマウス座標を記録
	last_mouse_x = mx;
	last_mouse_y = my;
}


//
// マウスドラッグ時に呼ばれるコールバック関数
//
void  motion( int mx, int my )
{
	// 右ボタンのドラッグ中は視点を回転する
	if ( drag_mouse_r )
	{
		// 前回のマウス座標と今回のマウス座標の差に応じて視点を回転

		// マウスの横移動に応じてＹ軸を中心に回転
		camera_yaw -= ( mx - last_mouse_x ) * 1.0;
		if ( camera_yaw < 0.0 )
			camera_yaw += 360.0;
		else if ( camera_yaw > 360.0 )
			camera_yaw -= 360.0;

		// マウスの縦移動に応じてＸ軸を中心に回転
		camera_pitch -= ( my - last_mouse_y ) * 1.0;
		if ( camera_pitch < -90.0 )
			camera_pitch = -90.0;
		else if ( camera_pitch > 90.0 )
			camera_pitch = 90.0;

		// 今回のマウス座標を記録
		last_mouse_x = mx;
		last_mouse_y = my;
	}

	// シフトキーを押しながら、左ボタンドラッグ
	if ( drag_mouse_l )
	{
		// 前回のマウス座標と今回のマウス座標の差に応じて視点を回転

		// マウスの横移動に応じてＹ軸を中心に回転
		camera_roll -= ( mx - last_mouse_x ) * 1.0;
		if ( camera_roll < 0.0 )
			camera_roll += 360.0;
		else if ( camera_roll > 360.0 )
			camera_roll -= 360.0;

		// 今回のマウス座標を記録
		last_mouse_x = mx;
		last_mouse_y = my;
	}

	// 中ボタン
	if ( drag_mouse_m )
	{
		// 前回のマウス座標と今回のマウス座標の差に応じて視点を回転

		// マウスの横移動に応じてＺ軸を中心に回転
		camera_distance -= ( my - last_mouse_y ) * 0.05;

		// 今回のマウス座標を記録
		last_mouse_x = mx;
		last_mouse_y = my;
	}
}


//
//  アイドル時に呼ばれるコールバック関数
//
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
	glutMotionFunc( motion );
	glutIdleFunc( idle );

	// 環境初期化
	initEnvironment();

	// GLUTのメインループに処理を移す
    glutMainLoop();
    return 0;
}

