#include <gl/GL.h>
#include <gl/GLU.h>
#include "main.h"

void Render();

HDC hdc;
HGLRC hrc;

void Render()
{
    glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFinish();
}

void rnCreate(HWND hwnd,HDC dc){
     PIXELFORMATDESCRIPTOR pfd;
     int nPixelFormat;

     hdc=dc;
     memset(&pfd, 0, sizeof(pfd));

     pfd.nSize = sizeof(pfd);
     pfd.nVersion = 1;
     pfd.dwFlags = PFD_DRAW_TO_WINDOW |
					  PFD_SUPPORT_OPENGL;
     pfd.iPixelType = PFD_TYPE_RGBA;
     pfd.cColorBits = 32;

     nPixelFormat = ChoosePixelFormat(hdc, &pfd);
     SetPixelFormat(hdc, nPixelFormat, &pfd);

     hrc=wglCreateContext(hdc);
     wglMakeCurrent(hdc, hrc);
}

void rnSize(int size_x,int size_y){
		glViewport( 0, 0, size_x, size_y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, 1, -1);
		glMatrixMode(GL_MODELVIEW );
		glLoadIdentity();     
}

void rnDestroy(){
     wglMakeCurrent(hdc, NULL);
     wglDeleteContext(hrc);
     ReleaseDC(hWnd,hdc);
}

/*
void WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch (iMessage) {
	case WM_CREATE:
		hWndMain=hWnd;
		PIXELFORMATDESCRIPTOR pfd;
		int nPixelFormat;

		hdc=GetDC(hWnd);
		memset(&pfd, 0, sizeof(pfd));

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW |
					  PFD_SUPPORT_OPENGL;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;

		nPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, nPixelFormat, &pfd);

		hrc=wglCreateContext(hdc);
		wglMakeCurrent(hdc, hrc);
		return 0;
	case WM_PAINT:
		DoDisplay();
		SetTextColor(hdc, RGB(255,255,0));
		SetBkMode(hdc,TRANSPARENT);
		TextOutA(hdc,10,10,"Win32 OpenGL",12);
		ValidateRect(hWnd, NULL);
		return 0;
	case WM_SIZE:
		glViewport( 0, 0, LOWORD(lParam), HIWORD(lParam));
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-1, 1, -1, 1, 1, -1);

		glMatrixMode(GL_MODELVIEW );
		glLoadIdentity();
		return 0;
	case WM_DESTROY:
		wglMakeCurrent(hdc, NULL);
		wglDeleteContext(hrc);
		ReleaseDC(hWnd,hdc);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
*/