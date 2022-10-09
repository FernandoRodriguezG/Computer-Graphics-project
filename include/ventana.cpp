#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "include/vertex.hpp"
#include "include/edge.hpp"
#include "include/face.hpp"
#include "include/object.hpp"
#include "include/Transform.hpp"
#include "include/model.hpp"
#include "include/ventana.hpp"

void Ventana::inicializaVentana(){ //Inicialización de la ventana y creación
	if( !glfwInit() ){
		fprintf( stderr, "Fallo al inicializar GLFW\n" );
		getchar();
	}
	window = glfwCreateWindow(1375, 700, "Un viaje al espacio",NULL, NULL);
	if( window == NULL ) {
		fprintf( stderr, "Fallo al abrir la ventana de GLFW.\n" );
		getchar();
		glfwTerminate();
	}
	contexto();
	proyecciones();
}

void Ventana::contexto(){ //Se pone contexto a la ventana
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Ventana::proyecciones(){ //Se colocan las proyecciones de la ventana
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ar = width / height;
	//Proyección en paralelo
	glViewport(0, 0, width, height);
	glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);
	//Proyección en perspectiva
	//glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Ventana::perspectivas(){ //Función para cambiar las ventanas según se presionen teclas
	if(glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS){ //Flecha izquierda - Vista desde y=15
		eye[0]=0.0;
		eye[1]=15.0;
		eye[2]=0.0;
		viewup[0]=0.0;
		viewup[1]=0.0;
		viewup[2]=1.0;
	}
	if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS){//Flecha derecha - Vista desde Z = 10
		eye[0]=0.0;
		eye[1]=0.0;
		eye[2]=10.0;
		viewup[0]=0.0;
		viewup[1]=1.0;
		viewup[2]=0.0;
	}
	if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS){ //Flecha abajo - Vista esquinada 10/10/10
		eye[0]=10.0;
		eye[1]=10.0;
		eye[2]=10.0;
		viewup[0]=0.0;
		viewup[1]=1.0;
		viewup[2]=0.0;
	}
}

void Ventana::elementos(){
	glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], 
			camera[0], camera[1], camera[2], 
			viewup[0], viewup[1], viewup[2]);
}

void Ventana::buffer(){
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Ventana::terminate(){
	glfwTerminate();
}


void Ventana::inicializaModelos(){
	double vel,angle;
	//PEdir al usuario los valores de angulo y velocidad inicial, por ahora se leeran por teclado
	cout<<"Por favor, ingrese la velocidad inicial del cohete: "<<endl;
	cin>>vel;
	cout<<"AHora, ingrese el angulo de salida del cohete"<<endl;
	cin>>angle;
			//const char* file,	float rp,float gp,float bp,		float sca,float vel, float trasla,	int type
	earth = Model("models/Earth.obj",0.0,0.0,1.0,	0.3,1.0,-0.7,	0,	0.0);
	rocket = Model("models/Rocket.obj",1.0,0.0,0.0, 	0.1,vel,1.0,	1,	angle);

}

void Ventana::dibujaModelos(){ 
		earth.dibujado();
		rocket.dibujado();
}

void Ventana::dibujaEspacio(){
	int b;
	do{
		perspectivas();
		elementos();
		dibujaModelos();
		buffer();	
		b = rocket.getBand();
	}while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0 && b != 1);
}
