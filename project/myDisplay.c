#include "./red_bull.h"
#include "./PDB.h"

#define POINTNUM (6)

static GLuint    displayList1          = 1;
static GLuint    displayList2          = 2;
static GLboolean needDisplayListMaking = GL_TRUE;

static GLfloat materialColor[4];
static GLfloat materialSpecular[4] = {0.2, 0.2, 0.2, 1.0 } ;
static GLfloat materialAmbient[4] = {0.1, 0.1, 0.1, 1.0 } ;

extern PDB pdb;

void __getColorRGB1(GLfloat color[3], char element[3]){
	char check[5] = "CONHP";
	if(element[0] == check[0]){
		color[0] = 0.5;
		color[1] = 0.5;
		color[2] = 0.5;
	}else if(element[0] == check[1]){
		color[0] = 0;
		color[1] = 0;
		color[2] = 1;
	}else if(element[0] == check[2]){
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
	}else if(element[0] == check[3]){
		color[0] = 1;
		color[1] = 1;
		color[2] = 0;
	}else if(element[0] == check[4]){
		color[0] = 0.5;
		color[1] = 1;
		color[2] = 0;
	}
}


void __getColorRGB2(GLfloat color[3], char resName[4]){
	char check[11][4] = {
		"ARG","HIS","LYS",
		"ASP","GLU","TYR","CYS",
		"SER","THR","ASN","GLN"
	};
	int i=0;
	for(;i<3;i++){
		if(strstr(resName,check[i])!=NULL){
			color[0] = 1;
			color[1] = 0;
			color[2] = 0;
			return;
		}
	}for(;i<7;i++){
		if(strstr(resName,check[i])!=NULL){
			color[0] = 0;
			color[1] = 0;
			color[2] = 1;
			return;
		}
	}for(;i<11;i++){
		if(strstr(resName,check[i])!=NULL){
			color[0] = 0.5;
			color[1] = 1;
			color[2] = 0;
			return;
		}
	}
	color[0] = 0.5;
	color[1] = 0.5;
	color[2] = 0.5;
}



void myDisplayListMake1(void){
	GLfloat color[3]; 		/* 使用する色の指定 */
	GLdouble radius=0.5;	        /* 作成する球面の半径 */	
	GLint    slices=10;             /* 球面を分割するためのパラメータ */
	GLint    stacks=10;

	glNewList(displayList1, GL_COMPILE);
		for(pdb.current = pdb.top; pdb.current->nextAtom!=NULL; pdb.current = pdb.current->nextAtom) {
			/* 色の設定 */
			__getColorRGB1(color,pdb.current->atom.element);
			glColor3f(color[0], color[1], color[2]);              /* 照明がないときのための色 */
			materialColor[0] = color[0];	materialColor[1] = color[1];	materialColor[2] = color[2];	
			materialColor[3] = 1.0;
			glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); /* 物質の鏡面反射の色の設定 */
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);     /* 物質の拡散光の色の設定  */
			glMaterialf(GL_FRONT, GL_SHININESS, 10.0);             /* 物質の鏡面指数 */
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);   /* 物質の環境光の色の設定 */
	
			/* 球面の創出 */
			glPushMatrix();
				//glScalef (1.0, 1.0, 1.0);                /* x, y, z軸に沿って、拡大縮小 */
				glTranslatef(pdb.current->atom.x, pdb.current->atom.y, pdb.current->atom.z); /* 移動 */
				glutSolidSphere(radius, slices, stacks);
			glPopMatrix();
		}
		/* 色の設定 */
			__getColorRGB1(color,pdb.current->atom.element);
			glColor3f(color[0], color[1], color[2]);              /* 照明がないときのための色 */
			materialColor[0] = color[0];	materialColor[1] = color[1];	materialColor[2] = color[2];	
			materialColor[3] = 1.0;
			glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); /* 物質の鏡面反射の色の設定 */
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);     /* 物質の拡散光の色の設定  */
			glMaterialf(GL_FRONT, GL_SHININESS, 10.0);             /* 物質の鏡面指数 */
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);   /* 物質の環境光の色の設定 */
	
			/* 球面の創出 */
			glPushMatrix();
				//glScalef (1.0, 1.0, 1.0);                /* x, y, z軸に沿って、拡大縮小 */
				glTranslatef(pdb.current->atom.x, pdb.current->atom.y, pdb.current->atom.z); /* 移動 */
				glutSolidSphere(radius, slices, stacks);
			glPopMatrix();
	glEndList();
}


void myDisplayListMake2(void){
	GLfloat color[3];

	glNewList(displayList2, GL_COMPILE);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
		// 色の設定
		__getColorRGB2(color,pdb.top->atom.resName);
		glColor3f(color[0], color[1], color[2]); /* 照明を考えないときの色 */	
		// 頂点の設定
		glVertex3f(pdb.top->atom.x, pdb.top->atom.y, pdb.top->atom.z);
		for(pdb.current = pdb.top; pdb.current->nextAtom!=NULL; pdb.current = pdb.current->nextAtom) {
			__getColorRGB2(color,pdb.current->atom.resName); 
			glColor3f(color[0], color[1], color[2]);	
			glVertex3f((pdb.current->atom.x + pdb.current->nextAtom->atom.x)/2.0,
				   (pdb.current->atom.y + pdb.current->nextAtom->atom.y)/2.0,
				   (pdb.current->atom.z + pdb.current->nextAtom->atom.z)/2.0);

			__getColorRGB2(color,pdb.current->nextAtom->atom.resName);
			glColor3f(color[0], color[1], color[2]);	
			glVertex3f(pdb.current->nextAtom->atom.x,
				   pdb.current->nextAtom->atom.y,
				   pdb.current->nextAtom->atom.z);
		}
	glEnd();
	glPopMatrix();
	glEndList();

}



void  myDisplayListMake(void){
	myDisplayListMake1();
	myDisplayListMake2();
	needDisplayListMaking = GL_FALSE;
}


void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cameraInfo* camera;
	camera = getMyCamera();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	myLightSet();
    gluPerspective(camera->Fovy, camera->Aspect, camera->ClipNear, camera->ClipFar);   
    gluLookAt(camera->Eye[0], camera->Eye[1], camera->Eye[2],
     		camera->Centre[0], camera->Centre[1], camera->Centre[2],
     		camera->Up[0], camera->Up[1], camera->Up[2]);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//myLightSet();
	
	// 高速化のためにディスプレイリストを使用する。
	if(GL_TRUE == needDisplayListMaking) {
		myDisplayListMake();
	}

	glPushMatrix();
		//myLightSet();
		glCallList(displayList1); /* ディスプレイリスト1を取り出す */
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(displayList2); /* ディスプレイリスト2を取り出す */
		glEnable(GL_LIGHTING);
	glPopMatrix();

	 // ティーポットを描く
	 glPushMatrix();
		glTranslatef(1, 1, 1); 
		myLightSet();
		glutSolidTeapot(1.0);
	glPopMatrix();
	

	glutSwapBuffers();
}
