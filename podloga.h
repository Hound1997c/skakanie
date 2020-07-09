#ifndef PODLOGA_H
#define PODLOGA_H

//Podloga model made out of triangles
//Contains arrays:
//vertices - vertex positions in homogenous coordinates
//normals - vertex normals in homogenous coordinates
//texCoords - texturing coordinates
//colors - vertex colors (rgba)
//Culling GL_CW
//TBN friendly

#include "model.h"

namespace Models {
	namespace PodlogaInternal {
		extern float vertices[];
		extern float normals[];
		extern float vertexNormals[];
		extern float texCoords[];
		extern float colors[];
		extern unsigned int vertexCount;
	} 
	
	class Podloga: public Model {
		public:
			Podloga();
			virtual ~Podloga();
			virtual void drawSolid();
	};

	extern Podloga podloga;
}




#endif
