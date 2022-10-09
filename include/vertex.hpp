class Vertex {
private:
	arma::frowvec vex;
public:
	Vertex();
	Vertex(float xi,float yi,float zi);
	Vertex(arma::frowvec verx);
	arma::frowvec getVec();
	void imprimir();
	arma::fcolvec h();
	void setValue(arma::frowvec verx); 
};
