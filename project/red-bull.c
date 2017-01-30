#include "./PDB.h"
#include "./red_bull.h"

PDB pdb;
int main(int argc, char* argv[])
{	
    FILE *fp;
	if(NULL==(fp=fopen(argv[1],"r"))){
	  printf("fopen error1!\n");
	  return 1;
	}
	pdbRead(fp,&pdb);
	fclose(fp);
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);  
	glutInitWindowPosition(WIN_POSX, WIN_POSY); 
	glutCreateWindow(WIN_NAME);
	myInit();

	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMouseMotion);
	glutPassiveMotionFunc(myMousePassiveMotion);
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);

	glutMainLoop(); 
	return 0;
}
