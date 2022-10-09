/*
RODRIGUEZ GONZALEZ FERNANDO DE JESUS
GRAFICACIÓN POR COMPUTADORA 9-10AM
3 DE ENERO DE 2021
SISTEMA SOLAR
*/

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

int main( void )
{
	Ventana window = Ventana(); //Constructor de la clase Ventana
	window.inicializaVentana(); //Inicialización de la ventana y elementos
	window.inicializaModelos();
	window.dibujaEspacio(); //Dibujado de la pantalla
	window.terminate();
	return 0;
}


