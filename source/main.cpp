#include "OGL_Graphics/OGL_Graphics.h"

#include <cstdio>

int main()
{
  OGL_Graphics* l_graphics = new OGL_Graphics();
  if(! l_graphics->Init() )
    printf( l_graphics->GetErrorMessage( ).c_str( ) );
  
  getchar();
  return 0;
}