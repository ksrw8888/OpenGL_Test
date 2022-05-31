#pragma comment( lib, "SOIL.lib" )
#include <cmath>
#include <GL/glut.h>
#include <GL/SOIL.h>
#include <cstdio>   // for opening file



//#include <cstdio>   // for opening file

int mx = 0, my = 0;
GLuint texture01, texture02, texture03;

GLuint LoadSOILTexture(const char* filename);

void shape1(double radius, double maxHeight);

void normal(float n[], float p0[], float p1[], float p2[]);
void rectangle(double w, double h);
void box(float x, float y, float z);
void fan(double radius, double degree);

void gun();
void mouseMove(int x, int y) {
	mx = x;
	my = y;
	glutPostRedisplay();
}

void cylinder(float r, float length)
{
	int const n = 24;
	float PI = (float)acos(-1.0);
	float theta = 0.0, x[n + 1], y[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		x[i] = (float)(r * cos(theta));
		y[i] = (float)(r * sin(theta));
		theta = theta + (float)(2 * PI / n);
	}

	/*
	glBegin(GL_QUAD_STRIP);
	for(int i=0; i<n; i++)
	{
	glVertex3f( x[i],y[i],0.0 );
	glVertex3f( x[i],y[i],-length);
	glVertex3f( x[i+1],y[i+1],0.0 );
	glVertex3f( x[i+1],y[i+1],-length );
	}
	glEnd(); */

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(x[i], y[i], 0.0);
		glVertex3f(x[i], y[i], -length);
		glVertex3f(x[i + 1], y[i + 1], -length);
		glVertex3f(x[i + 1], y[i + 1], 0.0);
		glVertex3f(x[i], y[i], 0.0);
	}
	glEnd();
}


void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0, (float)w / (float)h, 0.01, 1000.0);
	glMatrixMode(GL_MODELVIEW);

}



void draw_Aux_axis()
{
	glColor3f(1, 0, 0);
	glScalef(10, 10, 10);
	glBegin(GL_POLYGON);

	glVertex3f(0.5, 0.3, 0);
	glVertex3f(0.7, 0.0, 0);
	glVertex3f(0.5, -0.3, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0, -0.2, 0);
	glVertex3f(0.5, -0.2, 0);
	glVertex3f(0.5, 0.2, 0);
	glVertex3f(0.0, 0.2, 0);
	glEnd();

	glColor3f(0, 1, 0);

	glBegin(GL_POLYGON);
	glVertex3f(0.3, 0.5, 0);
	glVertex3f(0.0, 0.7, 0);
	glVertex3f(-0.3, 0.5, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.2, 0.0, 0);
	glVertex3f(-0.2, 0.5, 0);
	glVertex3f(0.2, 0.5, 0);
	glVertex3f(0.2, 0.0, 0);
	glEnd();
	glScalef(0.1, 0.1, 0.1);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearDepth(1.0f);
	glTranslatef(0.0, 0.0, -200.0f);

	glRotatef(-20 + mx, 0.0f, 1.0f, 0.0f);
	glRotatef(20 + my, 1.0f, 0.0f, 0.0f);
	//glRotatef(0 + mz, 0.0f, 1.0f, 0.0f);
	



	//render(0.2125, 0.1275, 0.054, 0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.7);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture01);

////////////////////////////////////////////////////////////
	glTranslatef(-30, 0, 0);   //把圖基本定位往後條

	glPushMatrix();

	for (int i = 0; i < 500; i++)
	{
		gun();
		glTranslatef(0, 0, 0.02);
	}

	glPopMatrix();

	glPushMatrix();

	glBegin(GL_POLYGON);
	glVertex3f(60, 40, 0);
	glVertex3f(70, 40, 0);
	glVertex3f(70, 19, 0);
	glVertex3f(60, 19, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(60, 40, 10);
	glVertex3f(70, 40, 10);
	glVertex3f(70, 19, 10);
	glVertex3f(60, 19, 10);
	glEnd();

	glPopMatrix();
///////////////////////////////////////////////////////////

	glBindTexture(GL_TEXTURE_2D, texture02);
	glPushMatrix();

	glTranslatef(98, 30, 5);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	GLUquadricObj* q;
	q = gluNewQuadric();// Create a new quadratic
	gluDisk(q, 0, 3, 32, 1);
	glTranslatef(0, 0, -1);

	for (int i = 0; i < 500; i++)
	{
		
		gluQuadricNormals(q, GL_SMOOTH);
		gluQuadricTexture(q, GL_TRUE);// Enable texture coords
		gluDisk(q, 2.5, 3, 32, 1);
		glTranslatef(0,0,0.02);
	}
	
	glPopMatrix();
//////////////////////////////////////////////////////////////
	
	glPushMatrix();

	glTranslatef(40, 40, 1);
	box(54, -8, -8);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(66, 14, 4);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < 50; i++)
	{
		shape1(6,12);
		glTranslatef(0, 0, 0.04);
	}
	

	glPopMatrix();
	
	glFlush();

}

void init(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	float position[] = { 3.0, 3.0, 3.0, 0.0 };
	float white[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);


	texture01 = LoadSOILTexture("Data/pink.bmp");
	texture02 = LoadSOILTexture("Data/iron-gray.bmp");
	texture03 = LoadSOILTexture("Data/Wood007.bmp");



}


int main() {
	int w = 640;
	int h = 480;
	glutInitWindowSize(w, h);
	glutCreateWindow("SOIL");
	init();
	glutReshapeFunc(reshape);
	glutMotionFunc(mouseMove);
	glutDisplayFunc(display);
	glutMainLoop();
}







void normal(float n[], float p0[], float p1[], float p2[])
{
	float u[] = { 0,0,0 };
	float v[] = { 0,0,0 };

	float magnitude = 0;

	u[0] = p1[0] - p0[0];
	u[1] = p1[1] - p0[1];
	u[2] = p1[2] - p0[2];

	v[0] = p2[0] - p0[0];
	v[1] = p2[1] - p0[1];
	v[2] = p2[2] - p0[2];
	n[0] = u[1] * v[2] - u[2] * v[1];
	n[1] = u[2] * v[0] - u[0] * v[2];
	n[2] = u[0] * v[1] - u[1] * v[0];
	magnitude = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	// normalization
	n[0] = n[0] / magnitude;
	n[1] = n[1] / magnitude;
	n[2] = n[2] / magnitude;
}








void box(float x, float y, float z)
{

	float p0[] = { 0,0,0 }, p1[] = { x, 0, 0 }, p2[] = { x,y, 0 }, p3[] = { x, y,0 };

	float n1[] = { 0,0,0 };

	glPushMatrix();
	rectangle(x, y);  // front and back
	glTranslatef(0, 0, -z);
	rectangle(x, y);
	glTranslatef(0, 0, z);


	glRotatef(-90, 1.0, 0, 0);//top and bottom
	rectangle(x, z);
	glTranslatef(0, 0, y);
	rectangle(x, z);




	glRotatef(90, 1.0, 0, 0);

	glRotatef(90, 0.0, 1.0, 0);

	glTranslatef(0, -y, 0);
	rectangle(z, y);
	glTranslatef(0, 0, x);
	rectangle(z, y);

	glPopMatrix();
}

void rectangle(double w, double h)
{
	float pt1[] = { 0,0,0 }, pt2[] = { w,0,0 }, pt3[] = { w,h,0 }, n[3] = { 0 };
	glBegin(GL_QUADS);

	normal(n, pt1, pt2, pt3);
	glNormal3fv(n);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0, h, 0.0);
	glTexCoord2f(1, 1); glVertex3f(w, h, 0.0);
	glTexCoord2f(1, 0.0); glVertex3f(w, 0.0, 0.0);
	glEnd();
}

GLuint LoadSOILTexture(const char* filename)
{
	GLuint texture;
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return texture;
}


void shape1(double radius, double maxHeight)
{
	const double PI = acos(-1.0);
	float n[] = { 0,0,0 };
	double x[19] = { 0 }, y[19] = { 0 };
	double degree = 10.0;
	double theta = 0.0;
	double diameter = 2.0 * radius;
	double dtheta = degree * PI / 180.0;
	for (int i = 0; i < 19; i++)
	{
		x[i] = radius * cos(theta);
		y[i] = radius * sin(theta);
		theta = theta + dtheta;
	}
	float p0[] = { 0,0,0 }, p1[] = { 0,0,0 }, p2[] = { 0,0,0 };
	for (int i = 0; i < 18; i++)
	{
		glBegin(GL_QUADS);
		p0[0] = x[i];
		p0[1] = y[i];
		p0[2] = 0;
		p1[0] = x[i];
		p1[1] = maxHeight;
		p1[2] = 0;
		p2[0] = x[i + 1];
		p2[1] = maxHeight;
		p2[2] = 0;
		normal(n, p0, p1, p2);
		glTexCoord2f((x[i] - x[18]) / diameter, y[i] / maxHeight);
		glVertex2f(x[i], y[i]);
		glTexCoord2f((x[i] - x[18]) / diameter, 1.0);
		glVertex2f(x[i], maxHeight);
		glTexCoord2f((x[i + 1] - x[18]) / diameter, 1.0);
		glVertex2f(x[i + 1], maxHeight);
		glTexCoord2f((x[i + 1] - x[18]) / diameter, y[i + 1] /
			maxHeight); glVertex2f(x[i + 1], y[i + 1]);
		glEnd();
	}
}

void fan(double radius, double degree)
{
	const double PI = acos(-1.0);
	float n[] = { 0,0,0 };
	double x[37] = { 0 }, y[37] = { 0 };
	double diameter = 2.0 * radius;
	double radian = degree * PI / 180.0;
	//subdivision
	double dtheta = radian / 36.0;
	for (int i = 0; i < 37; i++)
	{
		x[i] = radius * cos(i * dtheta);
		y[i] = radius * sin(i * dtheta);
	}
	float p0[] = { 0,0,0 }, p1[] = { 0,0,0 }, p2[] = { 0,0,0 };
	for (int i = 0; i < 36; i++)
	{
		glBegin(GL_POLYGON);
		p0[0] = x[i];
		p0[1] = y[i];
		p0[2] = 0;
		p1[0] = x[i + 1];
		p1[1] = y[i + 1];
		p1[2] = 0;
		p2[0] = 0;
		p2[1] = 0;
		p2[2] = 0;
		normal(n, p0, p1, p2);
		glTexCoord2f(x[i] / diameter + 0.5, y[i] / diameter + 0.5);
		glVertex2f(x[i], y[i]);
		glTexCoord2f(x[i + 1] / diameter + 0.5, y[i + 1] / diameter + 0.5);
		glVertex2f(x[i + 1], y[i + 1]);
		glTexCoord2f(0.5, 0.5); glVertex2f(0, 0);
		glEnd();
	}
}

void gun() {



	glPushMatrix();                 //左下長方+左洞下半部
	rectangle(24, 20);
	glBegin(GL_POLYGON);
	glVertex3f(24, 0, 0);
	glVertex3f(34, 4, 0);
	glVertex3f(24, 4, 0);

	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(42, 8, 0);
	glVertex3f(60, 8, 0);
	glVertex3f(60, 10.1, 0);
	glVertex3f(48, 10.1, 0);

	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(42, 8, 0);
	glVertex3f(24, 0, 0);
	glVertex3f(42, -10, 0);
	glEnd();
	glTranslatef(42, 8, 0);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	//shape1(6, 3);
	fan(18, 90);
	glPopMatrix();

	//下3組指令完成左洞
	glPushMatrix();
	glTranslatef(36, 12, 0);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	shape1(8, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(48, 15, 0);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	shape1(4.9, 7);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(60, 15, 0);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	shape1(4.9, 7);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(60, 8, 0);
	glVertex3f(66, 4, 0);
	glVertex3f(68, 4, 0);
	glVertex3f(65, 10, 0);
	glVertex3f(60, 10, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(66, 6, 0);
	glVertex3f(63, -4, 0);
	glVertex3f(75, -4, 0);
	glVertex3f(75, 6, 0);
	glEnd();
	glTranslatef(75, 6, 0);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	fan(10, 90);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	glTranslatef(-2, 0, 0);
	rectangle(12, 16);

	glPopMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(90, 20, 0);
	glVertex3f(96, 17, 0);
	glVertex3f(100, 10, 0);
	glVertex3f(100, 22, 0);
	glVertex3f(97, 24, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(96, 17, 0);
	glVertex3f(96, 5, 0);
	glVertex3f(100, 5, 0);
	glVertex3f(100, 10, 0);

	glEnd();
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0, 40, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -21, 0);
	glVertex3f(40, -21, 0);
	glVertex3f(40, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(40, -7, 0);
	glVertex3f(40, -21, 0);
	glVertex3f(94, -21, 0);
	glVertex3f(94, -7, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(97, 0, 0);
	glVertex3f(97, -21, 0);
	glVertex3f(94, -21, 0);
	glVertex3f(94, -0, 0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();

	glBegin(GL_POLYGON);
	glVertex3f(60, 40, 0);
	glVertex3f(70, 40, 0);
	glVertex3f(76, 45, 0);
	glVertex3f(66, 45, 0);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(72, 50, 0);
	glVertex3f(66, 45, 0);
	glVertex3f(76, 45, 0);
	glVertex3f(94, 40, 0);
	glVertex3f(97, 40, 0);
	glVertex3f(97, 45, 0);
	glVertex3f(93, 50, 0);
	glEnd();


	glPopMatrix();


	/*glPushMatrix();

	glTranslatef(97, 30, 0);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	rectangle(5, 10);

	glPopMatrix();
	*/
}