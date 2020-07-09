#ifndef DACHY_H
#define DACHY_H

//Dachy model made out of triangles
//Contains arrays:
//vertices - vertex positions in homogenous coordinates
//normals - vertex normals in homogenous coordinates
//texCoords - texturing coordinates
//colors - vertex colors (rgba)
//Culling GL_CW
//TBN friendly

#include "model.h"

namespace Models {
	namespace DachyInternal {
		extern float vertices[];
		extern float normals[];
		extern float vertexNormals[];
		extern float texCoords[];
		extern float colors[];
		extern unsigned int vertexCount;
	} 
	
	class Dachy: public Model {
		public:
			Dachy();
			virtual ~Dachy();
			virtual void drawSolid();
	};

	extern Dachy dachy;
}




#endif
