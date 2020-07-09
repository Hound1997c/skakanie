/*
Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "stb_image.h"
//#include <GL/gl.h>
#include <iostream>

using namespace glm;
using namespace std;

float aspect=1;
float speed=3.14; //prêdkoœæ k¹towa obrotu w radianach na sekundê
float wysokosci[225] = {
70, 70, 70, 0, 60, 60, 60, 0, 60, 60, 60, 0, 0,  0,  80,
70, 0,  0,  0, 60, 60, 60, 0, 60, 0,  60, 0, 0,  80, 80,
70, 0,  0,  0, 0,  60, 0,  0, 60, 0,  60, 0, 80, 80, 0,
0,  0,  0,  0, 0,  0,  0,  0, 0,  0,  0,  0, 0,  0,  0,
60, 60, 60, 0, 0,  90, 0,  0, 0,  60, 0,  0, 70, 0,  0,
60, 0,  0,  0, 90, 90, 90, 0, 60, 60, 60, 0, 70, 0,  0,
60, 60, 60, 0, 0,  90, 0,  0, 60, 60, 60, 0, 70, 70, 70,
0,  0,  0,  0, 0,  0,  0,  0, 0,  0,  0,  0, 0,  0,  0,
0,  90, 0,  0, 60, 0,  60, 0, 0,  90, 0,  0, 60, 60, 60,
90, 90, 90, 0, 60, 0,  60, 0, 90, 90, 90, 0, 0,  0,  60,
0,  90, 0,  0, 60, 60, 60, 0, 0,  90, 0,  0, 60, 60, 60,
0,  0,  0,  0, 0,  0,  0,  0, 0,  0,  0,  0, 0,  0,  0,
80, 80, 0,  0, 60, 60, 60, 0, 0,  60, 0,  0, 0,  0,  70,
0,  80, 0,  0, 60, 0,  0,  0, 60, 60, 60, 0, 0,  0,  70,
0,  80, 80, 0, 60, 60, 60, 0, 60, 60, 60, 0, 70, 70, 70,
};

int highMatrix [15][15];


float radius = 10.0f;
float camX = sin(glfwGetTime()) * radius;
float camZ = cos(glfwGetTime()) * radius;
glm::mat4 view;
glm::vec3 cameraPos;  /// 148.726 82.3851 148.632
glm::vec3 cameraFront;
glm::vec3 cameraUp;
// view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
float cameraSpeed = 5*0.05f; // adjust accordingly
bool isJumping = false;
bool isFalling = false;
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //cameraPos += cameraSpeed * cameraFront;
        {
            /*if(cameraPos.x + (cameraSpeed*cameraFront.x) <)
            {

            }*/
            cameraPos.x +=cameraSpeed*cameraFront.x;
            cameraPos.z +=cameraSpeed*cameraFront.z;
        }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //cameraPos -= cameraSpeed * cameraFront;
        {
            cameraPos.x -=cameraSpeed*cameraFront.x;
            cameraPos.z -=cameraSpeed*cameraFront.z;
        }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
       if (!isFalling) //*cameraPos.y;
       {
           cameraPos.y +=cameraSpeed;
           isJumping = true;
       }
       else
       {
           isJumping = false;
       }

    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        //cameraPos.y +=cameraSpeed*cameraFront.y;
        cout<<cameraPos.x<<" "<<cameraPos.y<<" "<<cameraPos.z<<endl;
        cout<<"tu jest "<<highMatrix[(int)cameraPos.z/10][(int)cameraPos.x/10]<<endl;

    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        isJumping = false;
    }
}

float lastX = 400, lastY = 300;
bool firstMouse = true;
float yawn = 0.0f;
float pitchn = 0.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yawn   += xoffset;
    pitchn += yoffset;

    if(pitchn > 89.0f)
        pitchn = 89.0f;
    if(pitchn < -89.0f)
        pitchn = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yawn)) * cos(glm::radians(pitchn));
    front.y = sin(glm::radians(pitchn));
    front.z = sin(glm::radians(yawn)) * cos(glm::radians(pitchn));
    cameraFront = glm::normalize(front);
}

unsigned int textureFloor;
int widthFloor, heightFloor, nrChannelsFloor;
unsigned char *dataFloor = stbi_load("podloga.png", &widthFloor, &heightFloor, &nrChannelsFloor, 3);

unsigned int textureWalls;
int widthWalls, heightWalls, nrChannelsWalls;
unsigned char *dataWalls = stbi_load("sciany.png", &widthWalls, &heightWalls, &nrChannelsWalls, 3);

unsigned int textureRoofs;
int widthRoofs, heightRoofs, nrChannelsRoofs;
unsigned char *dataRoofs = stbi_load("dachy.png", &widthRoofs, &heightRoofs, &nrChannelsRoofs, 3);

void loadTextureFloor()
{
  glGenTextures(1, &textureFloor);
  glBindTexture(GL_TEXTURE_2D, textureFloor);
  // set the texture wrapping/filtering options (on the currently bound texture object)

  // load and generate the texture
  if (dataFloor)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthFloor, heightFloor, 0, GL_RGB, GL_UNSIGNED_BYTE, dataFloor);
///      glGenerateMipmap(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
}

void loadTextureWalls()
{
  glGenTextures(1, &textureWalls);
  glBindTexture(GL_TEXTURE_2D, textureWalls);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  // load and generate the texture
  if (dataWalls)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthWalls, heightWalls, 0, GL_RGB, GL_UNSIGNED_BYTE, dataWalls);
///      glGenerateMipmap(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }
  else
  {
      std::cout << "Failed to load the texture" << std::endl;
  }
}

void loadTextureRoofs()
{
  glGenTextures(1, &textureRoofs);
  glBindTexture(GL_TEXTURE_2D, textureRoofs);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  // load and generate the texture
  if (dataRoofs)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthRoofs, heightRoofs, 0, GL_RGB, GL_UNSIGNED_BYTE, dataRoofs);
///      glGenerateMipmap(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
}

void loadTexture(char const *filename)
{
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
///      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
}

//Framebuffer size change event processing
void windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //Generate images in this resolution
	aspect=(float)width/(float)height; //Compute aspect ratio of width to height of the window
}

//Procedura obs³ugi b³êdów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura inicjuj¹ca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************

	glfwSetFramebufferSizeCallback(window, windowResize);//Zarejestruj procedurê obs³ugi zmiany rozmiaru ekranu.
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);

    glClearColor(0,0.87,0.87,1); //Ustaw kolor czyszczenia bufora kolorów na czarno
    glEnable(GL_LIGHTING); //W³¹cz cieniowanie
    // float lightPos[]={0.0, 0.0, 0.0, 1.0};
    float lightPos0[]={-1.0};
    float lightPos1[]={0.0};
    float lightPos2[]={0.4};
    float lightPos3[]={0.6};
    float lightPos4[]={0.8};
    float lightPos5[]={1.0};
    glLightfv(GL_LIGHT0,GL_CONSTANT_ATTENUATION,lightPos0);
    glLightfv(GL_LIGHT1,GL_CONSTANT_ATTENUATION,lightPos1);
    glLightfv(GL_LIGHT2,GL_CONSTANT_ATTENUATION,lightPos2);
    glLightfv(GL_LIGHT3,GL_CONSTANT_ATTENUATION,lightPos3);
    glLightfv(GL_LIGHT4,GL_CONSTANT_ATTENUATION,lightPos4);
    glLightfv(GL_LIGHT5,GL_CONSTANT_ATTENUATION,lightPos5);
    glEnable(GL_LIGHT0); //W³¹cz œwia³o numer 0
    glEnable(GL_LIGHT1); //W³¹cz œwia³o numer 0
    glEnable(GL_LIGHT2); //W³¹cz œwia³o numer 0
    glEnable(GL_LIGHT3); //W³¹cz œwia³o numer 0
    glEnable(GL_LIGHT4); //W³¹cz œwia³o numer 0
    glEnable(GL_LIGHT5); //W³¹cz œwia³o numer 0
    glEnable(GL_DEPTH_TEST); //W³¹cz bufor g³êbokoœci
    glEnable(GL_COLOR_MATERIAL); //W³¹cz ustawianie koloru materia³u przez polecenia glColor
    cameraPos   = glm::vec3(148.726f, 82.3851f, 148.632f);
    //cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    // glfwSetKeyCallback(window, processInput);

    for(int i=0,k=224; i<15; i++)
    {
        for(int j=14; j>=0; j--,k--)
        {
            highMatrix[i][j] = wysokosci[k];
        }
    }
    for(int i=0; i<15; i++)
    {
        for(int j=0; j<15; j++)
        {
            cout<<highMatrix[i][j]<<" ";
        }
        cout<<endl;
    }

}




//Procedura rysuj¹ca zawartoœæ sceny
void drawScene(GLFWwindow* window,float angle) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyœæ bufor kolorów i bufor g³êbokoœci

	//Przygotuj macierze rzutowania i widoku dla renderowanego obrazu
	mat4 P=perspective(50.0f*PI/180.0f, aspect, 1.0f, 50.0f); //Wylicz macierz rzutowania

	// mat4 V=lookAt( //Wylicz macierz widoku
	// vec3(50.0f,120.0f,50.0f),
	// vec3(0.0f,0.0f,0.0f),
	// vec3(0.0f,1.0f,0.0f));
	///cout<<cameraPos.x<<" "<<cameraPos.y<<" "<<cameraPos.z<<endl;
    if(!isJumping && cameraPos.y > highMatrix[(int)cameraPos.z/10][(int)cameraPos.x/10]+2)
        {
            cameraPos.y -= cameraSpeed;
            isFalling = true;
        }
        else
        {
            isFalling = false;
        }
    mat4 V=lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glMatrixMode(GL_PROJECTION); //W³¹cz tryb modyfikacji macierzy rzutowania
	glLoadMatrixf(value_ptr(P)); //Skopiuj macierz rzutowania
	glMatrixMode(GL_MODELVIEW); //W³¹cz tryb modyfikacji macierzy model-widok. UWAGA! Macierz ta bêdzie ³adowana przed narysowaniem ka¿dego modelu

    //Rysowanie pojedynczego modelu
    //1. Oblicz i za³aduj macierz modelu
	mat4 M=mat4(1.0f); //Wylicz macierz modelu
	// M=rotate(M,angle,vec3(0.0f,1.0f,0.0f));


	glLoadMatrixf(value_ptr(V*M)); //Za³aduj macierz model-widok
	//2. Narysuj obiekt
  // loadTexture("podloga.png");
  // loadTextureFloor();
///  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureFloor);
  glEnable(GL_TEXTURE_2D);
	Models::podloga.drawSolid();
  glDisable(GL_TEXTURE_2D);

  // loadTexture("dachy.png");
  // loadTextureRoofs();
///  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureRoofs);
  glEnable(GL_TEXTURE_2D);
	Models::dachy.drawSolid();
  glDisable(GL_TEXTURE_2D);

  // loadTexture("sciany.png");
  // loadTextureWalls();
///  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureWalls);
  glEnable(GL_TEXTURE_2D);
 Models::sciany.drawSolid();
  glDisable(GL_TEXTURE_2D);


  //mat4 macierzHelikoptera = M;
  //macierzHelikoptera = translate(macierzHelikoptera, vec3(50,90,50));
  //macierzHelikoptera = rotate(macierzHelikoptera, angle, vec3(0.0f, 1.0f, 0.0f));
  //macierzHelikoptera = translate(macierzHelikoptera, vec3(-10, 0, 0));
  //glLoadMatrixf(value_ptr(V*macierzHelikoptera)); //Za³aduj macierz model-widok
  //Models::helikopter.drawSolid();
	//Koniec
	glfwSwapBuffers(window);
}

int main(void)
{
	GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurê obs³ugi b³êdów

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1366, 768, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.


	if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	GLenum err;
	if ((err=glewInit()) != GLEW_OK) { //Zainicjuj bibliotekê GLEW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjuj¹ce

	float angle=0; //Aktualny k¹t obrotu obiektu
	glfwSetTime(0); //Wyzeruj licznik czasu
	//G³ówna pêtla
  loadTextureFloor();
  loadTextureRoofs();
  loadTextureWalls();
	while (!glfwWindowShouldClose(window)) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
        processInput(window);
	    //angle+=speed*glfwGetTime(); //Powiêksz k¹t obrotu o szybkoœæ obrotu razy czas, który min¹³ od poprzedniej klatki
	    glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window,angle); //Wykonaj procedurê rysuj¹c¹
		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}


  stbi_image_free(dataFloor);
  stbi_image_free(dataWalls);
  stbi_image_free(dataRoofs);

	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);
}
