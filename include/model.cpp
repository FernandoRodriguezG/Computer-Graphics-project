#include <iostream>
#include <vector>
#include <armadillo>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "vertex.hpp"
#include "edge.hpp"
#include "face.hpp"
#include "object.hpp"
#include "Transform.hpp"
#include "model.hpp"

using namespace std;
//CONstructor de la clase model
Model::Model(const char* file,float rp,float gp,float bp,float sca,float vel, float trasla,int type,double angle){
	modelo = Object(file);
	modelo.leerObj();
	setVertObj();;
	r = rp;
	g = gp;
	b = bp;
	tipo = type;
	scale = sca;
	velocity = vel;
	tras = trasla;
	this->angle = angle;
	t = 0.0;
	if(tipo==1) //Si es el cohete, se calcula la curva
		initCurva();
	band = 0;
}

//Se obtienen los vertices del obj despues de la lectura
void Model::setVertObj(){
	//pVertices.clear();
	vector<Vertex>aux;
	vector <Face> pFace = modelo.getFace();
	for(unsigned int i = 0;i<pFace.size();i++){
		aux = pFace[i].getVerToFace();
		pVertices.insert(pVertices.end(),aux.begin(),aux.end());
	}
}

//Se hace el angulo de traslación y ademas segun el tipo, se calcula la matriz segun sea el caso
void Model::matTrans(){
	if(tipo==0){//earth
		angle = (angle < 360.0f) ? angle+velocity : 0.0f;
		trans = Tr.R(0.0f, 1.0f, 0.0f, angle) * Tr.T(0.0, tras, 0.0) * Tr.S(scale,scale,scale);
	}else if(tipo==1){//rocket
		float r;
		if(t<=0.55) //Según la posición se coloca el angulo para la trasnformación 
			r=-45;
		else
			r=-135;
		arma::drowvec bezier = curvaB();
		trans = Tr.T(bezier.at(0),bezier.at(1),0) * Tr.S(scale, scale, scale) * Tr.T(bezier.at(0),bezier.at(1),0)*
				Tr.R(0.0f, 0.0f, 1.0f, r) * Tr.T(0,0,0);
		t = t+0.01; //AUMento de t para calculo de bezier
		if(t>=1.05){ //BAndera para terminar el programa
			band = 1;
		}
	}
}

void Model::initCurva(){ //INcialización y creación de parametros de bezier
	double gravedad = 9.8; //GRavedad
	double anglerad = (angle*M_PI/180); //ANgulo a radianes
	xmax = (pow(velocity,2)*(2*sin(anglerad)*cos(anglerad)))/gravedad; //ALcance maximo horizontal
	ymax = (pow(velocity,2) * pow(sin(anglerad),2))/(2*gravedad); //ALcance maximo vertical
	P1 = {-1.7,-0.8,0}; //PUNTO INICIAL
	P2 = {xmax/4,ymax,0}; //PUNTO DE CONTROL 2
	P3 = {(xmax/4)*3,ymax,0}; //PUNTO DE CONTROL 3
	P4 = {xmax,-0.8,0}; // PUNTO FINAL

}

arma::drowvec Model::curvaB(){
	arma::dmat GB(4,3);
	GB.row(0) = P1;
	GB.row(1) = P2;
	GB.row(2) = P3;
	GB.row(3) = P4;
	arma::drowvec T = {powf(t,3),powf(t,2),t,1};
	arma::drowvec Qt = T * mBezier * GB;
	return(Qt);
}


void Model::transVertex(){ //TRansformacion de los vectores multiplicando la matriz por vector
	pVerTrans.clear();
	matTrans();
	for ( unsigned int i=0; i<pVertices.size(); i++ ) {
		arma::fcolvec v = pVertices[i].h();
		arma::fcolvec vp = trans * v;
		Vertex rv = Vertex();
		rv.setValue(arma::trans(vp));
		pVerTrans.push_back(rv);
	}
}

void Model::dibujado(){ //SE dibujan los triangulos de las figuras
	transVertex();
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for ( unsigned int i=0; i<pVerTrans.size(); i++ ) {
		if(tipo==0 && i>2500){
			glColor3f(r, b, g);
		}
		arma::frowvec vert = pVerTrans[i].getVec();
			glVertex3f(vert[0], vert[1], vert[2]);
	}
	glEnd();
}


int Model::getBand(){
	return band;
}
