#ifdef _WIN32 
#include "WindowWindows.h"

/*
int main(int argc, char** argv)
{
	HINSTANCE p_hInstance = 0;
	HINSTANCE p_hPrevInstance = 0;
	PSTR p_pScmdline = 0;
	int p_Cmdshow = 0;
	WindowWindows* m_windowWindows = new WindowWindows(p_hInstance, p_hPrevInstance, p_pScmdline, 0);
	system("pause");
	return 0;
}*/

int WINAPI WinMain(HINSTANCE p_hInstance, HINSTANCE p_hPrevInstance, PSTR p_pScmdline, int p_Cmdshow)
{
	WindowWindows* m_windowWindows = new WindowWindows();
	m_windowWindows->Initialize(p_hInstance, p_hPrevInstance, p_pScmdline, 0);
	m_windowWindows->Run();
	delete m_windowWindows;
	return 0;
}
#endif

#ifdef linux
#include "WindowLinux.h"
int main(int argc, char** argv)
{
	WindowLinux* m_windowLinux = new WindowLinux();

	return 0;
}

#endif