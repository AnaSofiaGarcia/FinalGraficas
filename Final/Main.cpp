//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <glm/glm.hpp>
//#include <IL/il.h>

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

/*void Initialize() {
	for (int j = 0; j <= 1080; j++) {
		for (int i = 0; i <= 720; i++) {
			_ray.CreatRay(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 5.0f));

			if(//sphere intersect)
		}
	}
}

void GameLoop()
{
	// Siempre es recomendable borrar la información anterior del framebuffer.
	// En este caso estamos borrando la información de color,
	// y la información de profundidad.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//_shaderProgram.SetUniformf("iGlobalTime", time);
	//_transform.SetRotation(0.0f, 0.0f, time);
	_camera.SetOrthographic(3.0f, 4.0f / 3.0f);
	// Cambiar el buffer actual.
	glutSwapBuffers();
}

void Idle()
{
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
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
	glutInitWindowSize(1080, 720);
	// Le damos un nombre a la ventana y la creamos.
	glutCreateWindow("Hello World GL");
	// Asociamos una funcion de render. Esta función se
	// mandará a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);
	glutIdleFunc(Idle);

	// Inicializar GLEW. Esta librería se encarga
	// de obtener el API de OpenGL de nuestra tarjeta
	// de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configuramos OpenGL. Este es el color
	// por default del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//Inicializar DevIL
	ilInit();
	ilEnable(IL_ORIGIN_SET);//cambiar punto de origen
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);//cambia a abajo a la izquierda para hcer match
									   //con las coordenadas de texturas


	Initialize();

	// Iniciar la aplicación. El main se pausará en esta
	// línea hasta que se cierre la ventana de OpenGL.
	glutMainLoop();

	// Terminar.
	return 0;
}*/

int thisone;
int main(int argc, char *argv[]) {
	cout << "Please wait..." << endl;

	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width*height;

	RGBType *pixels = new RGBType[n];

	double aspectratio = (double)width / (double)height;

	double ambientlight = 0.2;
	double accuracy = 0.00001;

	Ray O(0, 0, 0);
	Ray X(1, 0, 0);
	Ray Y(0, 1, 0);
	Ray Z(0, 0, 1);

	Ray new_sphere_location(2, 0, 1);
	Ray new_sphere_location2(-3, 0.75, -1);


	Ray campos(3, 1.5, -4);
	Ray look_at(0, 0, 0);
	Ray diff_btw(campos.getRayX() - look_at.getRayX(), campos.getRayY() - look_at.getRayY(), campos.getRayZ() - look_at.getRayZ());

	Ray camdir = diff_btw.negative().normalize();
	Ray camright = Y.crossProduct(camdir).normalize();
	Ray camdown = camright.crossProduct(camdir);
	Camera scene_cam(campos, camdir, camright, camdown);

	Color white_luz(1.0, 1.0, 1.0, 0);
	Color pretty_green(0.5, 1.0, 0.5, 0.3);
	Color maroon(1.0, 1.0, 1.0, 0.3);
	Color rey(0.5, 0.5, 1.0, 0.3);
	Color aje(0.24, 0.85, 0.35, 2);
	Color gray(0.5, 0.5, 0.75, 0);
	Color black(0.0, 0.0, 0.0, 0);
	Ray luz_position(-7, 30, -10);
	Light scene_luz(luz_position, white_luz);
	vector <Source*> luz_sources;
	luz_sources.push_back(dynamic_cast<Source*>(&scene_luz));

	Sphere scene_sphere(O, 0.95, rey);
	Sphere scene_sphere2(new_sphere_location, 1, gray);
	Sphere scene_sphere3(new_sphere_location2, 0.65, maroon);
	Plane scene_plano(Y, -1, aje);
	vector <GeometricObject*> scene_objects;
	scene_objects.push_back(dynamic_cast<GeometricObject*>(&scene_sphere));
	scene_objects.push_back(dynamic_cast<GeometricObject*>(&scene_sphere2));
	scene_objects.push_back(dynamic_cast<GeometricObject*>(&scene_sphere3));
	scene_objects.push_back(dynamic_cast<GeometricObject*>(&scene_plano));
	double xamnt, yamnt;

	for (int x = 0; x< width; x++) {
		for (int y = 0; y < height; y++) {
			thisone = y*width + x;


			if (width>height) {
				xamnt = ((x + 0.5) / width)*aspectratio - (((width - height) / (double)height) / 2);
				yamnt = ((height - y) + 0.5) / height;
			}
			else if (height > width) {
				xamnt = (x + 0.5) / width;
				yamnt = (((height - y) + 0.5) / height) / aspectratio - (((height - width) / (double)width) / 2);
			}
			else {
				xamnt = (x + 0.5) / width;
				yamnt = ((height - y) + 0.5) / height;
			}
			Ray cam_linea_origin = scene_cam.getCameraPosition();
			Ray cam_linea_direction = camdir.addRay(camright.multRay(xamnt - 0.5).addRay(camdown.multRay(yamnt - 0.5))).normalize();
			Line cam_linea(cam_linea_origin, cam_linea_direction);
			vector <double> intersections;
			for (int index = 0; index<scene_objects.size(); index++) {
				intersections.push_back(scene_objects.at(index)->findIntersection(cam_linea));
			}
			int index_w_object = winningObjectIndex(intersections);



			if (index_w_object == -1) {

				pixels[thisone].r = 0;
				pixels[thisone].g = 0;
				pixels[thisone].b = 0;

			}
			else {
				if (intersections.at(index_w_object)> accuracy) {
					Ray intersection_position = cam_linea_origin.addRay(cam_linea_direction.multRay(intersections.at(index_w_object)));
					Ray intersecting_linea_direction = cam_linea_direction;

					Color intersection_color = getColorAt(intersection_position, intersecting_linea_direction, scene_objects, index_w_object, luz_sources, accuracy, ambientlight);

					pixels[thisone].r = intersection_color.getColorRed();
					pixels[thisone].g = intersection_color.getColorGreen();
					pixels[thisone].b = intersection_color.getColorBlue();
				}
			}
		}
	}
	savebmp("scene.bmp", width, height, dpi, pixels);
	system("pause");
	return 0;
}

Color getColorAt(Ray intersection_position, Ray intersecting_linea_direction, vector<GeometricObject*> scene_objects, int index_w_object, vector<Source*> luz_sources, double accuracy, double ambientlight) {
	Color w_obj_color = scene_objects.at(index_w_object)->getColor();
	Ray winning_object_normal = scene_objects.at(index_w_object)->getNormal(intersection_position);
	if (w_obj_color.getColorAlpha() == 2) {
		int square = (int)floor(intersection_position.getRayX()) + (int)floor(intersection_position.getRayZ());
		if ((square % 2) == 0) {
			w_obj_color.setColorRed(0);
			w_obj_color.setColorGreen(0);
			w_obj_color.setColorBlue(0);
		}
		else {
			w_obj_color.setColorRed(1);
			w_obj_color.setColorGreen(1);
			w_obj_color.setColorBlue(1);
		}
	}




	Color final_color = w_obj_color.colorScalar(ambientlight);

	if (w_obj_color.getColorAlpha()>0 && w_obj_color.getColorAlpha() <= 1) {

		double dot1 = winning_object_normal.dotProduct(intersecting_linea_direction.negative());
		Ray scalar1 = winning_object_normal.multRay(dot1);
		Ray add1 = scalar1.addRay(intersecting_linea_direction);
		Ray scalar2 = add1.multRay(2);
		Ray add2 = intersecting_linea_direction.negative().addRay(scalar2);
		Ray reflection_direction = add2.normalize();
		Line reflection_linea(intersection_position, reflection_direction);

		vector<double> reflection_intersections;
		for (int reflection_index = 0; reflection_index<scene_objects.size(); reflection_index++) {
			reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_linea));

		}
		int index_w_object_with_reflection = winningObjectIndex(reflection_intersections);

		if (index_w_object_with_reflection != -1) {
			if (reflection_intersections.at(index_w_object_with_reflection) > accuracy) {
				Ray reflection_intersection_position = intersection_position.addRay(reflection_direction.multRay(reflection_intersections.at(index_w_object_with_reflection)));
				Ray reflection_intersection_linea_direction = reflection_direction;

				Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_linea_direction, scene_objects, index_w_object_with_reflection, luz_sources, accuracy, ambientlight);

				final_color = final_color.colorAdd(reflection_intersection_color.colorScalar(w_obj_color.getColorAlpha()));

			}
		}
	}

	for (int luz_index = 0; luz_index <luz_sources.size(); luz_index++) {
		Ray luz_direction = luz_sources.at(luz_index)->getLightPosition().addRay(intersection_position.negative()).normalize();
		float cosine_angle = winning_object_normal.dotProduct(luz_direction);

		if (cosine_angle >0) {
			bool shadowed = false;
			Ray distance_to_luz = luz_sources.at(luz_index)->getLightPosition().addRay(intersection_position.negative()).normalize();
			float distance_to_luz_magnitude = distance_to_luz.magnitude();

			Line shadow_linea(intersection_position, luz_sources.at(luz_index)->getLightPosition().addRay(intersection_position.negative()).normalize());

			vector<double>secondary_intersections;

			for (int object_index = 0; object_index<scene_objects.size() && shadowed == false; object_index++) {
				secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_linea));
			}
			for (int c = 0; c < secondary_intersections.size(); c++) {
				if (secondary_intersections.at(c) > accuracy) {
					if (secondary_intersections.at(c) <= distance_to_luz_magnitude) {
						shadowed = true;

					}
					break;
				}
			}
			if (shadowed == false) {
				final_color = final_color.colorAdd(w_obj_color.colorMultiply(luz_sources.at(luz_index)->getLightColor()).colorScalar(cosine_angle));
				if (w_obj_color.getColorAlpha()>0 && w_obj_color.getColorAlpha() <= 1) {
					double dot1 = winning_object_normal.dotProduct(intersecting_linea_direction.negative());
					Ray scalar1 = winning_object_normal.multRay(dot1);
					Ray add1 = scalar1.addRay(intersecting_linea_direction);
					Ray scalar2 = add1.multRay(2);
					Ray add2 = intersecting_linea_direction.negative().addRay(scalar2);
					Ray reflection_direction = add2.normalize();

					double specular = reflection_direction.dotProduct(luz_direction);
					if (specular > 0) {
						specular = pow(specular, 10);
						final_color = final_color.colorAdd(luz_sources.at(luz_index)->getLightColor().colorScalar(specular*w_obj_color.getColorAlpha()));
					}
				}
			}
		}
	}
	return final_color.clip();
}

int winningObjectIndex(vector<double> object_intersections) {
	int index_of_minimum_value;
	if (object_intersections.size() == 0) {
		return -1;
	}
	else if (object_intersections.size() == 1) {
		if (object_intersections.at(0)>0) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		double max = 0;
		for (int i = 0; i <object_intersections.size(); i++) {
			if (max < object_intersections.at(i)) {
				max = object_intersections.at(i);

			}
		}
		if (max>0) {
			for (int index = 0; index<object_intersections.size(); index++) {
				if (object_intersections.at(index)>0 && object_intersections.at(index) <= max) {
					max = object_intersections.at(index);
					index_of_minimum_value = index;
				}
			}
			return index_of_minimum_value;
		}
		else {
			return -1;
		}
	}
}

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