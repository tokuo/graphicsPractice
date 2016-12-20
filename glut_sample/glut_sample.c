//
//  GLUTを使ったサンプルプログラム
//      Originalted From Oshita
//		Modified by Tac

#include <stdio.h>
#include <stdlib.h>

// GLUTヘッダファイルのインクルード
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

// グローバル変数
// 同一ファイル内部の関数間で変数を持ち合う
static int     turn = 1;
static float   theta = 0.0;

//
//  ウィンドウ再描画時に呼ばれるコールバック関数
//
void  display( void )
{
	float  angle;

	// 画面をクリア（ピクセルデータとＺバッファの両方をクリア）
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// 変換行列を設定（モデル座標系）
	//（カメラが (0.0, 1.0, 5.0) の位置にあるとする）
    glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();                // 単位行列とする
	glTranslatef( 0.0, -1.0, -5.0 ); // モデルを移動させる行列操作  

	// 地面を描画
	glBegin( GL_POLYGON ); // 多角形の描画開始：法線ベクトルに対して右回り
		glColor3f( 0.5, 0.8, 0.5 );  // 色の設定
		glNormal3f( 0.0, 1.0, 0.0 ); // 面の法線ベクトルの設定
		glVertex3f( 3.0, 0.0, 3.0 ); // 面の頂点の設定 
		glVertex3f( 3.0, 0.0,-3.0 );
		glVertex3f(-3.0, 0.0,-3.0 );
		glVertex3f(-3.0, 0.0, 3.0 );
	glEnd();

	// 物体の回転角度を計算（360度表現→ラジアンに変換）
	angle = M_PI * theta / 180.0;

	// 変換行列を設定（物体のモデル座標系）
	//（物体が (0.0, 1.0, 0.0) の位置にあり、Y軸を中心に回転しているとする）
	// 移動
	glTranslatef( 0.0, 1.0, 0.0 );
	// 回転角、回転軸
	glRotatef( angle, 0.0f, 1.0f, 0.0f );

	// 物体（２枚のポリゴン）を描画: 1枚の面の表側と裏側の設定
	glBegin( GL_TRIANGLES );
		glColor3f( 0.0, 0.0, 1.0 );  // 色の設定
		glNormal3f( 0.0, 0.0, 1.0 ); // 面の法線ベクトルの設定
		glVertex3f(-1.0, 1.0, 0.0 ); // 面の頂点の設定
		glVertex3f( 0.0,-1.0, 0.0 );
		glVertex3f( 1.0, 0.5, 0.0 );

		glColor3f( 1.0, 0.0, 0.0 );  // 色の設定
		glNormal3f( 0.0, 0.0,-1.0 ); // 面の法線ベクトルの設定
		glVertex3f(-1.0, 1.0, 0.0 ); // 面の頂点の設定
		glVertex3f( 1.0, 0.5, 0.0 );
		glVertex3f( 0.0,-1.0, 0.0 );
	glEnd();

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
	// 視界角, アスペクト比, 視点からの距離(手前), 視点からの距離(奧)
	// 視錐台の設定
    gluPerspective(45, (double)w/h, 1, 500);
}

//
// マウスクリック時に呼ばれるコールバック関数
//
void  mouse( int button, int state, int mx, int my )
{
	// 左ボタンがクリックされたら回転方向を正にする
	if(( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN )) {
		turn = 1.0;
	// 右ボタンがクリックされたら回転方向を負にする
	} else if( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_DOWN ) ) {
		turn = -1.0;
	}	

        // button state mx, my; mx, myはマウスがクリックされた位置	
#undef DEBUG
#ifdef DEBUG
	fprintf(stderr, ""); 
#endif
}


//  
//  アイドル時に呼ばれるコールバック関数
//  (なにもしないとき)
//

void  idle( void )
{
	// 物体を回転
	theta += 10 * turn;

	// 再描画の指示を出す（ この後で再描画のコールバック関数が呼ばれる: この場合は、display()関数 ）
	glutPostRedisplay();
}

//
//  環境初期化関数
//
void  init_environment( void )
{
	// 光源を作成する
	float  light0_position[] = { 1.0, 1.0, 1.0, 1.0 }; // 光源位置
	float  light0_diffuse[]  = { 0.8, 0.8, 0.8, 1.0 }; // 拡散光
	float  light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // 鏡面反射
	float  light0_ambient[]  = { 0.1, 0.1, 0.1, 1.0 }; // 環境光
	glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light0_diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light0_specular );
	glLightfv( GL_LIGHT0, GL_AMBIENT, light0_ambient );
	glEnable( GL_LIGHT0 );                             // ライト0: 点灯 

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
// キーボードが押されたときに呼び出されるコールバック関数 
//
void
key(unsigned char key, int x, int y)
{

#undef DEBUG
#ifdef DEBUG
	fprintf(stderr, "What key ? \n"); 
#endif
	switch(key) {
		case 'q':
			exit(EXIT_FAILURE);
			break;
	}
}

//
//  メイン関数（プログラムはここから開始）
//
int  main( int argc, char ** argv )
{
	// GLUTの初期化
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH ); //ディスプレイモードの設定: ダブルバッファ、RBGA(Alpha値)
    glutInitWindowSize(400, 400 );  // ウィンドウの大きさ
    glutInitWindowPosition(100, 100 ); // ウィンドウの位置
    glutCreateWindow("New GLUT program"); // ウィンドウの生成
	
// コールバック関数の登録：イベントが生じたときに呼び出される関数を登録（引数は決まっている）
// 途中で変更も可能（例えば、マウスの利用の仕方が変更になる）
    glutDisplayFunc( display ); // ディスプレイの再描画
    glutReshapeFunc( reshape ); // ウィンドウの大きさが変更されたとき
    glutMouseFunc( mouse ); // マウスのボタンが押されたとき
    glutIdleFunc( idle ); // イベントが何もないとき
    glutKeyboardFunc( key ); // キーボードが押されたとき

// 環境初期化
    init_environment();

// GLUTのメインループに処理を移す
// イベントが生じたときに上記の関数を呼び出す
    glutMainLoop();
    return 0;
}

