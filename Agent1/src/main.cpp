#include <stdlib.h>
#include <math.h>

# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>

#include <GL/glut.h>
#include "globals.h"
#include "drawing.h"


#define mysize 800

using namespace std;





//****************************************************************************80

int main(int argc, char *argv[])
{
	int i;
	int iwrap;
	int j;

	

	cout << "\n";
	cout << "CONWAY'S GAME OF LIFE\n";


	state = new bool[m * n];
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
		{
			state[i + j*m] = false;
		}
	}

	glutInit(&argc, argv);
	//
	//  Use double buffering; otherwise the screen jitters when the user
	//  updates it.
	//
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	if (m == n)
	{
		box_size = (mysize / m);
		pixel_width = mysize;
		pixel_height = mysize;
	}
	else if (m < n)
	{
		box_size = (mysize / n);
		pixel_width = n * box_size;
		pixel_height = m * box_size;
	}
	else if (n < m)
	{
		box_size = (mysize / m);
		pixel_width = n * box_size;
		pixel_height = m * box_size;
	}
	cout << "  Box size = " << box_size << "\n";
	cout << "  Pixels(WxH):  " << pixel_width << "  "
		<< pixel_height << "\n";

	glutInitWindowSize(pixel_width, pixel_height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Life");
	glutDisplayFunc(display);
	my_init();
	glutKeyboardFunc(my_keyboard);
	glutMouseFunc(my_mouse);
	glutMainLoop();
	//
	//  Free memory.
	//
	delete[] state;
	//
	//  Terminate.
	//
	cout << "\n";
	cout << "LIFE\n";
	cout << "  Normal end of execution.\n";

	cout << "\n";
	

	return 0;
}
//****************************************************************************80


