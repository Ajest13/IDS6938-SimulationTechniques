void my_init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//
	//  Change this to proportions for MxN
	//
	gluOrtho2D(0.0, (double)pixel_width, 0.0, (double)pixel_height);
	glMatrixMode(GL_MODELVIEW);

	return;
}


void box_draw(int i, int j, bool state_ij)
{
	float p[2];
	GLfloat a;
	GLfloat b;
	GLfloat c;

	GLfloat gray[3] = { 0.8, 0.8, 0.8 };
	GLfloat yellow[3] = { 1.0, 1.0, 0.0 };

	if (state_ij)
	{
		glColor3fv(yellow);
	}
	else
	{
		glColor3fv(gray);
	}

	c = box_size;
	a = j   * c;
	b = (m - 1 - i) * c;
	//
	//  Fill boxes with gray or yellow.
	//
	glBegin(GL_POLYGON);
	p[0] = a + 3;
	p[1] = b + 3;
	glVertex2fv(p);
	p[0] = a + c - 3;
	p[1] = b + 3;
	glVertex2fv(p);
	p[0] = a + c - 3;
	p[1] = b + c - 3;
	glVertex2fv(p);
	p[0] = a + 3;
	p[1] = b + c - 3;
	glVertex2fv(p);
	glEnd();
	//
	//  Draw box boundaries in BLUE.
	//
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINE_LOOP);
	p[0] = a;
	p[1] = b;
	glVertex2fv(p);
	p[0] = a + c;
	p[1] = b;
	glVertex2fv(p);
	p[0] = a + c;
	p[1] = b + c;
	glVertex2fv(p);
	p[0] = a;
	p[1] = b + c;
	glVertex2fv(p);
	glEnd();
	//
	//  Clear all the buffers.
	//
	glFlush();

	return;
}



void display()
{
	int i;
	int j;
	//
	//  Clear the window.
	//
	glClear(GL_COLOR_BUFFER_BIT);
	//
	//  Draw each box.
	//
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
		{
			box_draw(i, j, state[i + j*m]);
		}
	}
	glFlush();
	//
	//  Time to swap buffers.
	//
	glutSwapBuffers();

	return;
}





void my_mouse(int btn, int mouse_state, int x, int y)
{
	int i;
	int j;
	int k;

	i = y / box_size;    
	j = x / box_size;

	if (btn == GLUT_LEFT_BUTTON && mouse_state == GLUT_DOWN)
	{
		theGameofLife.state_reset(m, n, state, i, j);
	}
	else if (btn == GLUT_MIDDLE_BUTTON && mouse_state == GLUT_DOWN)
	{
		theGameofLife.state_reset(m, n, state, i, j);
	}
	else if (btn == GLUT_RIGHT_BUTTON && mouse_state == GLUT_DOWN)
	{
		theGameofLife.state_reset(m, n, state, i, j);
	}
	//
	//  Redisplay the screen.
	//  Since this causes a jerky screen, it would be best to double buffer!
	//
	display();

	return;
}


void my_keyboard(unsigned char key, int x, int y)
{
	theGameofLife.state_update(m, n, state);
	display();

	return;
}