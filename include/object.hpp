using namespace std;

class Object{
private:
	string nameFile;
	string nombre;
	vector <Vertex> vertexList;
	vector <Face> faceList;
	void split(const string& str, vector <string>& cont, char delim);
	int indexVertex(const string& cad);
public:
	Object() = default;
	Object (const char* file);
	void leerObj();
	void imprimirObj();
	vector <Face> getFace();
};
