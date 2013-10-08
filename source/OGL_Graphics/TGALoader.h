#ifndef _TGALOADER_H_
#define _TGALOADER_H_

// Some macros to shorten things up.
//#define sint short int
#include "glm/ext.hpp"
#define uchar unsigned char

/**
 * This structure holds info about the TGA image before we load it into OpenGL.
 *
 * @author Tom Arnold
 */
struct tga_data_t {
	uchar depth;
	sint w, h;
	uchar* data;
};

tga_data_t* tga_data_load( const char* fn );

#endif
