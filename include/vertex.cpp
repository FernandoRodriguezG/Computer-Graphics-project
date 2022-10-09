#include <iostream>
#include <armadillo>
#include "vertex.hpp"


using namespace std;

Vertex::Vertex () {
	vex = {0.0, 0.0, 0.0};
}

Vertex::Vertex(float xi,float yi,float zi) {
	vex = {xi,yi,zi};
}

Vertex::Vertex(arma::frowvec verx) {
	vex = verx;
}

void Vertex::setValue(arma::frowvec verx) {
	vex = verx;
}

arma::frowvec Vertex::getVec(){
	return vex;
}

arma::fcolvec Vertex::h(){
	arma::fcolvec h = {{vex[0]},{vex[1]},{vex[2]},{1.0}};

	return(h);
}

void Vertex::imprimir() {
	cout << vex;
}
