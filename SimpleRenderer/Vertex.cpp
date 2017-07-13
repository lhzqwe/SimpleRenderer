#include "Vertex.h"



Vertex::Vertex()
{
}


Vertex::~Vertex()
{
}

void Vertex::SetPosition(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vertex::SetColor(float R, float G, float B)
{
	this->R = R;
	this->G = G;
	this->B = B;
}
