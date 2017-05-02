#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <IL/il.h>

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Transform.h"


#include "Ray.h"
#include "Line.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Sphere.h"
#include "GeometricObject.h"
#include "Plane.h"
#include "Source.h"

using namespace std;

float Time;
Mesh _mesh;
ShaderProgram _shaderProgram;
Transform _transform;
Camera _camara;
Texture2D _raytracing;

struct RGBType {
	double r;
	double g;
	double b;
};

void savebmp(const char *filename, int w, int h, int dpi, RGBType *data) {
	FILE *f;
	int k = w*h;
	int s = 4 * k;
	int filesize = 54 + s;
	double factor = 39.375;
	int m = static_cast<int>(factor);
	int ppm = dpi*m;
	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i< k; i++) {
		RGBType rgb = data[i];

		double red = (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue = (data[i].b) * 255;

		unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red) };
		fwrite(color, 1, 3, f);
	}
	fclose(f);


}

int winningObjectIndex(vector<double> objectIntersections) {
	int minimumValue;
	if (objectIntersections.size() == 0) {
		return -1;
	}
	else if (objectIntersections.size() == 1) {
		if (objectIntersections.at(0) > 0) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		double max = 0;
		for (int i = 0; i <objectIntersections.size(); i++) {
			if (max < objectIntersections.at(i)) {
				max = objectIntersections.at(i);

			}
		}
		if (max > 0) {
			for (int index = 0; index<objectIntersections.size(); index++) {
				if (objectIntersections.at(index)>0 && objectIntersections.at(index) <= max) {
					max = objectIntersections.at(index);
					minimumValue = index;
				}
			}
			return minimumValue;
		}
		else {
			return -1;
		}
	}
}

Color getColorAt(Ray intersectionPosition, Ray intersectLineDirection, vector<GeometricObject*> sceneObjects, int indexObject, vector<Source*> lightSources, double accuracy, double ambientLight) {
	Color objColor = sceneObjects.at(indexObject)->getColor();
	Ray objectNormal = sceneObjects.at(indexObject)->getNormalAt(intersectionPosition);
	if (objColor.getColorSpecial() == 2) {
		int square = (int)floor(intersectionPosition.getRayX()) + (int)floor(intersectionPosition.getRayZ());
		if ((square % 2) == 0) {
			objColor.setColorRed(0);
			objColor.setColorGreen(0);
			objColor.setColorBlue(0);
		}
		else {
			objColor.setColorRed(1);
			objColor.setColorGreen(1);
			objColor.setColorBlue(1);
		}
	}

	Color finalColor = objColor.colorScalar(ambientLight);

	if (objColor.getColorSpecial() > 0 && objColor.getColorSpecial() <= 1) {

		double dot1 = objectNormal.dotProduct(intersectLineDirection.negative());
		Ray scalar1 = objectNormal.multRay(dot1);
		Ray add1 = scalar1.addRay(intersectLineDirection);
		Ray scalar2 = add1.multRay(2);
		Ray add2 = intersectLineDirection.negative().addRay(scalar2);
		Ray reflectionDirection = add2.normalize();
		Line reflectionLine(intersectionPosition, reflectionDirection);

		vector<double> reflectionIntersections;
		for (int reflection_index = 0; reflection_index<sceneObjects.size(); reflection_index++) {
			reflectionIntersections.push_back(sceneObjects.at(reflection_index)->findIntersection(reflectionLine));

		}
		int indexObjectReflection = winningObjectIndex(reflectionIntersections);

		if (indexObjectReflection != -1) {
			if (reflectionIntersections.at(indexObjectReflection) > accuracy) {
				Ray intersection_Position = intersectionPosition.addRay(reflectionDirection.multRay(reflectionIntersections.at(indexObjectReflection)));
				Ray intersection_linedirection = reflectionDirection;

				Color intersectionColor = getColorAt(intersection_Position, intersection_linedirection, sceneObjects, indexObjectReflection, lightSources, accuracy, ambientLight);

				finalColor = finalColor.colorAdd(intersectionColor.colorScalar(objColor.getColorSpecial()));

			}
		}
	}

	for (int lightIndex = 0; lightIndex <lightSources.size(); lightIndex++) {
		Ray lightDirection = lightSources.at(lightIndex)->getLightPosition().addRay(intersectionPosition.negative()).normalize();
		float cosineAngle = objectNormal.dotProduct(lightDirection);

		if (cosineAngle >0) {
			bool shadowed = false;
			Ray lightDistance = lightSources.at(lightIndex)->getLightPosition().addRay(intersectionPosition.negative()).normalize();
			float lightDistanceMagnitude = lightDistance.magnitude();

			Line shadowLine(intersectionPosition, lightSources.at(lightIndex)->getLightPosition().addRay(intersectionPosition.negative()).normalize());

			vector<double>secondaryIntersections;

			for (int objectIndex = 0; objectIndex<sceneObjects.size() && shadowed == false; objectIndex++) {
				secondaryIntersections.push_back(sceneObjects.at(objectIndex)->findIntersection(shadowLine));
			}
			for (int c = 0; c < secondaryIntersections.size(); c++) {
				if (secondaryIntersections.at(c) > accuracy) {
					if (secondaryIntersections.at(c) <= lightDistanceMagnitude) {
						shadowed = true;

					}
					break;
				}
			}
			if (shadowed == false) {
				finalColor = finalColor.colorAdd(objColor.colorMultiply(lightSources.at(lightIndex)->getLightColor()).colorScalar(cosineAngle));
				if (objColor.getColorSpecial() > 0 && objColor.getColorSpecial() <= 1) {
					double dot1 = objectNormal.dotProduct(intersectLineDirection.negative());
					Ray scalar1 = objectNormal.multRay(dot1);
					Ray add1 = scalar1.addRay(intersectLineDirection);
					Ray scalar2 = add1.multRay(2);
					Ray add2 = intersectLineDirection.negative().addRay(scalar2);
					Ray reflectionDirection = add2.normalize();

					double specular = reflectionDirection.dotProduct(lightDirection);
					if (specular > 0) {
						specular = pow(specular, 10);
						finalColor = finalColor.colorAdd(lightSources.at(lightIndex)->getLightColor().colorScalar(specular * objColor.getColorSpecial()));
					}
				}
			}
		}
	}
	return finalColor.clip();
}

void doInit() {

}

void Initialize() 
{
	Time = 0;
	std::vector<glm::vec3> positions;
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));



	std::vector<glm::vec2> texCoords;
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));
	

	std::vector<unsigned int> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);

	_mesh.CreateMesh(4);
	_mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_mesh.SetTexCoordAttribute(texCoords, GL_STATIC_DRAW, 1);
	_mesh.SetIndices(indices, GL_STATIC_DRAW);

	_shaderProgram.CreateProgram();
	_shaderProgram.Activate();
	_shaderProgram.AttachShader("DefaultTexture.vert", GL_VERTEX_SHADER);
	_shaderProgram.AttachShader("DefaultTexture.frag", GL_FRAGMENT_SHADER);
	_shaderProgram.SetAttribute(0, "VertexPosition");
	_shaderProgram.SetAttribute(1, "VertexTexCoord");
	_shaderProgram.LinkProgram();
	_shaderProgram.Deactivate();


	_raytracing.LoadTexture("RayTracing.bmp");
	
	_camara.SetPerspective(1.0f, 1000.0f, 60.0f, 1.0f);
	_camara.SetPosition(0.0f, 0.0f, -2.7f);

	_shaderProgram.Activate();
	_shaderProgram.SetUniformi("DiffuseTexture", 0);
	_shaderProgram.Deactivate();
}

void Idle() {
	glutPostRedisplay();
}

void GameLoop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Time += 0.05f;
	if (Time >= 360)
		Time = 0;
	//_camara.SetOrthographic(3.0f, 4.0f / 3.0f);
	_shaderProgram.Activate();
	glActiveTexture(GL_TEXTURE0);
	_raytracing.Bind();

    _shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camara.GetViewProjection() * _transform.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);

	_raytracing.Unbind();
	_shaderProgram.Deactivate();

	// Cambiar el buffer actual.
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
		_camara.MoveForward(0.1f, false);
	if (key == 's')
		_camara.MoveForward(-0.1f, false);
	if (key == 'd')
		_camara.MoveRight(0.1f, false);
	if (key == 'a')
		_camara.MoveRight(-0.1f, false);
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		_transform.MoveForward(0.1f, true);
	if (key == GLUT_KEY_DOWN)
		_transform.MoveForward(-0.1f, true);
	if (key == GLUT_KEY_RIGHT)
		_transform.MoveRight(0.1f, true);
	if (key == GLUT_KEY_LEFT)
		_transform.MoveRight(-0.1f, true);
}

/*void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	_camara.SetPerspective(1.0f, 1000.0f, 60.0f,
	(float)width / (float)height);
}*/

int thisone;
int main(int argc, char *argv[]) {
	cout << "Cargando . . ." << endl;

	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width*height;

	RGBType *pixels = new RGBType[n];

	double aspectRatio = (double)width / (double)height;

	double ambientLight = 0.1;
	double accuracy = 0.00001;

	Ray O(0, 0, 0);
	Ray X(1, 0, 0);
	Ray Y(0, 1, 0);
	Ray Z(0, 0, 1);

	Ray newSphereLocation(5, 0, 1);
	Ray newSphereLocation2(0, 1, 1);
	Ray newSphereLocation3(-5, 3, -1);
	Ray newSphereLocation4(-5, 1, 0);


	Ray campos(0, 2, -10);
	Ray look_at(0, 0, 0);
	Ray diff_btw(campos.getRayX() - look_at.getRayX(), campos.getRayY() - look_at.getRayY(), campos.getRayZ() - look_at.getRayZ());

	Ray camdir = diff_btw.negative().normalize();
	Ray camright = Y.crossProduct(camdir).normalize();
	Ray camdown = camright.crossProduct(camdir);
	Camera sceneCam(campos, camdir, camright, camdown);

	////////////////////////////////////////Colores////////////////////////////////////////
	Color light(1.0, 1.0, 1.0, 0);

	Color red(1.0, 0, 0, 0.2);
	Color green(0, 1.0, 0, 0.1);
	Color blue(0, 0, 1.0, 0);

	Color yellow(1.0, 1.0, 0, 1);

	Color lightBlue(0.2, 1.0, 0.9, 0.5);
	Color pink(1.0, 0.1, 0.6, 0.5);
	Color orange(1.0, 0.6, 0, 0.6);

	////////////////////////////////////////Luz////////////////////////////////////////
	Ray lightPosition(0, 30, 10);
	Light lightScene(lightPosition, light);
	vector <Source*> lightSources;
	lightSources.push_back(dynamic_cast<Source*>(&lightScene));



	////////////////////////////////////////Objetos////////////////////////////////////////
	Sphere sphere(newSphereLocation, 1, pink);
	Sphere sphere2(newSphereLocation2, 2, lightBlue);
	Sphere sphere3(newSphereLocation3, 0.5, green);
	Sphere sphere4(newSphereLocation4, 1.5, orange);

	Plane plane(Y, -1, red);
	Plane plane2(X, -5, blue);
	Plane plane3(Z, 10, green);


	vector <GeometricObject*> sceneObjects;
	sceneObjects.push_back(dynamic_cast<GeometricObject*>(&sphere));
	sceneObjects.push_back(dynamic_cast<GeometricObject*>(&sphere2));
	sceneObjects.push_back(dynamic_cast<GeometricObject*>(&sphere3));
	sceneObjects.push_back(dynamic_cast<GeometricObject*>(&sphere4));
	sceneObjects.push_back(dynamic_cast<GeometricObject*>(&plane));
	sceneObjects.push_back(dynamic_cast<GeometricObject*>(&plane2));
	sceneObjects.push_back(dynamic_cast<GeometricObject*>(&plane3));


	double Xamnt, Yamnt;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			thisone = y * width + x;


			if (width>height) {
				Xamnt = ((x + 0.5) / width) * aspectRatio - (((width - height) / (double)height) / 2);
				Yamnt = ((height - y) + 0.5) / height;
			}
			else if (height > width) {
				Xamnt = (x + 0.5) / width;
				Yamnt = (((height - y) + 0.5) / height) / aspectRatio - (((height - width) / (double)width) / 2);
			}
			else {
				Xamnt = (x + 0.5) / width;
				Yamnt = ((height - y) + 0.5) / height;
			}
			Ray camOrigin = sceneCam.getCameraPosition();
			Ray camDirection = camdir.addRay(camright.multRay(Xamnt - 0.5).addRay(camdown.multRay(Yamnt - 0.5))).normalize();
			Line cam_linea(camOrigin, camDirection);
			vector <double> intersections;
			for (int index = 0; index<sceneObjects.size(); index++) {
				intersections.push_back(sceneObjects.at(index)->findIntersection(cam_linea));
			}
			int indexObject = winningObjectIndex(intersections);



			if (indexObject == -1) {

				pixels[thisone].r = 0;
				pixels[thisone].g = 0;
				pixels[thisone].b = 0;

			}
			else {
				if (intersections.at(indexObject)> accuracy) {
					Ray intersection_position = camOrigin.addRay(camDirection.multRay(intersections.at(indexObject)));
					Ray intersecting_line_direction = camDirection;

					Color intersection_color = getColorAt(intersection_position, intersecting_line_direction, sceneObjects, indexObject, lightSources, accuracy, ambientLight);

					pixels[thisone].r = intersection_color.getColorRed();
					pixels[thisone].g = intersection_color.getColorGreen();
					pixels[thisone].b = intersection_color.getColorBlue();
				}
			}
		}
	}
	savebmp("RayTracing.bmp", width, height, dpi, pixels);
	system("pause");

	//OpenGL 
	// Inicialización de Freeglut.
	// Freeglut se encarga de crear una ventana
	// En donde vamos a poder dibujar
	glutInit(&argc, argv);
	// Freeglut es el encargado de solicitar un contexto
	// de OpenGL. El contexto se refiere a las capacidades
	// que va a tener nuestra aplicación gráfica.
	glutInitContextVersion(4, 4);
	// Tenemos que informar que queremos trabajar únicamente con
	// el pipeline programable
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// Freeglut nos permite configurar eventos que ocurren en la venta.
	// Un evento que nos interesa es cuando alguien cierra la venta.
	// En este caso simplemente dejamos de renderear y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Configuramos el framebuffer. En este caso estamos solicitando
	// un buffer true color RGBA, un buffer de profundidad y un segundo buffer
	// para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	// Le damos un nombre a la ventana y la creamos.
	glutCreateWindow("Hell World GL");
	// Asociamos una funcion de render. Esta función se
	// mandará a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);

	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
	//glutReshapeFunc(ReshapeWindow);

	// Inicializar GLEW. Esta librería se encarga
	// de obtener el API de OpenGL de nuestra tarjeta
	// de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configuramos OpenGL. Este es el color
	// por default del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//glDisable(GL_PROGRAM_POINT_SIZE);
	//glPointSize(5);

	// Inicializar DevIL
	ilInit(); // Inicializamos la librería y sus recursos
	ilEnable(IL_ORIGIN_SET); // Le decimos que queremos cambiar
							 // el punto de origen
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT); // Cambiarlo y configurarlo
										// como abajo a la izquerda. Hace match con las
										// coordenadas de textura.

	Initialize();

	// Iniciar la aplicación. El main se pausará en esta
	// línea hasta que se cierre la ventana de OpenGL.
	glutMainLoop();

	// Terminar.
	return 0;
}