#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#define WINDOW_TITLE "Robot Body"

float x = 0.0, y = 0.0, z = 0.0;

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
		else if (wParam == 'X') {
			x = 0.05;
		}
		else if (wParam == 'Y') {
			y = 0.05;
		}
		else if (wParam == 'Z') {
			z = 0.05;
		}
		else if (wParam == 'S') {
			x = 0.0;
			y = 0.0;
			z = 0.0;
			glLoadIdentity();
		}
		else if (wParam == 'P') {
			x = 0.0;
			y = 0.0;
			z = 0.0;
		}
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
void drawShoulder()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);

	glVertex3f(0.3f, 0.3f, 0.0f);
	glVertex3f(0.3f, 0.4f, 0.6f);
	glVertex3f(0.3f, -0.4f, 0.6f);
	glVertex3f(0.3f, -0.3f, 0.0f);

	glVertex3f(0.3f, -0.3f, 0.0f);
	glVertex3f(-0.3f, -0.3f, 0.0f);
	glVertex3f(-0.3f, -0.4f, 0.6f);
	glVertex3f(0.3f, -0.4f, 0.6f);

	glVertex3f(0.3f, -0.4f, 0.6f);
	glVertex3f(-0.3f, -0.4f, 0.6f);
	glVertex3f(-0.3f, 0.4f, 0.6f);
	glVertex3f(0.3f, 0.4f, 0.6f);

	glVertex3f(0.3f, 0.4f, 0.6f);
	glVertex3f(-0.3f, 0.4f, 0.6f);
	glVertex3f(-0.3f, 0.3f, 0.0f);
	glVertex3f(0.3f, 0.3f, 0.0f);

	glVertex3f(0.3f, 0.3f, 0.0f);
	glVertex3f(0.3f, -0.3f, 0.0f);
	glVertex3f(-0.3f, -0.3f, 0.0f);
	glVertex3f(-0.3f, 0.3f, 0.0f);

	glVertex3f(-0.3f, 0.3f, 0.0f);
	glVertex3f(-0.3f, -0.3f, 0.0f);
	glVertex3f(-0.3f, -0.4f, 0.6f);
	glVertex3f(-0.3f, 0.4f, 0.6f);

	glEnd();
}

void drawNeck()
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);

	glVertex3f(0.3f, -0.9f, 0.6f);
	glVertex3f(0.3f, 0.9f, 0.6f);
	glVertex3f(0.3f, 0.5f, 0.0f);
	glVertex3f(0.3f, -0.5f, 0.0f);

	glVertex3f(0.3f, -0.5f, 0.0f);
	glVertex3f(-0.3f, -0.5f, 0.0f);
	glVertex3f(-0.3f, -0.9f, 0.6f);
	glVertex3f(0.3f, -0.9f, 0.6f);

	glVertex3f(0.3f, -0.9f, 0.6f);
	glVertex3f(-0.3f, -0.9f, 0.6f);
	glVertex3f(-0.3f, 0.9f, 0.6f);
	glVertex3f(0.3f, 0.9f, 0.6f);

	glVertex3f(0.3f, 0.9f, 0.6f);
	glVertex3f(-0.3f, 0.9f, 0.6f);
	glVertex3f(-0.3f, 0.5f, 0.0f);
	glVertex3f(0.3f, 0.5f, 0.0f);

	glVertex3f(0.3f, 0.5f, 0.0f);
	glVertex3f(0.3f, -0.5f, 0.0f);
	glVertex3f(-0.3f, -0.5f, 0.0f);
	glVertex3f(-0.3f, 0.5f, 0.0f);

	glVertex3f(-0.3f, 0.5f, 0.0f);
	glVertex3f(-0.3f, -0.5f, 0.0f);
	glVertex3f(-0.3f, -0.9f, 0.6f);
	glVertex3f(-0.3f, 0.9f, 0.6f);

	glEnd();
}

void drawFrontPlateLeft()
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);

	glVertex3f(-0.1f, 0.7f, 0.8f);
	glVertex3f(-0.1f, 0.0f, 0.6f);
	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.7f, 0.2f);

	glVertex3f(-0.1f, 0.7f, 0.2f);
	glVertex3f(0.1f, 0.7f, 0.2f);
	glVertex3f(0.1f, 0.7f, 0.8f);
	glVertex3f(-0.1f, 0.7f, 0.8f);

	glVertex3f(-0.1f, 0.7f, 0.8f);
	glVertex3f(0.1f, 0.7f, 0.8f);
	glVertex3f(0.1f, 0.0f, 0.6f);
	glVertex3f(-0.1f, 0.0f, 0.6f);

	glVertex3f(-0.1f, 0.0f, 0.6f);
	glVertex3f(0.1f, 0.0f, 0.6f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.0f, 0.0f);

	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.7f, 0.2f);
	glVertex3f(0.1f, 0.7f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.0f);

	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.7f, 0.2f);
	glVertex3f(0.1f, 0.7f, 0.8f);
	glVertex3f(0.1f, 0.0f, 0.6f);

	glEnd();
}

void drawFrontPlateRight()
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);

	glVertex3f(-0.1f, 0.0f, 0.6f);
	glVertex3f(-0.1f, -0.7f, 0.8f);
	glVertex3f(-0.1f, -0.7f, 0.2f);
	glVertex3f(-0.1f, 0.0f, 0.0f);

	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.6f);
	glVertex3f(-0.1f, 0.0f, 0.6f);

	glVertex3f(-0.1f, 0.0f, 0.6f);
	glVertex3f(0.1f, 0.0f, 0.6f);
	glVertex3f(0.1f, -0.7f, 0.8f);
	glVertex3f(-0.1f, -0.7f, 0.8f);

	glVertex3f(-0.1f, -0.7f, 0.8f);
	glVertex3f(0.1f, -0.7f, 0.8f);
	glVertex3f(0.1f, -0.7f, 0.2f);
	glVertex3f(-0.1f, -0.7f, 0.2f);

	glVertex3f(-0.1f, -0.7f, 0.2f);
	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, -0.7f, 0.2f);

	glVertex3f(0.1f, -0.7f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.6f);
	glVertex3f(0.1f, -0.7f, 0.8f);

	glEnd();
}

void drawChest()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(-0.8f, -0.3f, 0.8f);
	glVertex3f(0.8f, -0.3f, 0.8f);
	glVertex3f(0.9f, -0.3f, 0.6f);
	glVertex3f(-0.9f, -0.3f, 0.6f);

	glVertex3f(-0.9f, -0.3f, 0.6f);
	glVertex3f(-0.9f, 0.3f, 0.6f);
	glVertex3f(-0.8f, 0.3f, 0.8f);
	glVertex3f(-0.8f, -0.3f, 0.8f);

	glVertex3f(-0.8f, -0.3f, 0.8f);
	glVertex3f(-0.8f, 0.3f, 0.8f);
	glVertex3f(0.8f, 0.3f, 0.8f);
	glVertex3f(0.8f, -0.3f, 0.8f);

	glVertex3f(0.8f, -0.3f, 0.8f);
	glVertex3f(0.8f, 0.3f, 0.8f);
	glVertex3f(0.9f, 0.3f, 0.6f);
	glVertex3f(0.9f, -0.3f, 0.6f);

	glVertex3f(0.9f, -0.3f, 0.6f);
	glVertex3f(-0.9f, -0.3f, 0.6f);
	glVertex3f(-0.9f, 0.3, 0.6f);
	glVertex3f(0.9f, 0.3f, 0.6f);

	glVertex3f(0.9f, 0.3f, 0.6f);
	glVertex3f(-0.9f, 0.3f, 0.6f);
	glVertex3f(-0.8f, 0.3f, 0.8f);
	glVertex3f(0.8f, 0.3f, 0.8f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(-0.9f, -0.3f, 0.6f);
	glVertex3f(0.9f, -0.3f, 0.6f);
	glVertex3f(0.9f, -0.4f, 0.0f);
	glVertex3f(-0.9f, -0.4f, 0.0f);

	glVertex3f(-0.9f, -0.4f, 0.0f);
	glVertex3f(-0.9f, 0.3f, 0.0f);
	glVertex3f(-0.9f, 0.3f, 0.6f);
	glVertex3f(-0.9f, -0.3f, 0.6f);

	glVertex3f(-0.9f, -0.3f, 0.6f);
	glVertex3f(-0.9f, 0.3f, 0.6f);
	glVertex3f(0.9f, 0.3f, 0.6f);
	glVertex3f(0.9f, -0.3f, 0.6f);

	glVertex3f(0.9f, -0.3f, 0.6f);
	glVertex3f(0.9f, 0.3f, 0.6f);
	glVertex3f(0.9f, 0.3f, 0.0f);
	glVertex3f(0.9f, -0.4f, 0.0f);

	glVertex3f(0.9f, -0.4f, 0.0f);
	glVertex3f(-0.9f, -0.4f, 0.0f);
	glVertex3f(-0.9f, 0.3f, 0.0f);
	glVertex3f(0.9f, 0.3f, 0.0f);

	glVertex3f(0.9f, 0.3f, 0.0f);
	glVertex3f(-0.9f, 0.3f, 0.0f);
	glVertex3f(-0.9f, 0.3f, 0.6f);
	glVertex3f(0.9f, 0.3f, 0.6f);

	glEnd();
}

void drawStomach()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);

	glVertex3f(-0.7f, -0.3f, 0.0f); //A
	glVertex3f(0.7f, -0.3f, 0.0f); //B
	glVertex3f(-0.7f, 0.2f, 0.0f); //C
	glVertex3f(0.7f, 0.2f, 0.0f); //D
	glVertex3f(-0.9f, -0.4f, 1.0f); //I
	glVertex3f(0.9f, -0.4f, 1.0f); //J
	glVertex3f(-0.9f, 0.3f, 1.0f); //K
	glVertex3f(0.9f, 0.3f, 1.0f); //L

	glVertex3f(-0.9f, -0.4f, 1.0f);
	glVertex3f(0.9f, -0.4f, 1.0f);
	glVertex3f(0.7f, -0.3f, 0.0f);
	glVertex3f(-0.7f, -0.3f, 0.0f);

	glVertex3f(-0.7f, -0.3f, 0.0f);
	glVertex3f(-0.7f, 0.2f, 0.0f);
	glVertex3f(-0.9f, 0.3f, 1.0f);
	glVertex3f(-0.9f, -0.4f, 1.0f);

	glVertex3f(-0.9f, -0.4f, 1.0f);
	glVertex3f(-0.9f, 0.3f, 1.0f);
	glVertex3f(0.9f, 0.3f, 1.0f);
	glVertex3f(0.9f, -0.4f, 1.0f);

	glVertex3f(0.9f, -0.4f, 1.0f);
	glVertex3f(0.9f, 0.3f, 1.0f);
	glVertex3f(0.7f, 0.2f, 0.0f);
	glVertex3f(0.7f, -0.3f, 0.0f);

	glVertex3f(0.7f, -0.3f, 0.0f);
	glVertex3f(-0.7f, -0.3f, 0.0f);
	glVertex3f(-0.7f, 0.2f, 0.0f);
	glVertex3f(0.7f, 0.2f, 0.0f);

	glVertex3f(0.7f, 0.2f, 0.0f);
	glVertex3f(-0.7f, 0.2f, 0.0f);
	glVertex3f(-0.9f, 0.3f, 1.0f);
	glVertex3f(0.9f, 0.3f, 1.0f);

	glEnd();
}

void drawWaist()
{
	GLUquadricObj* waist = NULL;
	waist = gluNewQuadric();
	gluSphere(waist, 0.4, 30, 30);
}

void drawHips()
{
	GLUquadricObj* hips = NULL;
	hips = gluNewQuadric();
	gluSphere(hips, 0.9, 30, 30);
}

void drawBottomArmor()
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);

	glVertex3f(0.0f, -0.1f, 0.4f);
	glVertex3f(0.1f, -0.1f, 0.4f);
	glVertex3f(0.4f, -0.1f, 0.0f);
	glVertex3f(-0.4f, -0.1f, 0.0f);

	glVertex3f(-0.4f, -0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.4f);
	glVertex3f(0.0f, -0.1f, 0.4f);

	glVertex3f(0.0f, -0.1f, 0.4f);
	glVertex3f(0.0f, 0.1f, 0.4f);
	glVertex3f(0.1f, 0.1f, 0.4f);
	glVertex3f(0.1f, -0.1f, 0.4f);

	glVertex3f(0.1f, -0.1f, 0.4f);
	glVertex3f(0.1f, 0.1f, 0.4f);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(0.4f, -0.1f, 0.0f);

	glVertex3f(0.4f, -0.1f, 0.0f);
	glVertex3f(-0.4f, -0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(0.4f, 0.1f, 0.0f);

	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.4f);
	glVertex3f(0.1f, 0.1f, 0.4f);

	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 1.0);

	glVertex3f(0.0f, -0.1f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.6f);
	glVertex3f(0.1f, -0.1f, 0.4f);

	glVertex3f(0.1f, -0.1f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.6f);
	glVertex3f(0.1f, 0.1f, 0.4f);

	glVertex3f(0.1f, 0.1f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.6f);
	glVertex3f(0.0f, 0.1f, 0.4f);

	glVertex3f(0.0f, 0.1f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.6f);
	glVertex3f(0.0f, -0.1f, 0.4f);

	glEnd();
}

void drawBottom()
{
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.0);

	glVertex3f(-0.4f, -0.3f, 0.8f);
	glVertex3f(0.4f, -0.3f, 0.8f);
	glVertex3f(0.4f, -0.3f, 0.4f);
	glVertex3f(-0.4f, -0.3f, 0.4f);

	glVertex3f(-0.4f, -0.3f, 0.4f);
	glVertex3f(-0.4f, 0.3f, 0.4f);
	glVertex3f(-0.4f, 0.3f, 0.8f);
	glVertex3f(-0.4f, -0.3f, 0.8f);

	glVertex3f(-0.4f, -0.3f, 0.8f);
	glVertex3f(-0.4f, 0.3f, 0.8f);
	glVertex3f(0.4f, 0.3f, 0.8f);
	glVertex3f(0.4f, -0.3f, 0.8f);

	glVertex3f(0.4f, -0.3f, 0.8f);
	glVertex3f(0.4f, 0.3f, 0.8f);
	glVertex3f(0.4f, 0.3f, 0.4f);
	glVertex3f(0.4f, -0.3f, 0.4f);

	glVertex3f(0.4f, -0.3f, 0.4f);
	glVertex3f(-0.4f, -0.3f, 0.4f);
	glVertex3f(-0.4f, 0.3f, 0.4f);
	glVertex3f(0.4f, 0.3f, 0.4f);

	glVertex3f(0.4f, 0.3f, 0.4f);
	glVertex3f(-0.4f, 0.3f, 0.4f);
	glVertex3f(-0.4f, 0.3f, 0.8f);
	glVertex3f(0.4f, 0.3f, 0.8f);

	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 0.0);

	glVertex3f(-0.4f, -0.3f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, -0.3f, 0.4f);

	glVertex3f(0.4f, -0.3f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.3f, 0.4f);

	glVertex3f(0.4f, 0.3f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.4f, 0.3f, 0.4f);

	glVertex3f(-0.4f, 0.3f, 0.4f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.4f, -0.3f, 0.4f);

	glEnd();
}

void body() {
	glPushMatrix(); //all
	glTranslatef(0.2, 0.35, 0.0);
	glPushMatrix(); //neck

	glRotatef(90, 0.0, 0.8, 0.0);
	glRotatef(270, 0.8, 0.0, 0.0);
	glTranslatef(0.0, 0.2, 0.3);
	glScalef(0.4, 0.4, 0.4);
	drawNeck();

	glPopMatrix(); //neck

	glPushMatrix(); //right shoulder

	glRotatef(90, 0.0, 0.8, 0.0);
	glRotatef(250, 0.8, 0.0, 0.0);
	glTranslatef(0.01, 0.4, 0.5);
	glScalef(0.4, 0.4, 0.4);
	drawShoulder();

	glPopMatrix(); //right shoulder

	glPushMatrix(); //left shoulder

	glRotatef(90, 0.0, 0.8, 0.0);
	glRotatef(-65, 0.8, 0.0, 0.0);
	glTranslatef(0.01, 0.1, 0.35);
	glScalef(0.4, 0.4, 0.4);
	drawShoulder();

	glPopMatrix(); //left shoulder

	glPushMatrix(); //chest

	glRotatef(270, 0.8, 0.0, 0.0);
	glTranslatef(-0.2, 0.0, -0.02);
	glScalef(0.26, 0.4, 0.4);
	drawChest();

	glPopMatrix(); //chest

	glPushMatrix(); //stomach

	glRotatef(270, 0.8, 0.0, 0.0);
	glTranslatef(-0.2, 0.0, -0.42);
	glScalef(0.26, 0.4, 0.4);
	drawStomach();

	glPopMatrix(); //stomach

	glPushMatrix(); //frontplate

	glRotatef(90, 0.0, 0.8, 0.0);
	glRotatef(270, 0.8, 0.0, 0.0);
	glTranslatef(0.16, 0.2, 0.0);
	glScalef(0.4, 0.4, 0.4);
	drawFrontPlateLeft();
	drawFrontPlateRight();

	glPopMatrix(); //frontplate

	glPushMatrix(); //waist

	glTranslatef(-0.2, -0.5, 0.02);
	glScalef(0.35, 0.35, 0.35);
	drawWaist();

	glPopMatrix(); //waist

	glPushMatrix(); //hips

	glTranslatef(-0.2, -0.72, 0.0);
	glScalef(0.3, 0.15, 0.3);
	drawHips();

	glPopMatrix(); //hips

	glPushMatrix(); //bottom

	glRotatef(270, 0.8, 0.0, 0.0);
	glTranslatef(-0.2, 0.0, -1.05);
	glScalef(0.3, 0.3, 0.3);
	drawBottom();

	glPopMatrix(); // bottom

	glPushMatrix(); //bottom armor

	glRotatef(270, 0.8, 0.0, 0.0);
	glTranslatef(0.4, -0.2, 0.0);
	glScalef(0.3, 0.3, 0.3);


	glRotatef(270, 0.0, 0.8, 0.0);
	glTranslatef(-2.6, 1.65, 2.05);
	drawBottomArmor();

	glRotatef(180, 0.0, 0.8, 0.0);
	glTranslatef(0.0, 0.0, 0.1);
	drawBottomArmor();
	glPopMatrix(); // bottom armor

	glPopMatrix(); //all
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glRotatef(x, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glScalef(1,0.55,1);
	body();
	glPopMatrix();
	
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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

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