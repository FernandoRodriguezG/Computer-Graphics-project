using namespace std;

class Ventana{
private:
	GLFWwindow* window; //Ventana
	arma::frowvec eye = {0.0, 0.0, 10.0}; //OJo de la camara, donde se coloca la camara
	arma::frowvec camera = {0.0, 0.0, 0.0}; // A donde apunta la camara
	arma::frowvec viewup = {0.0, 1.0, 0.0}; // Vector vista hacia arriba
	float ar;
	Model rocket;
	Model earth;
	void contexto();
	void proyecciones();
	void perspectivas();
	void elementos();
	void buffer();
	void dibujaModelos();
public:
	Ventana()=default;
	void inicializaVentana();
	void inicializaModelos();
	void dibujaEspacio();
	void terminate();
};
