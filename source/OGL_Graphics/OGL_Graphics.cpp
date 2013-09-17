// Works just as printf, only that it returns the result as a string instead of printing it
inline std::string stringf( const char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );
    std::string buf = vformat( fmt, ap );
    va_end( ap );
    return buf;
}

// Initialize the Win/Lin window and set up OpenGL 4
bool OGL_Graphics::Init( )
{
	if( !glfwInit() )
		return this->SetError( std::string( "ERROR: GLFW init\n" ) );
    
	// Get a list of supported video modes
	GLFWvidmode l_list[ 20 ];
	int l_numModes = glfwGetVideoModes( l_list, 20 );

	if( l_numModes < 1 )
		return this->SetError( std::string( "No desktop modes available!" ) );

	/*printf("Supported modes:\n");
	for (int i = 0; i < numModes; i++)
	{
		printf("\t %dx%d (%d, %d, %d)\n", list[i].Width, list[i].Height, list[i].RedBits, list[i].GreenBits, list[i].BlueBits);
	}*/

	// Pick the highest mode available
	int l_currentMode = l_numModes - 1;

	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 4 ); // set version of OpenGL to 4.0
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 0 );
	glfwOpenWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // do not allow deprecated
	//glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 16 ); // Multisampling, yay!
	//glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // force current version of spec

	if( !glfwOpenWindow(
        l_list[ l_currentMode ].Width,
        l_list[ l_currentMode ].Height,
        l_list[ l_currentMode ].RedBits,
        l_list[ l_currentMode ].GreenBits,
        l_list[ l_currentMode ].BlueBits,
        0,
        0,
        0,
        GLFW_WINDOW
        // GLFW_FULLSCREEN
      )
    )
	{
		glfwTerminate();
		return this->SetError( std::string( "ERROR: creating load window\n" ) );
	}
	
	// Start GLEW (that's it! - we could also use GLEW to check for driver support of all GL extensions)
	glewExperimental = 1;
	GLenum l_err = glewInit( );
	if ( l_err != GLEW_OK )
	{
		glfwTerminate();
		return this->SetError( stringf( "ERROR starting GLEW: %s\n", glewGetErrorString( l_err ) ) );
	}

	// Get version info and print it to the console
	const GLubyte* l_renderer = glGetString( GL_RENDERER );
	const GLubyte* l_vendor = glGetString( GL_VENDOR );
	const GLubyte* l_version = glGetString( GL_VERSION );
	const GLubyte* l_glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

	//GLint major, minor;
	glGetIntegerv( GL_MAJOR_VERSION, &l_major );
	glGetIntegerv( GL_MINOR_VERSION, &l_minor );
  if( l_major < 4 )
  {
		glfwTerminate();
		return this->SetError( stringf( "ERROR: GL Version not supported: %d\n", l_major ) );
  }
		
	// enable some useful GL behaviours
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_MULTISAMPLE_ARB );

	// set colour to clear screen buffer to
	glClearColor( 0.f, 0.f, 1.f, 1.f );
	glFlush();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear buffer using colour
	
	glfwSetWindowTitle( "SpaceOut: OpenGL4 Test" );//l_windowTitle.c_str( ) );
	glfwSwapInterval( 1 ); // VSync on
	
	// set-up callbacks. we can also do a keyboard and mouse input callback, and various others (see freeGLUT website)
	//glfwSetWindowSizeCallback( ResizeCallback ); // register callback for reshape (if set earlier won't be called until an actual resize)
}

// Draw rainbows!!!111
bool OGL_Graphics::Update( )
{
}

// Set the error message and return false to be returned further on for the error management
bool OGL_Graphics::SetError( std::string &p_errorMessage )
{
  this->m_errorMessage = p_errorMessage;
  
  return false;
}