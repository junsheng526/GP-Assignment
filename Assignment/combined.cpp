#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <Math.h>

#define WINDOW_TITLE "Robot"
//Nielsen
//Lighting
float dif[] = { 1.0, 1.0, 1.0 };
float DLightx = 0.0;
float DLighty = 1.0;
float DLightz = 0.0;
float posD[] = { DLightx, DLighty, DLightz }; //white diffuse ligh
bool isLightOn = false;

//Turning Robot 
float LegHeliSpeed = 0.0;
float legSpinSpeed = 0.0;
float FlyUp = 0.0;
float FlightUp = 0.0;


//Junsheng animation new variable
//head
float rUDHead = 0, rLRHead = 0, rHeadUDSpeed = 10, rHeadLRSpeed = 10;
float rLRHeadX = 0, rLRHeadY = 0, rLRHeadZ = 0;
float rUDHeadX = 0, rUDHeadY = 0, rUDHeadZ = 0;
//head
float rBody = 0, rBodySpeed = 10, rBodyX = 0, rBodyY = 0, rBodyZ = 0;
float rLeg = 0, rLegSpeed = 10, rLegX = 0, rLegY = 0, rLegZ = 0;
float tLegX = 0, tLegY = 0, tLegZ = 0, tLegSpeed = 0.05;
float tHandX = 0, tHandY = 0, tHandZ = 0, tHandSpeed = 0.5;
float rLegToWalk = 0, rLegToWalkSpeed = 10, rLegToWalkX = 0, rLegToWalkY = 0, rLegToWalkZ = 0;
float tRobotPosition = 0, tRobotPositionX = 0, tRobotPositionY = 0, tRobotPositionZ = 0, tRobotPositionSpeed = 1;
float rHand = 0, rHandX = 0, rHandY = 0, rHandZ = 0, rHandSpeed = 10;

//^^^^^^^^^^^^^^Junsheng animation new variable^^^^^^^^^^^^^^^^
int qNo = 1;
float x = 0, y = 0;		//origin of circle (x, y) (0,0)
float radius = 0.5;		//radius of circle
float angle = 0;		//angle of circle
float PI = 3.1429;		//PI
float x2 = 0, y2 = 0;	//point on circle (x2,y2)
float noOfTri = 36;		//no of triangles


//Sheyn
float lRArmSpeed, lRArmSpeedX, lRArmSpeedY, lRArmSpeedZ;
float tx = 0, ty = 0, tz = 0, tSpeed = 1.0;
float ptx = 0.0, pty = 0.0, ptSpeed = 0.5;
float pry = 0.0, prSpeed = 1.0;
bool isOrtho = true;
float oNear = -20.0, oFar = 20.0;
float pNear = 1.0, pFar = 21.0;
float rs1 = 3.0;
float lazerZ = 0, lazer = 0;
//Sheyn
//----------new variables------------------------------------------
float lArmSpeed, lArmSpeedX, lArmSpeedY, lArmSpeedZ;
float lSArmSpeed, lSArmSpeedX, lSArmSpeedY, lSArmSpeedZ;
float lSLArmSpeed, lSLArmSpeedX, lSLArmSpeedY, lSLArmSpeedZ;
float lLArmSpeed, lLArmSpeedX, lLArmSpeedY, lLArmSpeedZ;
float lLLArmSpeed, lLLArmSpeedX, lLLArmSpeedY, lLLArmSpeedZ;
float mWristSpeed, mWristSpeedX, mWristSpeedY, mWristSpeedZ;
float mLWristSpeed, mLWristSpeedX, mLWristSpeedY, mLWristSpeedZ;
float wSpeedX, wSpeedY, wSpeedZ;
float wLSpeedX, wLSpeedY, wLSpeedZ;
float sSheildX = 30.0, sSheildY = 30.0, sSheildZ = 30.0;
//Sheyn

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
		//else if (wParam == 'P') {
		//	isOrtho = false;
		//	tz = pNear + 3.0;
		//}
		//Sheyn
		else if (wParam == 'A')
			ptx -= ptSpeed;
		else if (wParam == 'D')
			ptx += ptSpeed;
		else if (wParam == VK_HOME)
			pty += ptSpeed;
		else if (wParam == VK_END)
			pty -= ptSpeed;
		else if (wParam == 'L')
			pry += prSpeed;
		else if (wParam == 'R')
			pry -= prSpeed;

		//vvvvvvvvvvvvvvvvvjunsheng new statementvvvvvvvvvvvvvvvvvvvv
		//vvvvvvvvmove headvvvvvvvvvv
		else if (wParam == VK_F1) {
			rLRHeadX = 0.0;
			rLRHeadY = 10.0;
			rLRHeadZ = 0.0;
			rLRHead += rHeadLRSpeed;
			if (rLRHead >= 10) {
				rLRHead = 10;
			}
		}
		else if (wParam == VK_F2) {
			rLRHeadX = 0.0;
			rLRHeadY = 10.0;
			rLRHeadZ = 0.0;
			rLRHead -= rHeadLRSpeed;
			if (rLRHead <= -10) {
				rLRHead = -10;
			}
		}
		else if (wParam == VK_F3) {
			rUDHeadX = 10.0;
			rUDHeadY = 0.0;
			rUDHeadZ = 0.0;
			rUDHead += rHeadUDSpeed;
			if (rUDHead >= 10) {
				rUDHead = 10;
			}
		}
		else if (wParam == VK_F4) {
			rUDHeadX = 10.0;
			rUDHeadY = 0.0;
			rUDHeadZ = 0.0;
			rUDHead -= rHeadUDSpeed;
			if (rUDHead <= -10) {
				rUDHead = -10;
			}
		}
		//^^^^^^^^^^move head^^^^^^^^^^^^
		//vvvvvvvvmove bodyvvvvvvvvvv
		else if (wParam == VK_F5) {
			rBodyY = 10.0;
			rBody += rBodySpeed;
		}
		else if (wParam == VK_F6) {
			rBodyY = 10.0;
			rBody -= rBodySpeed;
		}
		else if (wParam == VK_F7) {
			rBodyZ = 10.0;
			rBody += rBodySpeed;
		}
		else if (wParam == VK_F8) {
			rBodyZ = 10.0;
			rBody -= rBodySpeed;
		}
		
		//^^^^^^^^^^move body^^^^^^^^^^^^
		//vvvvvvvvvvvvmove legvvvvvvvvvv

		else if (wParam == 'X') {			//crouch up
			rLegX = 10.0;
			rLeg += rLegSpeed;
			tLegY += tLegSpeed;
			tHandY += tHandSpeed;
			if (rLeg >= 10 && tLegY >= 0.05 && tHandY >= 0.5) {
				rLeg = 10;
				tLegY = 0.05;
				tHandY = 0.5;
			}
		}

		else if (wParam == 'Z') {			//crouch down
			rLegX = 10.0;
			rLeg -= rLegSpeed;
			tLegY -= tLegSpeed;
			tHandY -= tHandSpeed;
			if (rLeg <= -10 && tLegY <= -0.05 && tHandY <= -0.5) {
				rLeg = -10;
				tLegY = -0.05;
				tHandY = -0.5;
			}
		}
		else if (wParam == 'W') {
			rLegToWalkX = 10.0;
			rLegToWalkZ = 10.0;
			rLegToWalk -= rLegToWalkSpeed;//Right Front Leg
			tRobotPosition += tRobotPositionSpeed;
			if (rLegToWalk <= -10) {
				rLegToWalk += (2*rLegToWalkSpeed);
			}
			else if (rLegToWalk >= 10) {
				rLegToWalk -= (2 * rLegToWalkSpeed);
			}
			if (isOrtho) {
				if (tz < oFar)
					tz += tSpeed;
			}
			else {
				if (tz < (pFar - rs1) / 2)
					tz += tSpeed;
			}
		}
		else if (wParam == 'S') {
			rLegToWalkX = -10.0;
			rLegToWalkZ = -10.0;
			rLegToWalk += rLegToWalkSpeed;//Right Front Leg
			tRobotPosition -= tRobotPositionSpeed;
			if (rLegToWalk <= -10) {
				rLegToWalk += (2 * rLegToWalkSpeed);
			}
			else if (rLegToWalk >= 10) {
				rLegToWalk -= (2 * rLegToWalkSpeed);
			}
			
			if (isOrtho) {
				if (tz > oNear)
					tz -= tSpeed;
			}
			else {
				if (tz > (pNear + rs1))
					tz -= tSpeed;
			}
		}
		//else if (wParam == VK_TAB) {
		//	rHandX = 10.0;
		//	rHandY = 0.0;
		//	rHandZ = 0.0;
		//	rHand += rHandSpeed;
		//}
		//else if (wParam == 'Q') {
		//	rHandX = 10.0;
		//	rHandY = 0.0;
		//	rHandZ = 0.0;
		//	rHand -= rHandSpeed;
		//}
		else if (wParam == 'M') {
			lazerZ -= 10;
		}
		else if (wParam == 'N') {
		lazerZ = 1;
		}
		//-------------------------------Junsheng finish---------------------------------------
		//-------------------------------Nielsen Start-------------------------------------------
		else if (wParam == 'T')  //Turn on/off lights
		isLightOn = !isLightOn;

		/*else if (wParam == 'G') {
		DLightx = 0.0;
		DLighty = 1.0;
		DLightz = 0.0;
		}

		else if (wParam == 'B') {
		DLightx = 0.0;
		DLighty = -1.0;
		DLightz = 0.0;
		}

		else if (wParam == 'H') {
		DLightx = -1.0;
		DLighty = 0.0;
		DLightz = 0.0;
		}

		else if (wParam == 'J') {
		DLightx = 1.0;
		DLighty = 0.0;
		DLightz = 0.0;
		}

		else if (wParam == 'N') {
		DLightx = 0.0;
		DLighty = 0.0;
		DLightz = -1.0;

		}

		else if (wParam == 'M') {
		DLightx = 0.0;
		DLighty = 0.0;
		DLightz = 1.0;
		}*/

		else if (wParam == VK_F11) {
		legSpinSpeed = 20.0;
		FlightUp = 0.05;
		}
		//-------------------------------Nielsen Finish-------------------------------------------
		//-------------animation sheyn-----------------------
		else if (wParam == '1') {
		lRArmSpeed = 40.0;
		lRArmSpeedX = 10.0;
		lRArmSpeedY = 0.0;
		lRArmSpeedZ = 0.0;
		lArmSpeed = -40.0;
		lArmSpeedX = 10.0;
		lArmSpeedY = 0.0;
		lArmSpeedZ = 0.0;
		}
		else if (wParam == '2') {
		lRArmSpeed = 0.0;
		lRArmSpeedX = 0.0;
		lRArmSpeedY = 0.0;
		lRArmSpeedZ = 0.0;
		lArmSpeed = 0.0;
		lArmSpeedX = 0.0;
		lArmSpeedY = 0.0;
		lArmSpeedZ = 0.0;
		}
		else if (wParam == '3') {
		lSArmSpeed = 90.0;
		lSArmSpeedX = 0.0;
		lSArmSpeedY = 1.0;
		lSArmSpeedZ = 0.0;
		lSLArmSpeed = -90.0;
		lSLArmSpeedX = 0.0;
		lSLArmSpeedY = 1.0;
		lSLArmSpeedZ = 0.0;
		}
		else if (wParam == '4') {
		lSArmSpeed = 0.0;
		lSArmSpeedX = 0.0;
		lSArmSpeedY = 0.0;
		lSArmSpeedZ = 0.0;
		lSLArmSpeed = 0.0;
		lSLArmSpeedX = 0.0;
		lSLArmSpeedY = 0.0;
		lSLArmSpeedZ = 0.0;
		}
		else if (wParam == '5') {
		lLArmSpeed = 40.0;
		lLArmSpeedX = 1.0;
		lLArmSpeedY = 0.0;
		lLArmSpeedZ = 0.0;
		lLLArmSpeed = 40.0;
		lLLArmSpeedX = -1.0;
		lLLArmSpeedY = 0.0;
		lLLArmSpeedZ = 0.0;
		}
		else if (wParam == '6') {
		lLArmSpeed = 0.0;
		lLArmSpeedX = 0.0;
		lLArmSpeedY = 0.0;
		lLArmSpeedZ = 0.0;
		lLLArmSpeed = 0.0;
		lLLArmSpeedX = 0.0;
		lLLArmSpeedY = 0.0;
		lLLArmSpeedZ = 0.0;
		}
		else if (wParam == '7') {
		wSpeedX = 30.0;
		wSpeedY = 30.0;
		wSpeedZ = 30.0;
		wLSpeedX = 30.0;
		wLSpeedY = 30.0;
		wLSpeedZ = 30.0;
		}
		else if (wParam == '8') {
		wSpeedX = 0.0;
		wSpeedY = 0.0;
		wSpeedZ = 0.0;
		wLSpeedX = 0.0;
		wLSpeedY = 0.0;
		wLSpeedZ = 0.0;
		}
		else if (wParam == 'K') {	//need change 
		sSheildX = 0.0;
		sSheildY = 0.0;
		sSheildZ = 0.0;
		}
		else if (wParam == 'F') {	//need change 
		sSheildX = 30.0;
		sSheildY = 30.0;
		sSheildZ = 30.0;
		}
		//-------------animation sheyn-----------------------
		//mchange texture 1
		else if (wParam == VK_SPACE) {
		tx = 0;
		ty = 0;
		tz = 0;
		ptx = 0;
		pty = 0;
		pry = 0;
		rLRHeadX = 0.0;
		rLRHeadY = 0.0;
		rLRHeadZ = 0.0;
		rUDHeadX = 0.0;
		rUDHeadY = 0.0;
		rUDHeadZ = 0.0;
		rBodyY = 0.0;
		rBody = 0;
		rBodyY = 0.0;
		rBody = 0;
		rBodyZ = 0.0;
		rBody = 0;
		rBodyZ = 0.0;
		rBody = 0;
		rLegX = 0.0;
		rLeg = 0;
		tLegY = 0;
		tHandY = 0;
		rLegToWalkX = 0.0;
		rLegToWalkZ = 0.0;
		rLegToWalk = 0;
		rLegToWalkX = 0.0;
		rLegToWalkZ = 0.0;
		rLegToWalk = 0;
		lazerZ = 1;
		sSheildX = 30.0;
		sSheildY = 30.0;
		sSheildZ = 30.0;
		wSpeedX = 0.0;
		wSpeedY = 0.0;
		wSpeedZ = 0.0;
		wLSpeedX = 0.0;
		wLSpeedY = 0.0;
		wLSpeedZ = 0.0;
		lLArmSpeed = 0.0;
		lLArmSpeedX = 0.0;
		lLArmSpeedY = 0.0;
		lLArmSpeedZ = 0.0;
		lLLArmSpeed = 0.0;
		lLLArmSpeedX = 0.0;
		lLLArmSpeedY = 0.0;
		lLLArmSpeedZ = 0.0;
		lSArmSpeed = 0.0;
		lSArmSpeedX = 0.0;
		lSArmSpeedY = 0.0;
		lSArmSpeedZ = 0.0;
		lSLArmSpeed = 0.0;
		lSLArmSpeedX = 0.0;
		lSLArmSpeedY = 0.0;
		lSLArmSpeedZ = 0.0;
		lRArmSpeed = 0.0;
		lRArmSpeedX = 0.0;
		lRArmSpeedY = 0.0;
		lRArmSpeedZ = 0.0;
		lArmSpeed = 0.0;
		lArmSpeedX = 0.0;
		lArmSpeedY = 0.0;
		lArmSpeedZ = 0.0;
		legSpinSpeed = 0.0;
		FlightUp = 0.0;
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
//Sheyn
void projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			//reset matrix

	glTranslatef(ptx, pty, 0.0);	//only translate projection for tx,ty
	glRotatef(pry, 0.0, 1.0, 0.0);	//only rotate projection for ry

	if (isOrtho) {
		glOrtho(-20.0, 20.0, -20.0, 20.0, oNear, oFar);
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
	//animation wrist
	glPushMatrix();
	glTranslatef(wSpeedX, wSpeedY, wSpeedZ);

	//draw finger on robot
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

	//wrist right
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(-5.7, -0.5, -1.4);
	glRotatef(90, 0.3, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawPolygon(1.3, 0.0, 0.5, 1.0);
	glPopMatrix();

	glPopMatrix();
}

void drawLeftHand()
{
	//animation wrist
	glPushMatrix();
	glTranslatef(wLSpeedX, wLSpeedY, wLSpeedZ);

	glRotatef(-180, 0.0, 10.0, 0.0);
	glRotatef(-35, 10.0, 0.0, 0.0);

	//draw finger on hand
	glPushMatrix();
	glTranslatef(-6.0, -1.5, 1.3);
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

	//wrist right
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(-5.9, -1.5, 1.8);
	glRotatef(90, 0.3, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawPolygon(1.3, 0.0, 0.5, 1.0);
	glPopMatrix();

	glPopMatrix();
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

	glPushMatrix();
	glRotatef(lRArmSpeed, lRArmSpeedX, lRArmSpeedY, lRArmSpeedZ);
	//joint1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(0.1, 3.0, 0.0);
	drawSphere(0.45);
	glPopMatrix();

	//animation side arm
	glPushMatrix();
	glRotatef(lSArmSpeed, lSArmSpeedX, lSArmSpeedY, lSArmSpeedZ);

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

	//animation lower arm
	glPushMatrix();
	glRotatef(lLArmSpeed, lLArmSpeedX, lLArmSpeedY, lLArmSpeedZ);

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

	//draw right hand
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glTranslatef(-3.5, 1.0, -4.0);
	drawHand();
	glPopMatrix();

	//right finger
	glPushMatrix();
	glRotatef(lLArmSpeed, lLArmSpeedX, lLArmSpeedY, lLArmSpeedZ);
	glTranslatef(2.9, 0.0, 0.0);
	drawRightHand();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawLeftArm()
{
	glPushMatrix();
	glRotatef(-180, 0.0, 10.0, 0.0);

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

	glPushMatrix();
	glRotatef(lArmSpeed, lArmSpeedX, lArmSpeedY, lArmSpeedZ);
	//joint1
	glPushMatrix();
	glColor3f(1.0, 0.8, 0.5);
	glTranslatef(0.1, 3.0, 0.0);
	drawSphere(0.45);
	glPopMatrix();

	//animation side arm
	glPushMatrix();
	glRotatef(lSLArmSpeed, lSLArmSpeedX, lSLArmSpeedY, lSLArmSpeedZ);

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

	//animation lower arm
	glPushMatrix();
	glRotatef(lLLArmSpeed, lLLArmSpeedX, lLLArmSpeedY, lLLArmSpeedZ);

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

	//left hand
	glPushMatrix();
	glScalef(0.6, 0.6, 0.6);
	glTranslatef(-2.0, 1.7, 2.0);
	glRotatef(-35, 10.0, 0.0, 0.0);
	drawHand();
	glPopMatrix();

	//left finger
	glPushMatrix();
	glRotatef(lLLArmSpeed, lLLArmSpeedX, lLLArmSpeedY, lLLArmSpeedZ);
	glTranslatef(3.2, 0.0, 0.0);
	glRotatef(180, 0.0, 1.0, 0.0);
	drawLeftHand();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawBothArm()
{
	//right 

	glPushMatrix();
	glTranslatef(-3.0, 0.0, 0.0);
	drawRightArm();
	glPopMatrix();

	//left 
	glPushMatrix();
	glRotatef(rBody, rBodyX, rBodyY, rBodyZ);
	glTranslatef(tHandX, tHandY, tHandZ);
	glTranslatef(3.0, 0.0, 0.0);
	drawLeftArm();
	glPopMatrix();
}

void drawBothWeapon()
{
	glPushMatrix();
	glTranslatef(sSheildX, sSheildY, sSheildZ);

	//right weapon 
	glPushMatrix();
	glTranslatef(-5.0, -0.6, -2.5);	//glTranslatef(-4.9, -0.65, -2.0);
	glRotatef(-90, 0.0, 1.0, 0.3);
	showWeapon();
	glPopMatrix();

	//left weapon 
	glPushMatrix();
	glTranslatef(5.1, -0.7, -1.9);		//glTranslatef(5.1, -0.65, -2.0);
	glRotatef(-180, 0.0, 10.0, 0.0);	//rotate whole weapon
	glRotatef(-35, 10.0, 0.0, 0.0);		//rotate same side wif hand
	glRotatef(-90, 0.0, 1.0, 0.3);		//rotate same slope wif hand
	showWeapon();
	glPopMatrix();

	glPopMatrix();
}

void showHand()
{
	drawBothArm();
	drawBothWeapon();
}




//Nielsen Lau Mu Her

void drawShoulder()
{
	glBegin(GL_QUADS);
	
	glColor3f(0.45, 0.41, 0.32);
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
	glColor3f(0.55, 0.5, 0.4);

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
	glColor3f(0.06, 1.00, 0.98);

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
	glColor3f(0.06, 1.00, 0.98);

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
	glColor3f(0.45, 0.41, 0.32);

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
	glColor3f(0.55, 0.5, 0.4);

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
	glColor3f(0.45, 0.41, 0.32);

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
	glColor3f(0.20, 0.16, 0.17);
	GLUquadricObj* waist = NULL;
	waist = gluNewQuadric();
	gluSphere(waist, 0.4, 30, 30);
}

void drawHips()
{
	glColor3f(0.07, 0.07, 0.06);
	GLUquadricObj* hips = NULL;
	hips = gluNewQuadric();
	gluSphere(hips, 0.9, 30, 30);
}

void drawBottomArmor()
{
	glBegin(GL_QUADS);
	glColor3f(0.45, 0.41, 0.32);

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
	glColor3f(0.45, 0.41, 0.32);

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
	glPushMatrix();//upper body

	
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
	glTranslatef(0.01, 0.05, 0.34);
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

	glPopMatrix();//upper body

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

//Nielsen Lau Mu Her

//Choo Jun Sheng

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

void drawSphere(float r, float sl, float st) {
	GLUquadricObj* sphere = NULL;			//create quadric obj pointer
	sphere = gluNewQuadric();				//create the quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//set the draw style
	gluSphere(sphere, r, sl, st);			//draw sphere
	gluDeleteQuadric(sphere);				//delete the quadric obj
}

void drawCylinder2(float tr, float br, float h) {
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
	glColor3f(0.45, 0.41, 0.32);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sz * 2, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	//Face 2 : Left
	glBegin(GL_QUADS);
	glColor3f(0.55, 0.5, 0.4);
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
	glTranslatef(0.0, 0.0, 0.4);

	glPushMatrix();//blok2 top face
	drawCircle(0.5);
	glPopMatrix();//blok2 top face

	drawCylinder(0.5, 0.5, 1.0);

	glPushMatrix();//blok 3 bottom face
	glTranslatef(0.0, 0.0, 1.0);
	drawCircle(0.5);
	glPopMatrix();;//blok 3 bottom face

	glPopMatrix();//blok1

	glPushMatrix();//bottom part connecter sphere
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0, 0, 2.24);
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
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(-0.5, 0.04, -0.3);//
	glScalef(0.25, 2.25, 0.35);
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
	glRotatef(rLeg, rLegX, rLegY, rLegZ);
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
	glPopMatrix();
}


void fourLeg() {
	glPushMatrix();//4 leg

	glPushMatrix();//Right Front Leg
	glRotatef(rLegToWalk, rLegToWalkX, rLegToWalkY, rLegToWalkZ);
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	
	completeLeg();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Left Front Leg
	glRotatef(rLegToWalk, rLegToWalkX, rLegToWalkY, rLegToWalkZ);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	completeLeg();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rLegToWalk, rLegToWalkX, rLegToWalkY, rLegToWalkZ);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	//glRotatef(rLegToWalk, rLegToWalkX, rLegToWalkY, rLegToWalkZ);
	completeLeg();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rLegToWalk, rLegToWalkX, rLegToWalkY, rLegToWalkZ);
	glRotatef(270, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.25);
	
	completeLeg();
	glPopMatrix();

	glPopMatrix();//4 leg
}

//----------------------------------------------------------------------------------------------turn head
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
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.25);
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
	drawCylinder(0.25, 0.15, 0.4);//////////////////////cylider head !!!!!!!!!!!!!!!!!!!!!!!!!!!

	glPushMatrix();//small cylinder bottom face
	glTranslatef(0.0, 0.0, 0.4);
	glColor3f(0.45, 0.41, 0.32);
	drawCircle(0.15);

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
	glScalef(1, 1, lazerZ);
	drawCircle(0.05);
	drawCylinder(0.05,0.05,0.05);
	glPopMatrix();

	glPushMatrix();//eye2
	glColor3f(0.06, 1.00, 0.98);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(0.1, -0.15, -0.25);
	glRotatef(-30, 0.0, 1.0, 0.0);
	//glScalef(1, 1, -100);
	glScalef(1, 1, lazerZ);
	drawCircle(0.05);
	drawCylinder(0.05, 0.05, 0.05);
	glPopMatrix();

	glPopMatrix();//all
}

void robotHeadwithEye() {
	glRotatef(rBody, rBodyX, rBodyY, rBodyZ);
	robotHead();
}

//Choo Jun Sheng

void lighting()
{
	if (isLightOn) {
		glEnable(GL_LIGHTING);  //Enable lighting
	}
	else {
		glDisable(GL_LIGHTING);  //Disable lighting
	}

	//Light 0 : White color diffuse light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_POSITION, posD);
	glEnable(GL_LIGHT0);
}

void display()
{
	glClearColor(0.804, 0.820, 0.894, 0.004);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	lighting();
	projection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(tx, ty, tz);
	
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.0, FlyUp, 0.0);
	//glScalef(2, 2, 2);
	glPushMatrix();//all

	glPushMatrix();//hand
	glRotatef(rBody, rBodyX, rBodyY, rBodyZ);
	glTranslatef(tHandX, tHandY, tHandZ);
	showHand();
	glPopMatrix();//hand

	glPushMatrix();//x10
	glScalef(10, 10, 10);

	glPushMatrix();//body head
	glTranslatef(tLegX, tLegY, tLegZ);

	glPushMatrix();//body and head
	glRotatef(rBody, rBodyX, rBodyY, rBodyZ);
	glPushMatrix();
	glRotatef(rUDHead, rUDHeadX, rUDHeadY, rUDHeadZ);
	glRotatef(rLRHead, rLRHeadX, rLRHeadY, rLRHeadZ);
	glPushMatrix();//head
	glTranslatef(0, 0.72, 0);
	robotHeadwithEye();
	glPopMatrix();//head
	glPopMatrix();


	glPushMatrix();//body
	glScalef(1, 0.5, 1);
	body();
	glPopMatrix();//body
	glPopMatrix();//body and head

	glPopMatrix();//body head hand

	glPushMatrix();//leg
	glRotatef(LegHeliSpeed, 0.0, 1.0, 0.0);
	glTranslatef(0, -0.5, 0);
	glRotatef(45,0,1,0);
	//glRotatef(rLeg, rLegX, rLegY, rLegZ);
	fourLeg();
	glPopMatrix();//leg

	glPopMatrix();//x10

	glPopMatrix();//all
	LegHeliSpeed += legSpinSpeed;
	FlyUp += FlightUp;

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