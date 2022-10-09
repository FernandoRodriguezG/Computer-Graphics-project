using namespace std;

class Face{
private:	
	vector <Edge> edges;
	vector <int> indexVertex;
	vector <Vertex> vertices;
	arma::frowvec normal;
	void calculaNormal();
public:
	Face(vector <Edge> edgelist,vector <Vertex> auxVertex,vector <int> indexList);
	void imprimir();
	vector <int> getIndVex();
	vector <Vertex> getVerToFace();
};
