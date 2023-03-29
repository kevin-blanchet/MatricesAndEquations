#pragma once
#include <vector>

class Matrix
{
public:
	Matrix(unsigned i, unsigned j);

	unsigned getSizeI() const;
	unsigned getSizeJ() const;

	void set(unsigned i, unsigned j, float value);
	float get(unsigned i, unsigned j) const;

	Matrix Multiply(float f) const;
	Matrix Multiply(const Matrix& m) const;
	float Det() const;
	Matrix Sub(unsigned startI, unsigned startJ, unsigned endI, unsigned endJ) const;
	Matrix Invert() const;
	Matrix Transpose() const;
	Matrix Comatrix() const;

	void print() const;
	
protected:
	unsigned _sizeI;
	unsigned _sizeJ;

	std::vector<float> _data;
};

