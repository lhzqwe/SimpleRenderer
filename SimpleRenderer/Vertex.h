#pragma once
class Vertex
{
public:
	Vertex() = default;
	Vertex(float _x, float _y, float _z, float _w,
			float _R, float _G, float _B) :
		x(_x), y(_y), z(_z), w(_w),
		R(_R), G(_G), B(_B)
		{};
	~Vertex();

private:
	void SetPosition(float x, float y, float z, float w);
	void SetColor(float R, float G, float B);

private :
	float x;
	float y;
	float z;
	float w;

	float R;
	float G;
	float B;
};

