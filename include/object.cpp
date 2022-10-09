#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <iterator>
#include <armadillo>
#include <sstream>
#include <fstream>
#include "vertex.hpp"
#include "edge.hpp"
#include "face.hpp"
#include "object.hpp"

using namespace std;

void Object::split(const string& str, vector <string>& cont, char delim)
{
	size_t current=0,previous=0;
	while((previous=str.find(delim,current)) != string::npos){
		if(str[current] != delim)
			cont.push_back(str.substr(current,previous-current));
		current = previous+1;
	}
	cont.push_back(str.substr(current));
}

Object::Object(const char* file){
	nameFile = file;
	nombre = file;
}

int Object::indexVertex(const string& cad){
	vector <string> cadena;
	split(cad,cadena,'/');
	int aux = stoi(cadena[0])-1;
	return(aux);
}

void Object::leerObj(){
	string linea;
	ifstream archivoOBJ(nameFile);
	while (getline (archivoOBJ, linea)){
		vector <string> elementos;
		split(linea,elementos,' ');
		if(!strcmp(elementos[0].c_str(), "g" )){
			nombre = elementos[1];
		}
		if(!strcmp(elementos[0].c_str(), "v" )){
			float x = stof(elementos[1]);
			float y = stof(elementos[2]);
			float z = stof(elementos[3]);
			Vertex v = Vertex(x,y,z);
			vertexList.push_back(v);
		}
		if(!strcmp(elementos[0].c_str(), "f" )){
			int inVer1 = indexVertex(elementos[1]);
			int inVer2 = indexVertex(elementos[2]);
			int inVer3 = indexVertex(elementos[3]);
			vector <int> indVertex = {inVer1,inVer2,inVer3};
			vector <Vertex> auxVertex ={vertexList[inVer1],vertexList[inVer2],vertexList[inVer3]};
			Edge E1 = Edge(vertexList[inVer1],vertexList[inVer2]);
			Edge E2 = Edge(vertexList[inVer2],vertexList[inVer3]);
			Edge E3 = Edge(vertexList[inVer3],vertexList[inVer1]);
			vector <Edge> eList = {E1,E2,E3};
			Face f = Face(eList,auxVertex,indVertex);
			faceList.push_back(f);
		}
	}
	archivoOBJ.close();
}

vector <Face> Object::getFace(){
	return (faceList);
}

void Object::imprimirObj(){
	int i;
	cout << "OBJ a imprimir: " << nombre << endl;
	cout << "Vertices: " << endl;
	for(i=0;i<vertexList.size();i++){
		cout << "Vertice #" << i+1;
		vertexList[i].imprimir();
	}
	cout << endl;
	cout << "Caras: " << endl;
	for(i=0;i<faceList.size();i++){
		cout << "Face #" << i+1;
		faceList[i].imprimir();
	}
	cout<<endl;
	/*cout << "Normales: " << endl;
	for(i=0;i<faceList.size();i++){
		cout << "Face #" << i+1;
		normales[i].imprimir();
	}*/
}
