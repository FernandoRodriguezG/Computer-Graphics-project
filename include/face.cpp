#include <iostream>
#include <vector>
#include <armadillo>
#include "vertex.hpp"
#include "edge.hpp"
#include "face.hpp"

using namespace std;

Face::Face(vector <Edge> edgelist,vector <Vertex> auxVertex,vector <int> indexList){
	edges = edgelist;
	vertices = auxVertex;
	indexVertex = indexList;
	calculaNormal();
}

void Face::imprimir(){
	cout << " Formada por los vertices:"<<endl;
	for(int i=0;i<indexVertex.size();i++){
		cout << indexVertex[i]+1 << " " ;
	}
	cout<<endl;
	cout << "Aristas de la cara:"<<endl;;
	for(int i=0;i<edges.size();i++){
		edges[i].imprimir();
		cout << endl;
	}
	cout<<endl;
	cout << "Normales de la cara:"<<endl;
		cout<< normal << endl;
}

vector <int> Face::getIndVex(){
	return (indexVertex);
}

vector <Vertex> Face::getVerToFace(){
	return (vertices);
}

void Face::calculaNormal(){
	normal = arma::cross(vertices[1].getVec()-vertices[0].getVec(),
					vertices[2].getVec()-vertices[0].getVec());
}

