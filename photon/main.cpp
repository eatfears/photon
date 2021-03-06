#include <vector>
#include <deque>
#include <list>
#include <time.h>

#include "photon.h"
#include "gsl/gsl_randist.h"
gsl_rng *randNumGen;

#pragma comment( lib, "opengl32.lib" ) // ������ OpenGL32.lib ��� ��������
#pragma comment( lib, "glu32.lib" )    // ������ GLu32.lib ��� ��������

using namespace std;

GLWindow glwWnd;
Viewport vpViewport(300, 100);


LRESULT CALLBACK WndProc(  HWND  hWnd,      // ���������� ������� ����
	UINT  uMsg,								// ��������� ��� ����� ����
	WPARAM  wParam,							// �������������� ����������
	LPARAM  lParam)							// �������������� ����������
{
	switch (uMsg)							// �������� ��������� ��� ����
	{
	case WM_ACTIVATE:						// �������� ��������� ���������� ����
		{
			if( !HIWORD( wParam ) )			// ��������� ��������� �����������
			{
				glwWnd.active = true;				// ��������� �������
			}
			else
			{
				glwWnd.active = false;				// ��������� ������ �� �������
			}

			return 0;						// ������������ � ���� ��������� ���������
		}

	case WM_SYSCOMMAND:						// ������������� ��������� �������
		{
			switch ( wParam )				// ������������� ��������� �����
			{
			case SC_SCREENSAVE:				// �������� �� ���������� �����������?
			case SC_MONITORPOWER:			// �������� �� ������� ������� � ����� ���������� �������?
				return 0;					// ������������� ���
			}
			break;							// �����
		}

	case WM_CLOSE:							// �� �������� ��������� � ��������?
		{
			PostQuitMessage( 0 );			// ��������� ��������� � ������
			return 0;						// ��������� �����
		}

	case WM_KEYDOWN:						// ���� �� ������ ������?
		{
			glwWnd.keys[wParam] = true;			// ���� ���, �� ����������� ���� ������ true
			return 0;						// ������������
		}

	case WM_KEYUP:							// ���� �� �������� �������?
		{
			glwWnd.keys[wParam] = false;			//  ���� ���, �� ����������� ���� ������ false
			return 0;						// ������������
		}

	case WM_SIZE:							// �������� ������� OpenGL ����
		{
			glwWnd.ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );	// ������� �����=Width, ������� �����=Height
			return 0;						// ������������
		}
	}

	// ���������� ��� �������������� ��������� DefWindowProc
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

int WINAPI WinMain(  HINSTANCE  hInstance,  // ���������� ����������
	HINSTANCE  hPrevInstance,				// ���������� ������������� ����������
	LPSTR    lpCmdLine,						// ��������� ��������� ������
	int    nCmdShow )						// ��������� ����������� ����
	{
	MSG  msg;								// ��������� ��� �������� ��������� Windows
	BOOL  done = false;						// ���������� ���������� ��� ������ �� �����

	glwWnd.fullscreen = false;				// ������� �����

	// ������� ���� OpenGL ����
	if( !glwWnd.CreateGLWindow("Photon", 400, 400, 32) )
	{
		return 0;							// �����, ���� ���� �� ����� ���� �������
	}
	srand(time(NULL));
	randNumGen = gsl_rng_alloc(gsl_rng_mt19937);

	glwWnd.Resolution = vpViewport.Resolution;
	vpViewport.SceneInit();
	ImageSensor &isSensor_a = vpViewport.oWorld.isSensor;
	

	while( !done )							// ���� ������������, ���� done �� ����� true
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )	// ���� �� � ������� �����-������ ���������?
		{
			if( msg.message == WM_QUIT )    // �� ������� ��������� � ������?
			{
				done = true;				// ���� ���, done=true
			}

			else							// ���� ���, ������������ ���������
			{
				TranslateMessage( &msg );   // ��������� ���������
				DispatchMessage( &msg );	// �������� ���������
			}
		}
		else								// ���� ��� ���������
		{
			// ������������� �����.
			if( glwWnd.active )					// ������� �� ���������?
			{
				if(glwWnd.keys[VK_ESCAPE])			// ���� �� ������ ������� ESC?
				{
					done = true;			// ESC ������� �� �������� ���������� ���������
				}
				else						// �� ����� ��� ������, ������� �����.
				{
					vpViewport.OneStep();
					glwWnd.DrawGLScene(isSensor_a);			// ������ �����
					isSensor_a.Clear();

					double cng = 1.01;
					double nng = 0.1;

					if(glwWnd.keys[107] == true){
						vpViewport.oWorld.lLens.x+=nng;}
						//vpViewport.oWorld.lLens.Focus*=cng;}
					if(glwWnd.keys[109] == true){
						vpViewport.oWorld.lLens.x-=nng;}
						//vpViewport.oWorld.lLens.Focus/=cng;}
					if(glwWnd.keys[32] == true){
						vpViewport.oWorld.isSensor.ClearMode = SENSOR_ONE_CLEAR;}


					SwapBuffers( glwWnd.hDC );		// ������ ����� (������� �����������)
				}
			}
		}
	}

	glwWnd.KillGLWindow();						// ��������� ����
	return ( msg.wParam );					// ������� �� ���������
}