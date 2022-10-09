using namespace std;

class Model{
private:
	double angle,velocity; //ANgulo traslacion
	float r,g,b; //colores rgb
	float scale,tras; //DAtos necesarios para transformacion
	Object modelo; //OBJ
	int tipo; //0=tierra - 1=rocket
	Transform Tr = Transform(); //transformación
	arma::fmat trans; //su propia matriz de transformación
	vector <Vertex> pVertices; //vertices obj
	vector <Vertex> pVerTrans; //vertices transformados
	float t; //Avance para los puntos en la curva de bezier
	int band; //Bandera para terminar ejecución
	double xmax,ymax; //Alcance maximo tanto en horizontal como vertical
	arma::fmat mBezier = {{-1,3,-3,1}, //Matriz constante de BEzier
						  {3,-6,3,0},
						  {-3,3,0,0},
						  {1,0,0,0}};
	arma::drowvec P1,P2,P3,P4; //Puntos de control Bezier
	arma::drowvec curvaB(); //CAlculos curva de bezier
	void transVertex();
	void matTrans();
	void setVertObj();
	void initCurva();
public:
	Model(const char* file,float rp,float gp,float bp,float sca,float vel, float trasla,int type,double angle);
	Model() = default;
	void dibujado();
	int getBand();
};
