#pragma once

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

class GLWindow
{
public:
	GLWindow(void);
	~GLWindow(void);

	void KillGLWindow(void);
	int InitGL(void);
	void ReSizeGLScene( GLsizei width, GLsizei height );
	bool CreateGLWindow( LPCSTR title, int width, int height, int bits);
	int DrawGLScene(void);

	HGLRC  hRC;						// ���������� �������� ����������
	HDC  hDC;						// ��������� �������� ���������� GDI
	HWND  hWnd;						// ����� ����� �������� ���������� ����
	HINSTANCE  hInstance;           // ����� ����� �������� ���������� ����������

	bool  keys[256];				// ������, ������������ ��� �������� � �����������
	bool  active;					// ���� ���������� ����, ������������� � true �� ���������
	bool  fullscreen;				// ���� ������ ����, ������������� � ������������� �� ���������
};
