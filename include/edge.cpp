#include <iostream>
#include <armadillo>
#include "vertex.hpp"
#include "edge.hpp"

using namespace std;

Edge::Edge(Vertex va,Vertex vb){
	vi = va;
	vf = vb;
}

void Edge::imprimir(){
	cout<<"Vector inicial:"; vi.imprimir();
	cout<<"Vector final:"; vf.imprimir();
}
