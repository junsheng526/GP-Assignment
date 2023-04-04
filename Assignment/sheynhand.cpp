#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <Math.h>

#pragma comment(lib, "GLU32.lib")			//can use this comment or set properties
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Ass Demo"

int qNo;
float tx = 0, ty = 0, tz = 0, tSpeed = 1.0;
float ptx = 0.0, pty = 0.0, ptSpeed = 0.5;
float pry = 0.0, prSpeed = 1.0;
bool isOrtho = true;
float oNear = -10.0, oFar = 10.0;
float pNear = 1.0, pFar = 21.0;
float rs1 = 3.0;
float angle = 0;		//angle of circle
float PI = 3.1429;
float noOfTri = 36;		//no of triangle

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x31)		//where press '1'
			qNo = 1;
		else if (wParam == 0x32)		//where press '2'
			qNo = 2;
		else if (wParam == VK_LEFT)		//where press left
			tx -= tSpeed;
		else if (wParam == VK_RIGHT)
			tx += tSpeed;
		else if (wParam == VK_UP) {
			if (isOrtho) {
				if (tz > oNear)
					tz -= tSpeed;
			}
			else {
				if (tz > (pNear + rs1))
					tz -= tSpeed;
			}
		}
		else if (wParam == VK_DOWN) {
			if (isOrtho) {
				if (tz < oFar)
					tz += tSpeed;
			}
			else {
				if (tz < (pFar - rs1) / 2)
					tz += tSpeed;
			}
		}
		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {
			isOrtho = false;
			tz = pNear + 3.0;
		}
		else if (wParam == 'A')
			ptx -= ptSpeed;
		else if (wParam == 'D')
			ptx += ptSpeed;
		else if (wParam == 'W')
			pty += ptSpeed;
		else if (wParam == 'S')
			pty -= ptSpeed;
		else if (wParam == 'L')
			pry += prSpeed;
		else if (wParam == 'R')
			pry -= prSpeed;
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

void projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			//reset matrix

	glTranslatef(ptx, pty, 0.0);	//only translate projection for tx,ty
	glRotatef(pry, 0.0, 1.0, 0.0);	//only rotate projection for ry

	if (isOrtho) {
		glOrtho(-10.0, 10.0, -10.0, 10.0, oNear, oFar);
	}
	else {
		gluPerspective(20, 1.0, -1.0, 1.0);
		glFrustum(-10.0, 10.0, -10.0, 10.0, pNear, pFar);
	}

}

void drawPyramid(float size)
{
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.0, 0.0, size);
	glVertex3f(size, 0.0, size);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0.0, 0.0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawSphere2D(float rd)
{
	float x = 0, y = 0;		//origin of circle (x,y) (0,0)
	float x2 = 0, y2 = 0;	//point on circle (x2,y2)
	float x3 = 0, y3 = 0;	//point on circle (x3,y3)

	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x, y);	//origin of circle

	//rd = radius of circle
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri) {
		x2 = x + rd * cos(angle);
		y2 = y + rd * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawSphere(float rs1)
{
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	//gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, rs1, 30, 30);
	gluDeleteQuadric(sphere);
}

void drawCylinder(float br, float tr, float h)
{
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	//gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, br, tr, h, 30, 10);
	gluDeleteQuadric(cylinder);
}

void drawFullCylinder(float br, float tr, float h, float rd, float tfc)
{
	drawCylinder(br, tr, h);
	drawSphere2D(rd);
	glTranslatef(0.0, 0.0, tfc);
	drawSphere2D(rd);
}

void drawWeapon()
{
	glColor3f(0.4, 0.4, 0.4);
	//left1 
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 1.3, 0.0);	//B
	glVertex3f(0.0, 1.3, 0.3);	//H
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(0.0, 1.3, 0.0);	//B
	glVertex3f(-1.5, 0.8, 0.0);	//C
	glVertex3f(-1.5, 0.8, 0.3);	//I
	glVertex3f(0.0, 1.3, 0.3);	//H
	glVertex3f(0.0, 1.3, 0.0);	//B

	glVertex3f(-1.5, 0.8, 0.0);	//C
	glVertex3f(-1.5, 0.6, 0.0);	//D
	glVertex3f(-1.5, 0.6, 0.3);	//J
	glVertex3f(-1.5, 0.8, 0.3);	//I
	glVertex3f(-1.5, 0.8, 0.0);	//C

	glVertex3f(-1.5, 0.6, 0.0);	//D
	glVertex3f(-1.7, 0.5, 0.0);	//E
	glVertex3f(-1.7, 0.5, 0.3);	//K
	glVertex3f(-1.5, 0.6, 0.3);	//J
	glVertex3f(-1.5, 0.6, 0.0);	//D

	glVertex3f(-1.7, 0.5, 0.0);	//E
	glVertex3f(-1.5, 0.0, 0.0);	//F	
	glVertex3f(-1.5, 0.0, 0.3);	//L
	glVertex3f(-1.7, 0.5, 0.3);	//K
	glVertex3f(-1.7, 0.5, 0.0);	//E

	glVertex3f(-1.5, 0.0, 0.0);	//F	
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(-1.5, 0.0, 0.3);	//L
	glVertex3f(-1.5, 0.0, 0.0);	//F	

	//back to A
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//left2
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 2.2, 0.0);	//E1
	glVertex3f(0.0, 2.2, 0.3);	//I1
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(0.0, 2.2, 0.0);	//E1
	glVertex3f(-0.4, 2.5, 0);	//B1
	glVertex3f(-0.4, 2.5, 0.3);	//F1
	glVertex3f(0.0, 2.2, 0.3);	//I1
	glVertex3f(0.0, 2.2, 0.0);	//E1

	glVertex3f(-0.4, 2.5, 0);	//B1
	glVertex3f(-1.0, 1.8, 0.0);	//C1
	glVertex3f(-1.0, 1.8, 0.3);	//G1
	glVertex3f(-0.4, 2.5, 0.3);	//F1
	glVertex3f(-0.4, 2.5, 0);	//B1

	glVertex3f(-1.0, 1.8, 0.0);	//C1
	glVertex3f(-1.0, 0.0, 0.0);	//D1
	glVertex3f(-1.0, 0.0, 0.3);	//H1
	glVertex3f(-1.0, 1.8, 0.3);	//G1
	glVertex3f(-1.0, 1.8, 0.0);	//C1

	glVertex3f(-1.0, 0.0, 0.0);	//D1
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(-1.0, 0.0, 0.3);	//H1
	glVertex3f(-1.0, 0.0, 0.0);	//D1

	//back to A
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//back(middle)
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 3.0, 0.3);	//G2
	glVertex3f(0.0, 3.5, 0.3);	//F2
	glVertex3f(0.0, 3.5, 0.0);	//A2

	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(-0.7, 0.0, 0.3);	//H2
	glVertex3f(-0.7, 3.0, 0.3);	//G2
	glVertex3f(-0.7, 3.0, 0.0);	//B2

	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(-0.7, 0.0, 0.3);	//H2
	glVertex3f(-0.7, 0.0, 0.0);	//C2

	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.7, 2.8, 0.3);	//J2
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(0.7, 0.0, 0.0);	//D2

	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(0.0, 3.5, 0.3);	//F2
	glVertex3f(0.7, 2.8, 0.3);	//J2
	glVertex3f(0.7, 2.8, 0.0);	//E2

	//back to A2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glEnd();

	//right1
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.5, 1.0, 0.0);	//A3
	glVertex3f(0.5, 1.0, 0.3);	//B3
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(0.7, 0.0, 0.0);	//D2

	glVertex3f(0.5, 1.0, 0.0);	//A3
	glVertex3f(0.0, 1.3, 0.0);	//B
	glVertex3f(0.0, 1.3, 0.3);	//H
	glVertex3f(0.5, 1.0, 0.3);	//B3
	glVertex3f(0.5, 1.0, 0.0);	//A3

	//back to A
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//right2
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(1.2, 0.0, 0.0);	//A4
	glVertex3f(1.2, 0.0, 0.3);	//E4
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(1.2, 0.0, 0.0);	//A4
	glVertex3f(1.2, 0.8, 0.0);	//B4
	glVertex3f(1.2, 0.8, 0.3);	//F4
	glVertex3f(1.2, 0.0, 0.3);	//E4
	glVertex3f(1.2, 0.0, 0.0);	//A4

	glVertex3f(1.2, 0.8, 0.0);	//B4
	glVertex3f(0.7, 1.7, 0.0);	//C4
	glVertex3f(0.7, 1.7, 0.3);	//G4
	glVertex3f(1.2, 0.8, 0.3);	//F4
	glVertex3f(1.2, 0.8, 0.0);	//B4

	glVertex3f(0.7, 1.7, 0.0);	//C4
	glVertex3f(0.0, 1.7, 0.0);	//D4
	glVertex3f(0.0, 1.7, 0.3);	//H4
	glVertex3f(0.7, 1.7, 0.3);	//G4
	glVertex3f(0.7, 1.7, 0.0);	//C4

	//back to A
	glVertex3f(1.2, 0.8, 0.0);	//B4
	glVertex3f(1.2, 0.0, 0.0);	//A4
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//right3
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(1.0, 0.0, 0.0);	//A5
	glVertex3f(1.0, 0.0, 0.3);	//D5
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(1.0, 0.0, 0.0);	//A5
	glVertex3f(1.0, 1.5, 0.0);	//B5
	glVertex3f(1.0, 1.5, 0.3);	//E5
	glVertex3f(1.0, 0.0, 0.3);	//D5
	glVertex3f(1.0, 0.0, 0.0);	//A5

	glVertex3f(1.0, 1.5, 0.0);	//B5
	glVertex3f(0.9, 2.2, 0.0);	//C5
	glVertex3f(0.9, 2.2, 0.3);	//F5
	glVertex3f(1.0, 1.5, 0.3);	//E5
	glVertex3f(1.0, 1.5, 0.0);	//B5

	glVertex3f(0.9, 2.2, 0.0);	//C5
	glVertex3f(0.0, 2.2, 0.0);	//E1
	glVertex3f(0.0, 2.2, 0.3);	//I1
	glVertex3f(0.9, 2.2, 0.3);	//F5
	glVertex3f(0.9, 2.2, 0.0);	//C5

	//back to A
	glVertex3f(1.0, 1.5, 0.0);	//B5
	glVertex3f(1.0, 0.0, 0.0);	//A5
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();
}

void drawWeaponLine()
{
	glColor3f(0.0, 1.0, 1.0);
	//left1 
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 1.3, 0.0);	//B
	glVertex3f(0.0, 1.3, 0.3);	//H
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(0.0, 1.3, 0.0);	//B
	glVertex3f(-1.5, 0.8, 0.0);	//C
	glVertex3f(-1.5, 0.8, 0.3);	//I
	glVertex3f(0.0, 1.3, 0.3);	//H
	glVertex3f(0.0, 1.3, 0.0);	//B

	glVertex3f(-1.5, 0.8, 0.0);	//C
	glVertex3f(-1.5, 0.6, 0.0);	//D
	glVertex3f(-1.5, 0.6, 0.3);	//J
	glVertex3f(-1.5, 0.8, 0.3);	//I
	glVertex3f(-1.5, 0.8, 0.0);	//C

	glVertex3f(-1.5, 0.6, 0.0);	//D
	glVertex3f(-1.7, 0.5, 0.0);	//E
	glVertex3f(-1.7, 0.5, 0.3);	//K
	glVertex3f(-1.5, 0.6, 0.3);	//J
	glVertex3f(-1.5, 0.6, 0.0);	//D

	glVertex3f(-1.7, 0.5, 0.0);	//E
	glVertex3f(-1.5, 0.0, 0.0);	//F	
	glVertex3f(-1.5, 0.0, 0.3);	//L
	glVertex3f(-1.7, 0.5, 0.3);	//K
	glVertex3f(-1.7, 0.5, 0.0);	//E

	glVertex3f(-1.5, 0.0, 0.0);	//F	
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(-1.5, 0.0, 0.3);	//L
	glVertex3f(-1.5, 0.0, 0.0);	//F	

	//back to A
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//left2
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 2.2, 0.0);	//E1
	glVertex3f(0.0, 2.2, 0.3);	//I1
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(0.0, 2.2, 0.0);	//E1
	glVertex3f(-0.4, 2.5, 0);	//B1
	glVertex3f(-0.4, 2.5, 0.3);	//F1
	glVertex3f(0.0, 2.2, 0.3);	//I1
	glVertex3f(0.0, 2.2, 0.0);	//E1

	glVertex3f(-0.4, 2.5, 0);	//B1
	glVertex3f(-1.0, 1.8, 0.0);	//C1
	glVertex3f(-1.0, 1.8, 0.3);	//G1
	glVertex3f(-0.4, 2.5, 0.3);	//F1
	glVertex3f(-0.4, 2.5, 0);	//B1

	glVertex3f(-1.0, 1.8, 0.0);	//C1
	glVertex3f(-1.0, 0.0, 0.0);	//D1
	glVertex3f(-1.0, 0.0, 0.3);	//H1
	glVertex3f(-1.0, 1.8, 0.3);	//G1
	glVertex3f(-1.0, 1.8, 0.0);	//C1

	glVertex3f(-1.0, 0.0, 0.0);	//D1
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(-1.0, 0.0, 0.3);	//H1
	glVertex3f(-1.0, 0.0, 0.0);	//D1

	//back to A
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//back(middle)
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 3.0, 0.3);	//G2
	glVertex3f(0.0, 3.5, 0.3);	//F2
	glVertex3f(0.0, 3.5, 0.0);	//A2

	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(-0.7, 0.0, 0.3);	//H2
	glVertex3f(-0.7, 3.0, 0.3);	//G2
	glVertex3f(-0.7, 3.0, 0.0);	//B2

	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(-0.7, 0.0, 0.3);	//H2
	glVertex3f(-0.7, 0.0, 0.0);	//C2

	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.7, 2.8, 0.3);	//J2
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(0.7, 0.0, 0.0);	//D2

	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(0.0, 3.5, 0.3);	//F2
	glVertex3f(0.7, 2.8, 0.3);	//J2
	glVertex3f(0.7, 2.8, 0.0);	//E2

	//back to A2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glEnd();

	//right1
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.5, 1.0, 0.0);	//A3
	glVertex3f(0.5, 1.0, 0.3);	//B3
	glVertex3f(0.7, 0.0, 0.3);	//I2
	glVertex3f(0.7, 0.0, 0.0);	//D2

	glVertex3f(0.5, 1.0, 0.0);	//A3
	glVertex3f(0.0, 1.3, 0.0);	//B
	glVertex3f(0.0, 1.3, 0.3);	//H
	glVertex3f(0.5, 1.0, 0.3);	//B3
	glVertex3f(0.5, 1.0, 0.0);	//A3

	//back to A
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//right2
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(1.2, 0.0, 0.0);	//A4
	glVertex3f(1.2, 0.0, 0.3);	//E4
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(1.2, 0.0, 0.0);	//A4
	glVertex3f(1.2, 0.8, 0.0);	//B4
	glVertex3f(1.2, 0.8, 0.3);	//F4
	glVertex3f(1.2, 0.0, 0.3);	//E4
	glVertex3f(1.2, 0.0, 0.0);	//A4

	glVertex3f(1.2, 0.8, 0.0);	//B4
	glVertex3f(0.7, 1.7, 0.0);	//C4
	glVertex3f(0.7, 1.7, 0.3);	//G4
	glVertex3f(1.2, 0.8, 0.3);	//F4
	glVertex3f(1.2, 0.8, 0.0);	//B4

	glVertex3f(0.7, 1.7, 0.0);	//C4
	glVertex3f(0.0, 1.7, 0.0);	//D4
	glVertex3f(0.0, 1.7, 0.3);	//H4
	glVertex3f(0.7, 1.7, 0.3);	//G4
	glVertex3f(0.7, 1.7, 0.0);	//C4

	//back to A
	glVertex3f(1.2, 0.8, 0.0);	//B4
	glVertex3f(1.2, 0.0, 0.0);	//A4
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();

	//right3
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);	//A
	glVertex3f(1.0, 0.0, 0.0);	//A5
	glVertex3f(1.0, 0.0, 0.3);	//D5
	glVertex3f(0.0, 0.0, 0.3);	//G
	glVertex3f(0.0, 0.0, 0.0);	//A

	glVertex3f(1.0, 0.0, 0.0);	//A5
	glVertex3f(1.0, 1.5, 0.0);	//B5
	glVertex3f(1.0, 1.5, 0.3);	//E5
	glVertex3f(1.0, 0.0, 0.3);	//D5
	glVertex3f(1.0, 0.0, 0.0);	//A5

	glVertex3f(1.0, 1.5, 0.0);	//B5
	glVertex3f(0.9, 2.2, 0.0);	//C5
	glVertex3f(0.9, 2.2, 0.3);	//F5
	glVertex3f(1.0, 1.5, 0.3);	//E5
	glVertex3f(1.0, 1.5, 0.0);	//B5

	glVertex3f(0.9, 2.2, 0.0);	//C5
	glVertex3f(0.0, 2.2, 0.0);	//E1
	glVertex3f(0.0, 2.2, 0.3);	//I1
	glVertex3f(0.9, 2.2, 0.3);	//F5
	glVertex3f(0.9, 2.2, 0.0);	//C5

	//back to A
	glVertex3f(1.0, 1.5, 0.0);	//B5
	glVertex3f(1.0, 0.0, 0.0);	//A5
	glVertex3f(0.0, 0.0, 0.0);	//A
	glEnd();
}

void showWeapon()
{
	glScalef(2.5, 2.5, 2.5);	//scale weapon

	glLineWidth(2.0);			//draw line
	drawWeaponLine();
	drawWeapon();				//draw weapon

	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(0.0, 0.5, 0.31);	//move out big circle
	drawSphere2D(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0.0, 0.5, 0.32);	//move out small circle
	drawSphere2D(0.2);
	glPopMatrix();
}

void drawPolygon(float size1, float size2, float size3, float size4)
{
	//Polygon size1 = 1.5 size2 = -0.5 size3 = 1.5 size4 = 1.0
	//hand size1 = 3.0 size2 = 0.0 size3 = 0.5 size4 = 1.0

	glBegin(GL_POLYGON);
	//glColor3f(1.0, 0.4, 0.4);

	//front
	glVertex3f(0.0, 0.0, 0.0);		//A
	glVertex3f(0.0, 0.0, size3);		//A1
	glVertex3f(0.0, size1, size3);	//B1
	glVertex3f(0.0, size1, 0.0);	//B
	glVertex3f(0.0, 0.0, 0.0);		//A

	glVertex3f(size4, size2, 0.0);	//C
	glVertex3f(size4, size2, size3);	//C1
	glVertex3f(0.0, 0.0, size3);		//A1
	glVertex3f(0.0, 0.0, 0.0);		//A

	glVertex3f(size4, size2, 0.0);	//C
	glVertex3f(size4, size1, 0.0);		//D
	glVertex3f(size4, size1, size3);		//D1
	glVertex3f(size4, size2, size3);	//C1
	glVertex3f(size4, size2, 0.0);	//C

	glVertex3f(size4, size1, 0.0);		//D
	glVertex3f(0.0, size1, 0.0);	//B
	glVertex3f(0.0, size1, size3);	//B1
	glVertex3f(size4, size1, size3);		//D1
	glVertex3f(size4, size1, 0.0);		//D

	//back to A
	glVertex3f(0.0, size1, 0.0);	//B
	glVertex3f(0.0, 0.0, 0.0);		//A
	glEnd();
}

void drawHand()
{
	glColor3f(1.0, 0.8, 0.5);

	glPushMatrix();
	glRotatef(-90, 0.0, 1.0, 0.3);		//rotate hand

	glPushMatrix();
	drawFullCylinder(3.0, 3.0, 0.5, 3.0, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 2.5, 0.0);
	drawPolygon(3.0, 0.0, 0.5, 1.0);
	glPopMatrix();

	glPopMatrix();
}

void drawRightArm()
{
	//shoulder polygon
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glScalef(0.5, 0.5, -0.5);
	glTranslatef(1.0, 5.2, 0.0);
	drawPolygon(1.5, -0.5, 1.5, 1.0);
	glPopMatrix();

	//adjust arm position without Polygon
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.3);

	//joint1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(0.1, 3.0, 0.0);
	drawSphere(0.45);
	glPopMatrix();

	//upper arm
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0.0, 2.8, 0.0);
	glRotatef(120, 1.0, -0.3, 0.0);
	drawFullCylinder(0.5, 0.5, 2.0, 0.5, 2.0);
	glPopMatrix();

	//joint2
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-0.6, 0.9, -1.0);
	drawSphere(0.4);
	glPopMatrix();

	//lower arm
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0.0, 0.0, -1.4);
	glRotatef(-90, 0.0, 1.0, 0.3);
	drawFullCylinder(0.6, 0.6, 1.5, 0.6, 1.5);
	glPopMatrix();

	//cylinder joint1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-0.7, -0.7, -1.4);
	glRotatef(-90, 0.0, 1.0, 0.3);
	drawFullCylinder(0.3, 0.3, 1.0, 0.3, 1.0);
	glPopMatrix();

	//cylinder joint2
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(-1.5, -0.8, -1.4);
	glRotatef(90, 1.0, -0.3, 0.0);
	drawFullCylinder(0.3, 0.3, 0.5, 0.3, 0.5);
	glPopMatrix();

	glPopMatrix();
}

void drawLeftArm()
{
	//shoulder polygon
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glScalef(0.5, 0.5, -0.5);
	glTranslatef(1.0, 5.2, 0.0);
	drawPolygon(1.5, -0.5, 1.5, 1.0);
	glPopMatrix();

	//adjust arm position without Polygon
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.3);

	//joint1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(0.1, 3.0, 0.0);
	drawSphere(0.45);
	glPopMatrix();

	//upper arm
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0.0, 2.8, 0.0);
	glRotatef(60, 1.0, -0.3, 0.0);
	drawFullCylinder(0.5, 0.5, 2.0, 0.5, 2.0);
	glPopMatrix();

	//joint2
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-0.6, 0.9, 1.2);
	drawSphere(0.4);
	glPopMatrix();

	//lower arm
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0.0, 0.0, 1.6);
	glRotatef(-90, 0.0, 1.0, 0.3);
	drawFullCylinder(0.6, 0.6, 1.5, 0.6, 1.5);
	glPopMatrix();

	//cylinder joint1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-0.7, -0.7, 1.8);
	glRotatef(-90, 0.0, 1.0, 0.3);
	drawFullCylinder(0.3, 0.3, 1.0, 0.3, 1.0);
	glPopMatrix();

	//cylinder joint2
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(-1.5, -0.7, 2.0);
	glRotatef(60, 1.0, -0.3, 0.0);
	drawFullCylinder(0.3, 0.3, 0.5, 0.3, 0.5);
	glPopMatrix();

	glPopMatrix();
}

void drawRight()
{
	drawRightArm();
	//draw right hand
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glTranslatef(-3.5, 1.0, -4.0);
	drawHand();
	glPopMatrix();
}

void drawLeft()
{
	//draw and rotate arm
	glPushMatrix();
	glRotatef(-180, 0.0, 10.0, 0.0);
	drawLeftArm();

	glPushMatrix();
	glScalef(0.6, 0.6, 0.6);
	glTranslatef(-2.0, 1.7, 2.0);
	glRotatef(-35, 10.0, 0.0, 0.0);
	drawHand();
	glPopMatrix();

	glPopMatrix();
}

void drawBothArm()
{
	//right 
	glPushMatrix();
	glTranslatef(-3.0, 0.0, 0.0);
	drawRight();
	glPopMatrix();

	//left 
	glPushMatrix();
	glTranslatef(3.0, 0.0, 0.0);
	drawLeft();
	glPopMatrix();
}

void drawBothWeapon()
{
	//right weapon (left)
	glPushMatrix();
	glTranslatef(-5.1, -1.7, 1.5);	//glTranslatef(-4.9, -0.65, -2.0);
	glRotatef(-91, 0.0, 1.0, 0.3);
	showWeapon();
	glPopMatrix();

	//left weapon (right)
	glPushMatrix();
	glTranslatef(4.85, -1.7, 1.4);		//glTranslatef(5.1, -0.65, -2.0);
	glRotatef(-180, 0.0, 10.0, 0.0);	//rotate whole weapon
	glRotatef(-35, 10.0, 0.0, 0.0);		//rotate same side wif hand
	glRotatef(-90, 0.0, 1.0, 0.3);		//rotate same slope wif hand
	showWeapon();
	glPopMatrix();
}

void drawFinger()
{
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 3.0, 0.6);	//G2
	glVertex3f(0.0, 3.5, 0.6);	//F2
	glVertex3f(0.0, 3.5, 0.0);	//A2

	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(-0.7, 0.0, 0.6);	//H2
	glVertex3f(-0.7, 3.0, 0.6);	//G2
	glVertex3f(-0.7, 3.0, 0.0);	//B2

	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 0.0, 0.6);	//I2
	glVertex3f(-0.7, 0.0, 0.6);	//H2
	glVertex3f(-0.7, 0.0, 0.0);	//C2

	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.7, 2.8, 0.6);	//J2
	glVertex3f(0.7, 0.0, 0.6);	//I2
	glVertex3f(0.7, 0.0, 0.0);	//D2

	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(0.0, 3.5, 0.6);	//F2
	glVertex3f(0.7, 2.8, 0.6);	//J2
	glVertex3f(0.7, 2.8, 0.0);	//E2

	//back to A2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glEnd();
}

void drawFingerLine()
{
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);

	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 3.0, 0.6);	//G2
	glVertex3f(0.0, 3.5, 0.6);	//F2
	glVertex3f(0.0, 3.5, 0.0);	//A2

	glVertex3f(-0.7, 3.0, 0.0);	//B2
	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(-0.7, 0.0, 0.6);	//H2
	glVertex3f(-0.7, 3.0, 0.6);	//G2
	glVertex3f(-0.7, 3.0, 0.0);	//B2

	glVertex3f(-0.7, 0.0, 0.0);	//C2
	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 0.0, 0.6);	//I2
	glVertex3f(-0.7, 0.0, 0.6);	//H2
	glVertex3f(-0.7, 0.0, 0.0);	//C2

	glVertex3f(0.7, 0.0, 0.0);	//D2
	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.7, 2.8, 0.6);	//J2
	glVertex3f(0.7, 0.0, 0.6);	//I2
	glVertex3f(0.7, 0.0, 0.0);	//D2

	glVertex3f(0.7, 2.8, 0.0);	//E2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glVertex3f(0.0, 3.5, 0.6);	//F2
	glVertex3f(0.7, 2.8, 0.6);	//J2
	glVertex3f(0.7, 2.8, 0.0);	//E2

	//back to A2
	glVertex3f(0.0, 3.5, 0.0);	//A2
	glEnd();
}

void drawThreeFinger()
{
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(2.0);

	//leftfinger
	glPushMatrix();
	glTranslatef(-1.15, 0.0, 0.8);
	glRotatef(-180, 0.0, 10.0, 0.0);
	drawFingerLine();
	drawFinger();
	glPopMatrix();

	//middle finger
	glPushMatrix();
	glTranslatef(-0.3, 0.0, 0.0);
	drawPolygon(2.0, 0.0, 0.5, 1.0);
	glPopMatrix();

	//right finger
	glPushMatrix();
	glTranslatef(1.5, 0.0, 0.0);
	drawFingerLine();
	drawFinger();
	glPopMatrix();
}

void drawRightHand()
{
	//draw finger on hand
	glPushMatrix();
	glTranslatef(-5.6, -0.5, -2.0);
	glRotatef(-90, 0.0, 1.0, 0.3);
	drawThreeFinger();
	glPopMatrix();

	//joint finger1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-5.75, -0.8, -1.4);
	drawSphere(0.2);
	glPopMatrix();

	//joint finger2
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-5.9, -0.7, -1.9);
	drawSphere(0.2);
	glPopMatrix();

	//joint finger3
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-5.9, -0.5, -2.5);
	drawSphere(0.2);
	glPopMatrix();

	//support right
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(-5.7, -0.5, -1.4);
	glRotatef(90, 0.3, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawPolygon(1.3, 0.0, 0.5, 1.0);
	glPopMatrix();
}

void drawLeftHand()
{
	glRotatef(-180, 0.0, 10.0, 0.0);
	glRotatef(-35, 10.0, 0.0, 0.0);
	//draw finger on hand
	glPushMatrix();
	glTranslatef(-5.8, -1.5, 1.3);
	glRotatef(-90, 0.0, 1.0, 0.3);
	drawThreeFinger();
	glPopMatrix();

	//joint finger1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-6.0, -1.8, 1.9);
	drawSphere(0.2);
	glPopMatrix();

	//joint finger2
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-6.0, -1.7, 1.4);
	drawSphere(0.2);
	glPopMatrix();

	//joint finger3
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(-6.0, -1.5, 0.9);
	drawSphere(0.2);
	glPopMatrix();

	//support left
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(-5.9, -1.5, 1.8);
	glRotatef(90, 0.3, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawPolygon(1.3, 0.0, 0.5, 1.0);
	glPopMatrix();
}

void showHand()
{
	drawBothArm();
	drawRightHand();
	drawLeftHand();
}

void showWH()
{
	showHand();
	drawBothWeapon();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);		//if no, transparent

	projection();
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(tx, ty, tz);
	showWH();

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

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
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