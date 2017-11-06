#ifndef OBJLOADER_H
#define OBJLOADER_H

/**
 * Modified objLoader provided by TAs on asssignment 1
 */

#include <vector>
#include "Primitive.h"
#include <memory>

class ObjLoader
{
public:
	static bool loadOBJ(const char * path, std::vector<std::shared_ptr<Primitive> >& primitives, Material* mat);
};

#endif