#ifdef _WIN32 
#include "WindowWindows.h"
#include <vld.h>

int WINAPI WinMain(HINSTANCE p_hInstance, HINSTANCE p_hPrevInstance, PSTR p_pScmdline, int p_Cmdshow)
{
	WindowWindows* m_windowWindows = new WindowWindows();
	m_windowWindows->Initialize(p_hInstance, p_hPrevInstance, p_pScmdline, 0);
	m_windowWindows->Run();
	//delete m_windowWindows;
	return 0;
}
#endif

#ifdef linux
#include "WindowLinux.h"

int main(int argc, char** argv)
{
	WindowLinux* m_windowLinux = new WindowLinux();
  
  m_windowLinux->Run();
  
	return 0;
}

#endif
