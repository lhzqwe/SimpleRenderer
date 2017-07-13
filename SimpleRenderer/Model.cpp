#include "Model.h"
#include "Vertex.h"

Model::Model()
{
}


Model::~Model()
{
}

void Model::Load(string file_name)
{
	ifstream ifs(file_name, ios::in);

	Vertex v;
	float x, y, z, w;
	float r, g, b;

	while (!ifs.eof())
	{
		ifs >> x >> y >> z >> w;
		ifs >> r >> g >> b;

		m_VertexList.push_back(Vertex(x, y, z, w, r, g, b));
	}

	ifs.close();
}