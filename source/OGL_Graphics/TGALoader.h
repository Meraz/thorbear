#ifndef _TGALOADER_H_
#define _TGALOADER_H_

#include <cstdlib>

/**
 * This structure holds info about the TGA image before we load it into OpenGL.
 *
 * @author Tom Arnold
 */
struct tga_data_t {
	unsigned char depth;
	short int w, h;
	unsigned char* data;
};

tga_data_t* tga_data_load( const char* fn );

#endif
