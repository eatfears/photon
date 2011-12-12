#pragma once
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <vector>

class GLWindow
{
public:
	GLWindow(int iResolution);
	~GLWindow(void);

	void KillGLWindow(void);
	int InitGL(void);
	void ReSizeGLScene( GLsizei width, GLsizei height );
	bool CreateGLWindow( LPCSTR title, int width, int height, int bits);
	int DrawGLScene(std::vector<float> Matrix);

	HGLRC  hRC;						// ���������� �������� ����������
	HDC  hDC;						// ��������� �������� ���������� GDI
	HWND  hWnd;						// ����� ����� �������� ���������� ����
	HINSTANCE  hInstance;           // ����� ����� �������� ���������� ����������

	bool  keys[256];				// ������, ������������ ��� �������� � �����������
	bool  active;					// ���� ���������� ����, ������������� � true �� ���������
	bool  fullscreen;				// ���� ������ ����, ������������� � ������������� �� ���������

private:
	float fMulCoeffitient;
	int Resolution;
};
