#ifndef _TEXTURE_LOADER_H
#define _TEXTURE_LOADER_H

#include <string>
using namespace std;

namespace gl
{
	unsigned int load_texture_2d(const string& file);

	unsigned int load_texture_3d(const string& file);
}
#endif //_TEXTURE_LOADER_H
