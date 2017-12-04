#include "zc_glutInit.h"

int zcGlutInit(int& argc, char** argv, char* const projName)
{
	//Configure initial window state
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(5, 5);
	glutInitWindowSize(1200, 800);
	int win = glutCreateWindow(projName);

	return win;
}
