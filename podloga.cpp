#include "podloga.h"

namespace Models {

	Podloga podloga;

	Podloga::Podloga() {
		vertices=PodlogaInternal::vertices;
		normals=PodlogaInternal::normals;
		vertexNormals=PodlogaInternal::vertexNormals;
		texCoords=PodlogaInternal::texCoords;
		colors=PodlogaInternal::colors;
		vertexCount=PodlogaInternal::vertexCount;
	}

	Podloga::~Podloga() {
	}

	void Podloga::drawSolid() {
		glEnable(GL_NORMALIZE);

		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		// glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(4,GL_FLOAT,0,vertices);
		//glColorPointer(4,GL_FLOAT,0,colors);
		glNormalPointer(GL_FLOAT,sizeof(float)*4,vertexNormals);
		glTexCoordPointer(2,GL_FLOAT,0,texCoords);

		glDrawArrays(GL_TRIANGLES,0,vertexCount);

		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		// glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	namespace PodlogaInternal {
			unsigned int vertexCount=6;

			float vertices[]={
0,5.48653e-14,150,1.0,
150,0,0,1.0,
0,0,0,1.0,
150,0,0,1.0,
0,5.48653e-14,150,1.0,
150,5.48653e-14,150,1.0,
			};

			float colors[]={
			};

			float normals[]={
-3.90307e-17,1,-3.79531e-16,0.0,
-3.90307e-17,1,-3.79531e-16,0.0,
-3.90307e-17,1,-3.79531e-16,0.0,
-3.90307e-17,1,-3.79531e-16,0.0,
-3.90307e-17,1,-3.79531e-16,0.0,
-3.90307e-17,1,-3.79531e-16,0.0,
			};

			float vertexNormals[]={
			};

			float texCoords[]={
-7.02568e-31,49.2126,
-49.2126,-7.29003e-31,
0,0,
-49.2126,-7.29003e-31,
-7.02568e-31,49.2126,
-49.2126,49.2126,
			};
	}
}
