#include <windows.h>
#include <commctrl.h>

LRESULT CALLBACK WindowProc( HWND, UINT, WPARAM, LPARAM );

INT WINAPI WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInst,
	LPSTR p_CmdLine, INT p_CmdShow )
{
	INITCOMMONCONTROLSEX	CommonControls;
	WNDCLASSEX				WinClass;
	LPCTSTR					ClassName = TEXT( "Project Sinister" );
	HWND					WindowHandle;
	MSG						Message;

	CommonControls.dwSize = sizeof( CommonControls );
	CommonControls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx( &CommonControls );

	WinClass.cbSize			= sizeof( WinClass );
	WinClass.style			= CS_HREDRAW | CS_VREDRAW;
	WinClass.lpfnWndProc	= WindowProc;
	WinClass.cbClsExtra		= 0;
	WinClass.cbWndExtra		= 0;
	WinClass.hInstance		= p_ThisInst;
	WinClass.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	WinClass.hIconSm		= LoadIcon( NULL, IDI_APPLICATION );
	WinClass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	WinClass.hbrBackground	= ( HBRUSH )GetStockObject( WHITE_BRUSH );
	WinClass.lpszMenuName	= NULL;
	WinClass.lpszClassName	= ClassName;

	if( !RegisterClassEx( &WinClass ) )
	{
		MessageBox( NULL, TEXT( "Failed to register window" ), ClassName,
			MB_ICONERROR | MB_OK );

		return 0;
	}

	HWND DesktopWindow = GetDesktopWindow( );
	HDC DesktopContext = GetDC( DesktopWindow );
	int Width = GetDeviceCaps( DesktopContext, HORZRES );
	int Height = GetDeviceCaps( DesktopContext, VERTRES );
	ReleaseDC( DesktopWindow, DesktopContext );

	int X = ( int )( ( ( float )Width / 2.0f )-640.0f );
	int Y = ( int )( ( ( float )Height / 2.0f )-360.0f  );

	WindowHandle = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		ClassName, ClassName,
		WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CAPTION |
		WS_MINIMIZEBOX | WS_OVERLAPPED, X, Y, 1280,
		720, NULL, NULL, p_ThisInst, NULL );
	
	ShowWindow( WindowHandle, p_CmdShow );
	UpdateWindow( WindowHandle );

	while( GetMessage( &Message, NULL, 0, 0 ) )
	{
		TranslateMessage( &Message );
		DispatchMessage( &Message );
	}

	return Message.wParam;
}

LRESULT CALLBACK WindowProc( HWND p_Window, UINT p_Message, WPARAM p_WParam,
	LPARAM p_LParam )
{
	HDC			DeviceContext;
	PAINTSTRUCT	Paint;
	RECT		Rect;

	switch( p_Message )
	{
		case WM_PAINT:
		{
			DeviceContext = BeginPaint( p_Window, &Paint );
			GetClientRect( p_Window, &Rect );
			DrawText( DeviceContext, TEXT( "Project Sinister" ), -1, &Rect,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER );
			EndPaint( p_Window, &Paint );
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}
		default:
		{
			return DefWindowProc( p_Window, p_Message, p_WParam, p_LParam );
		}
	}

	return 0L;
}

