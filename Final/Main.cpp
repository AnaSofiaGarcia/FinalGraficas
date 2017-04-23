#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <IL/il.h>
#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"

Camera _camera;
Ray _ray;
Sphere _sphere;

void Initialize() {
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
}