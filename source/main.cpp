#ifdef _WIN32
#include "WindowWindows.h"
int WINAPI WinMain(HINSTANCE p_hInstance, HINSTANCE p_hPrevInstance, PSTR p_pScmdline, int p_Cmdshow)
{
	//WindowWindows* m_windowWindows = new WindowWindows(p_hInstance, p_hPrevInstance, p_pScmdline, p_Cmdshow);
	return 0;
}
#endif

#ifdef linux
#include "WindowLinux.h"
int main(int argc, char** argv)
{
	//WindowLinux* m_windowLinux = new WindowLinux();

	return 0;
}

#endif