#include "myGUI.h"

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

// left botton
    if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) ){
        drag_mouse_l = 1;
    }
    else if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_UP ) ){
        drag_mouse_l = 0;
    }

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

// velocity control



        // 今回のマウス座標を記録
        last_mouse_x = mx; 
        last_mouse_y = my; 
    }
    // left drag control to verosity
/*
    if (drg_mouse_l){

    }   
*/
}

