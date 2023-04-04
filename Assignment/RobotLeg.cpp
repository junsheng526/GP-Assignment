#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <Math.h>

#define WINDOW_TITLE "Robot Leg"

int qNo = 1;
float x = 0, y = 0;		//origin of circle (x, y) (0,0)
//float radius = 0.5;		//radius of circle
float angle = 0;		//angle of circle
float PI = 3.1429;		//PI
float x2 = 0, y2 = 0;	//point on circle (x2,y2)
float noOfTri = 36;		//no of triangles



LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == 0x31)
			qNo = 1;
		else if (wParam == 0x32)
			qNo = 2;
		else if (wParam == 0x33)
			qNo = 3;
		else if (wParam == 0x35)
			qNo = 4;




		//mchange texture 1
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawPyramid(float sz) {
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
	//Face 1 : Bottom
	glColor3f(1.0, 0.0, 0.0); //red
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz, 0.0, sz);
	glVertex3f(sz, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2); //(0.25, 0.5, 0.25)
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(sz, 0.0, sz);
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(sz, 0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);
	glVertex3f(0.0, 0.0, 0.0);

	glEnd();
}

void drawCircle(float r) {
	glBegin(GL_TRIANGLE_FAN);
	//glVertex2f(x, y);

	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawRec(float sz) {
	glBegin(GL_QUADS);
	//Face 1 : Bottom
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz * 4, 0.0, sz);
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	//Face 2 : Left
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(0.0, 0.0, sz);
	//Face 3 : Front
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz);
	glVertex3f(sz * 4, 0.0, sz);
	//Face 4 : Right
	glVertex3f(sz * 4, 0.0, sz);
	glVertex3f(sz * 4, sz, sz);
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(sz * 4, 0.0, 0.0);
	//Face 5 : Back
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(sz * 4, sz, 0.0);
	//Face 6 : Top
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz);

	glEnd();
}

void drawSpecRec(float sz) {
	glBegin(GL_QUADS);
	//Face 1 : Bottom
	//glColor3f(1, 0, 0);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz * 4, 0.0, sz*2);//2,0,1
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	//Face 2 : Left
	//glColor3f(0, 1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(0.0, 0.0, sz);
	//Face 3 : Front
	//glColor3f(0, 0, 1);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz*2);//2,0.5,1
	glVertex3f(sz * 4, 0.0, sz*2);//2,0,1
	//Face 4 : Right
	//glColor3f(1, 1, 0);
	glVertex3f(sz * 4, 0.0, sz*2);//2,0,1
	glVertex3f(sz * 4, sz, sz*2);//2,0.5,1
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(sz * 4, 0.0, 0.0);
	//Face 5 : Back
	//glColor3f(1, 0, 1);
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(sz * 4, sz, 0.0);
	//Face 6 : Top
	//glColor3f(0, 1, 1);
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz*2);//2,0.5,1

	glEnd();
}

void drawSphere(float r, float sl, float st) {
	GLUquadricObj* sphere = NULL;			//create quadric obj pointer
	sphere = gluNewQuadric();				//create the quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//set the draw style
	gluSphere(sphere, r, sl, st);			//draw sphere
	gluDeleteQuadric(sphere);				//delete the quadric obj
}

void drawCylinder(float tr, float br, float h) {
	GLUquadricObj* cylinder = NULL;			//create quadric obj pointer
	cylinder = gluNewQuadric();				//create the quadric obj
	gluQuadricDrawStyle(cylinder, GLU_FILL);	//set the draw style
	gluCylinder(cylinder, tr, br, h, 30, 30);			//draw sphere
	gluDeleteQuadric(cylinder);				//delete the quadric obj
}

void drawGluCylinder(float tr, float br, float h) {
	GLUquadricObj* cylinder = NULL;			//create quadric obj pointer
	cylinder = gluNewQuadric();				//create the quadric obj
	gluQuadricDrawStyle(cylinder, GLU_LINE);	//set the draw style
	gluCylinder(cylinder, tr, br, h, 30, 2);			//draw sphere
	gluDeleteQuadric(cylinder);				//delete the quadric obj
}

void drawCone(float r, float h) {
	GLUquadricObj* cylinder = NULL;				//create quadric obj pointer
	cylinder = gluNewQuadric();					//create the quadric obj
	//gluQuadricDrawStyle(cylinder, GLU_FILL);	//set the draw style
	gluCylinder(cylinder, 0.0, r, h, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);					//delete the quadric obj
}

void drawConeLine(float r, float h) {
	GLUquadricObj* cylinder = NULL;				//create quadric obj pointer
	cylinder = gluNewQuadric();					//create the quadric obj
	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//set the draw style
	gluCylinder(cylinder, 0.0, r, h, 20, 10);	//draw cone
	gluDeleteQuadric(cylinder);					//delete the quadric obj
	glLineWidth(3.0);
}

void drawTri(float sz) {
	glBegin(GL_TRIANGLES);
	//Face 1 : Bottom
	//glColor3f(1, 0, 0);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz * 2, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	//Face 2 : Left
	glBegin(GL_QUADS);
	//glColor3f(0, 1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(0.0, 0.0, sz);
	//Face 3 : Front
	//glColor3f(0, 0, 1);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 2, sz, 0);
	glVertex3f(sz * 2, 0.0, 0);
	//Face 5 : Back
	//glColor3f(1, 0, 1);
	glVertex3f(sz * 2, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(sz * 2, sz, 0.0);
	glEnd();
	//Face 6 : Top
	glBegin(GL_TRIANGLES);
	//glColor3f(0, 1, 1);
	glVertex3f(sz * 2, sz, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glEnd();

	
}

//Shield Triangle
void drawShTri(float sz) {
	glBegin(GL_TRIANGLES);
	//Face 1 : Bottom
	glColor3f(0.45,0.41,0.32);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz * 2, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	//Face 2 : Left
	glBegin(GL_QUADS);
	glColor3f(0.55,0.5,0.4);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(0.0, 0.0, sz);
	//Face 3 : Front
	//glColor3f(0, 0, 1);
	glColor3f(0.55, 0.5, 0.4);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 2, sz, 0);
	glVertex3f(sz * 2, 0.0, 0);
	//Face 5 : Back
	glColor3f(0.55, 0.5, 0.4);
	glVertex3f(sz * 2, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(sz * 2, sz, 0.0);
	glEnd();
	//Face 6 : Top
	glBegin(GL_TRIANGLES);
	//glColor3f(0.67,0.64,0.55);
	glColor3f(0.55, 0.5, 0.4);
	glVertex3f(sz * 2, sz, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glEnd();


}	//Shield

//Shield Rectangle
void drawShRec(float sz) {
	glBegin(GL_QUADS);
	//Face 1 : Bottom
	glColor3f(0.45, 0.41, 0.32);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz * 4, 0.0, sz);
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	//Face 2 : Left
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(0.0, 0.0, sz);
	//Face 3 : Front
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz);
	glVertex3f(sz * 4, 0.0, sz);
	//Face 4 : Right
	glVertex3f(sz * 4, 0.0, sz);
	glVertex3f(sz * 4, sz, sz);
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(sz * 4, 0.0, 0.0);
	//Face 5 : Back
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(sz * 4, sz, 0.0);
	//Face 6 : Top
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz);

	glEnd();
}	//Shield

//Shield Quadrilateral
void drawShSpecRec(float sz) {						//Shield SPecRec
	glBegin(GL_QUADS);
	//Face 1 : Bottom
	//glColor3f(1, 0, 0);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz * 4, 0.0, sz * 2);//2,0,1
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	//Face 2 : Left
	//glColor3f(0, 1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(0.0, 0.0, sz);
	//Face 3 : Front
	//glColor3f(0, 0, 1);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz * 2);//2,0.5,1
	glVertex3f(sz * 4, 0.0, sz * 2);//2,0,1
	//Face 4 : Right
	//glColor3f(1, 1, 0);
	glVertex3f(sz * 4, 0.0, sz * 2);//2,0,1
	glVertex3f(sz * 4, sz, sz * 2);//2,0.5,1
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(sz * 4, 0.0, 0.0);
	//Face 5 : Back
	//glColor3f(1, 0, 1);
	glVertex3f(sz * 4, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(sz * 4, sz, 0.0);
	//Face 6 : Top
	//glColor3f(0, 1, 1);
	glVertex3f(sz * 4, sz, 0.0);
	glVertex3f(0.0, sz, 0.0);
	glVertex3f(0.0, sz, sz);
	glVertex3f(sz * 4, sz, sz * 2);//2,0.5,1

	glEnd();
}

void shield() {
	glPushMatrix();//shield all
	glScalef(0.15, 0.15, 0.15);
	glRotatef(270, 1.0, 0.0, 0.0);

	glPushMatrix();//1,2,3,4,8
	glScalef(1, 1.4, 1);
	//glTranslatef(0, 0.3, 0);

	glPushMatrix();//1,2,3
	glRotatef(10, 0, 0, 1);

	glPushMatrix();//1
	glTranslatef(0, -0.5, 0);
	drawShTri(0.5);
	glPopMatrix();//1

	glPushMatrix();//2
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(0, 0, 0);

	glPushMatrix();//2.1
	glScalef(0.5, 1, 2);//height,width,length
	glTranslatef(0, -0.5, 0);
	drawShRec(0.5);
	glPopMatrix();//2.1

	glPushMatrix();//2.2

	glRotatef(180, 0.0, 0.0, 1.0);
	glTranslatef(-1, 0, 1);
	glScalef(1, 1, 0.25);
	drawShTri(0.5);
	glPopMatrix();//2.2

	glPopMatrix();//2
	glPushMatrix();//3
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(0, 0, 1);
	glScalef(0.75, 1, 3);
	drawShSpecRec(0.5);

	glPopMatrix();//3

	glPopMatrix();//1,2,3

	glPushMatrix();//4,8
	glRotatef(-10, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	glPushMatrix();//4

	glPushMatrix();//4.1
	glTranslatef(1.5, -0.5, -2.5);
	glScalef(0.5, 0.33, 1);
	drawShTri(1.5);
	glPopMatrix();//4.1

	glPushMatrix();//4.2
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(1.5, 0, 2.5);
	glScalef(0.75, 1, 3);
	drawShSpecRec(0.5);

	glPopMatrix();//4.2

	glPopMatrix();//4

	glPushMatrix();//8.1
	glTranslatef(3, -0.5, -2.5);
	glScalef(0.5, 0.33, 1);
	drawShTri(1.5);
	glPopMatrix();//8.1

	glPushMatrix();//8.2
	glTranslatef(3, -0.5, -2.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.45, 0.33, 1);
	drawShRec(1.5);
	glPopMatrix();//8.2

	glPushMatrix();//8.3
	glRotatef(180, 1.0, 0.0, 0.0);
	//glTranslatef(-1, 0, 1);
	glTranslatef(3, 0, 5.2);
	glScalef(1.5, 1, 0.55);
	drawShTri(0.5);
	glPopMatrix();//8.3

	glPopMatrix();//4,8

	glPopMatrix();//1,2,3,4,8

	glPushMatrix();//6,7
	glTranslatef(0, -0.2, 0);
	glPushMatrix();//6

	glTranslatef(0, -0.5, -3.5);
	glScalef(1, 1, 2);
	drawShTri(0.5);
	glPopMatrix();//6

	glPushMatrix();//7.1

	glTranslatef(0.5, -0.5, -3.5);
	glScalef(0.5, -0.5, 2);
	glRotatef(180, 1, 0, 0);
	drawShTri(0.5);
	glPopMatrix();//7.1

	glPushMatrix();//7.2
	glRotatef(206, 0.0, 1.0, 0.0);
	glTranslatef(-3.92, 0, 2.7);
	glScalef(1.5, 1, 1);

	glPushMatrix();//2.1
	glScalef(0.5, 1, 2);//height,width,length
	glTranslatef(0, -0.5, 0);
	drawShRec(0.5);
	glPopMatrix();//2.1

	glPushMatrix();//2.2

	glRotatef(180, 0.0, 0.0, 1.0);
	glTranslatef(-1, 0, 1);
	glScalef(1, 1, 0.25);
	drawShTri(0.5);
	glPopMatrix();//2.2

	glPopMatrix();//7.2

	glPopMatrix();//6,7

	glPopMatrix();//shield all
}

void robotLeg() {
	glPushMatrix();//all
	glRotatef(30, 1.0, 0.0, 0.0);
	glTranslatef(0, 0, -0.5);
	glScalef(0.2, 0.2, 0.2);

	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glColor3f(0.20, 0.16, 0.17);
	drawSphere(0.5, 30.0, 30.0);
	glColor3f(0.07, 0.07, 0.06);
	glPopMatrix();

	glPushMatrix();//blok1
	glTranslatef(0.0, 0.0,0.4);

	glPushMatrix();//blok2 top face
	drawCircle(0.5);
	glPopMatrix();//blok2 top face

	drawCylinder(0.5,0.5,1.0);

	glPushMatrix();//blok 3 bottom face
	glTranslatef(0.0, 0.0, 1.0);
	drawCircle(0.5);
	glPopMatrix();;//blok 3 bottom face

	glPopMatrix();//blok1

	glPushMatrix();//bottom part connecter sphere
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0,0,2.24);
	glColor3f(0.20, 0.16, 0.17);
	drawSphere(0.5, 30.0, 30.0);
	glColor3f(0.07, 0.07, 0.06);
	glPopMatrix();//bottom part connecter sphere

	glPushMatrix();// small cylinder upper all
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(-1.8, 0.0, -0.45);
	glScalef(1, 1, 0.75);

	

	glPushMatrix();//small cylinder top face
	glColor3f(0.07, 0.07, 0.06);
	drawCircle(0.2);
	glPopMatrix();//small cylinder top face

	drawCylinder(0.2, 0.2, 1.2);

	glPushMatrix();//small cylinder bottom face
	glTranslatef(0.0, 0.0, 1.2);
	drawCircle(0.2);
	glColor3f(0.20, 0.16, 0.17);
	glPopMatrix();//small cylinder bottom face

	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();// small cylinder upper all

	glPushMatrix();// small cylinder upper all 2 small
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(-1.8, 0.0, -0.5);
	glScalef(0.5, 0.5, 0.85);

	glPushMatrix();//small cylinder top face
	glColor3f(0.06, 1.00, 0.98);//blue
	drawCircle(0.2);
	glPopMatrix();//small cylinder top face

	drawCylinder(0.2, 0.2, 1.2);

	glPushMatrix();//small cylinder bottom face
	glTranslatef(0.0, 0.0, 1.2);
	drawCircle(0.2);
	glColor3f(0.20, 0.16, 0.17);
	glPopMatrix();//small cylinder bottom face

	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();// small cylinder upper all 2 small

	glPushMatrix();//bottom part
	
	glTranslatef(0.0, 0.0, 2.24);
	glRotatef(60, 1.0, 0.0, 0.0);

	glPushMatrix();//big cylinder 2
	glTranslatef(0.0, -0.3, 0.2);

	glPushMatrix();//blok2
	glColor3f(0.07, 0.07, 0.06);
	drawCircle(0.25);
	glPopMatrix();//blok2

	drawCylinder(0.25, 0.25, 1.0);

	glPushMatrix();//blok 3 bottom face
	glTranslatef(0.0, 0.0, 1.0);
	drawCircle(0.25);
	glPopMatrix();;//blok 3 bottom face

	glPopMatrix();//big cylinder 2

	glPushMatrix();// small cylinder all
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(-1.2, -0.5, -0.65);

	glPushMatrix();//small rec back
	glColor3f(0.07, 0.07, 0.06);
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(-0.5, 0.04, -0.3);//
	glScalef(0.25,2.25,0.35);
	drawShSpecRec(0.5);
	
	glPopMatrix();//small rec back

	glPushMatrix();//small rec front 1
	glColor3f(0.41, 0.34, 0.21);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-10, 0.0, 0.0, 1.0);
	glTranslatef(0.25, 0.04, -0.3);//
	glScalef(0.15, 0.75, 0.75);

	drawShSpecRec(0.5);

	glPopMatrix();//small rec front 1

	glPushMatrix();//small rec front 2
	glColor3f(0.45, 0.41, 0.32);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(0.25, 0.39, -0.3);//
	glScalef(0.15, 0.75, 0.55);
	drawShSpecRec(0.5);

	glPopMatrix();//small rec front 2

	glPushMatrix();//small rec front 3
	glColor3f(0.41, 0.34, 0.21);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(10, 0.0, 0.0, 1.0);
	glTranslatef(0.45, 0.74, -0.3);//
	glScalef(0.15, 0.75, 0.75);
	drawShSpecRec(0.5);

	glPopMatrix();//small rec front 3

	glPushMatrix();//small cylinder top face
	glColor3f(0.20, 0.16, 0.17);
	drawCircle(0.2);
	glPopMatrix();//small cylinder top face

	drawCylinder(0.2, 0.2, 1.2);

	glPushMatrix();//small cylinder bottom face
	glTranslatef(0.0, 0.0, 1.2);
	drawCircle(0.2);
	glColor3f(1, 1, 1);
	glPopMatrix();//small cylinder bottom face

	//blue
	glPushMatrix();
	glScalef(0.5, 0.5, 1.2);
	glTranslatef(0.0, 0.0, -0.08);
	glPushMatrix();//small cylinder top face
	glColor3f(0.06, 1.00, 0.98);
	drawCircle(0.2);
	glPopMatrix();//small cylinder top face

	drawCylinder(0.2, 0.2, 1.2);

	glPushMatrix();//small cylinder bottom face
	glTranslatef(0.0, 0.0, 1.1);
	drawCircle(0.2);
	glColor3f(1, 1, 1);
	glPopMatrix();//small cylinder bottom face
	glPopMatrix();
	//blue

	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();// small cylinder all


	glPopMatrix();//bottom part

	glPopMatrix();//all
}

void completeLeg() {
	glPushMatrix();
	robotLeg();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.76, 0.74, 0.66);
	glScalef(0.6, 0.6, 0.6);
	glRotatef(125, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glTranslatef(-0.35, 0.8, -0.2);
	glRotatef(10, 0, 1, 0);
	shield();
	glPopMatrix();
}

void fourLeg() {
	glPushMatrix();//4 leg

	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	completeLeg();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	completeLeg();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	completeLeg();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	completeLeg();
	glPopMatrix();

	glPopMatrix();//4 leg
}

void robotHead() {
	
	

	glPushMatrix();//all
	glRotatef(90, 1.0, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glPushMatrix();//small cylinder top face
	glColor3f(0.45, 0.5, 0.4);
	drawCircle(0.25);

	glPushMatrix();//all small cirlce on head
	glScalef(0.75, 0.75, 1);
	glTranslatef(0, 0.07, 0);

	glPushMatrix();//rec
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -0.01, 0);
	glScalef(0.75, 1, 0.15);
	glTranslatef(-0.25, 0, 0.8);
	glBegin(GL_QUADS);
	glColor3f(0.06, 1.00, 0.98);
	glVertex3f(0,0,0);
	glVertex3f(0,0,0.25);
	glVertex3f(0.5, 0, 0.25);
	glVertex3f(0.5, 0, 0.0);
	glEnd();
	glPopMatrix();//rec

	glPushMatrix();//rec2
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -0.01, 0);
	glScalef(0.75, 1, 0.15);
	glTranslatef(-0.25, 0, 0.8);
	glRotatef(45, 0, 1, 1);
	glBegin(GL_QUADS);
	glColor3f(0.06, 1.00, 0.98);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.25);
	glVertex3f(0.5, 0, 0.25);
	glVertex3f(0.5, 0, 0.0);
	glEnd();
	glPopMatrix();//rec2

	glPushMatrix();//rec
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -0.01, 0);
	glScalef(0.075, 1, 1);
	glTranslatef(-0.25, 0, -0.28);
	glBegin(GL_QUADS);
	glColor3f(0.06, 1.00, 0.98);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.25);
	glVertex3f(0.5, 0, 0.25);
	glVertex3f(0.5, 0, 0.0);
	glEnd();
	glPopMatrix();//rec



	glPushMatrix();//top round
	glColor3f(0.06, 1.00, 0.98);
	//glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(0.15, -0.15, -0.005);
	//glRotatef(30, 0.0, 1.0, 0.0);
	drawCircle(0.05);
	glPopMatrix();

	glPushMatrix();//top round
	glColor3f(0.06, 1.00, 0.98);
	//glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(-0.15, -0.15, -0.005);
	//glRotatef(30, 0.0, 1.0, 0.0);
	drawCircle(0.05);
	glPopMatrix();

	glPushMatrix();//top round
	glColor3f(0.06, 1.00, 0.98);
	//glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(0, 0.05, -0.005);
	//glRotatef(30, 0.0, 1.0, 0.0);
	drawCircle(0.05);
	glPopMatrix();

	glPopMatrix();//all small cirlce on head

	glPopMatrix();//small cylinder top face
	glColor3f(0.55, 0.5, 0.4);
	drawCylinder(0.25, 0.25, 0.4);

	glPushMatrix();//small cylinder bottom face
	glTranslatef(0.0, 0.0, 0.4);
	glColor3f(0.45, 0.41, 0.32);
	drawCircle(0.25);

	glColor3f(0.06, 1.00, 0.98);
	

	glPopMatrix();//small cylinder bottom face

	glPushMatrix();//eye cylinder
	glColor3f(0.05, 0.32, 0.56);
	glTranslatef(0.0, 0.0, 0.12);
	drawCylinder(0.26, 0.26, 0.05);
	glPopMatrix();//eye cylinder

	glPushMatrix();//neck
	glColor3f(0.06, 1.00, 0.98);
	glTranslatef(0.0, 0.0, 0.45);
	drawGluCylinder(0.26, 0.26, 0.05);
	glPopMatrix();//neck

	glPushMatrix();//neck small
	glColor3f(0.06, 1.00, 0.98);
	glTranslatef(0.0, 0.0, 0.45);
	drawGluCylinder(0.2, 0.2, 0.05);
	glPopMatrix();//neck


	glPushMatrix();//eye1
	glColor3f(0.06, 1.00, 0.98);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(-0.1, -0.15, -0.25);
	glRotatef(30, 0.0, 1.0, 0.0);
	drawCircle(0.05);
	glPopMatrix();

	glPushMatrix();//eye2
	glColor3f(0.06, 1.00, 0.98);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(0.1, -0.15, -0.25);
	glRotatef(-30, 0.0, 1.0, 0.0);
	drawCircle(0.05);
	glPopMatrix();

	glPopMatrix();//all
}

void robotHeadwithEye() {
	robotHead();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	glRotatef(-90, 1.0, 0.0, 0.0);
	
	//glRotatef(0.05, 1.0, 1.0, 1.0);

	//fourLeg();

	robotHeadwithEye();



}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow
	(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------