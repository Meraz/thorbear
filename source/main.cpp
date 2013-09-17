#include "OGL_Graphics/OGL_Graphics.h"

int main()
{
  graphics = new OGL_Graphics();
  if(! graphics->Init() )
    printf( graphics->GetErrorMessage( ) );
  
  getch();
  return 0;
}