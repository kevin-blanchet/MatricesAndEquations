#include "Matrix.h"

#include <iostream>

Matrix::Matrix(unsigned i, unsigned j): _sizeI(i), _sizeJ(j)
{
	_data = std::vector<float>(i*j, 0);
}

unsigned Matrix::getSizeI() const
{
	return _sizeI;
}

unsigned Matrix::getSizeJ() const
{
	return _sizeJ;
}

void Matrix::set(unsigned i, unsigned j, float value)
{
	unsigned coord = i + j * _sizeI;
	_data[coord] = value;
}

float Matrix::get(unsigned i, unsigned j) const
{
	unsigned coord = i + j * _sizeI;
	return _data[coord];
}

Matrix Matrix::Multiply(float f) const
{

	Matrix m(_sizeI, _sizeJ);

	for (int i = 0; i < _sizeI; ++i)
	{
		for (int j = 0; j < _sizeJ; ++j)
		{
			m.set(i, j, get(i, j) * f);
		}
	}
	return m;
}

Matrix Matrix::Multiply(const Matrix& m) const
{
	if(_sizeJ != m.getSizeI())
	{
		std::cout << "ERROR: Attempted to multiply incompatible matrices" << std::endl;
		return Matrix(1, 1);
	}

	const unsigned u = _sizeI;
	const unsigned v = m.getSizeJ();
	Matrix r(u,v);

	for (int i = 0; i < u; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			float val = 0;

			for(int i2 = 0; i2 < _sizeJ; ++i2)
			{
				val += (get(i, i2) * m.get(i2, j));
			}

			r.set(i, j, val);
		}
	}

	return r;
}

float Matrix::Det() const
{
	if(_sizeI != _sizeJ)
	{
		std::cout << "ERROR: Matrix must be square" << std::endl;
		return 0.0f;
	}

	if(_sizeI == 1)
	{
		return get(0, 0);
	}

	if(_sizeI == 2)
	{
		return get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0);
	}

	float r = 0;

	for (int i = 0; i < _sizeI; ++i)
	{
		if (get(i, 0) != 0) {
			r += get(i, 0) * Sub((i + 1) % _sizeI, 1, _sizeI - 1, _sizeI - 1).Det();
		}
	}

	return r;
}

Matrix Matrix::Sub(unsigned startI, unsigned startJ, unsigned sizeI, unsigned sizeJ) const
{
	Matrix m(sizeI, sizeJ);

	for (int i = 0; i < m.getSizeI(); ++i)
	{
		for (int j = 0; j < m.getSizeJ(); ++j)
		{
			m.set(i, j, get((startI + i) % getSizeI(), (startJ + j) % getSizeJ()));
		}
	}

	return m;
}

Matrix Matrix::Invert() const
{
	Matrix m(_sizeI, _sizeJ);
	float det = Det();
	if (det != 0)
		m = Comatrix().Transpose().Multiply(1 / det);
	else
		std::cout << "Matrix is not invertible";
	return m;
}

Matrix Matrix::Transpose() const
{
	Matrix m(_sizeI, _sizeJ);
	for (int i = 0; i<_sizeI;++i)
	{
		for (int j = 0; j < _sizeJ; ++j)
		{
			m.set(j, i, get(i, j));
		}
	}
	return m;
}

Matrix Matrix::Comatrix() const
{
	Matrix m(_sizeI, _sizeJ);

	for (int i = 0; i < _sizeI; ++i)
	{
		for (int j = 0; j < _sizeJ; ++j)
		{
			m.set(i, j, Sub((i+1)%_sizeI, (j+1)%_sizeJ, _sizeI-1, _sizeJ-1).Det());
		}
	}
	return m;
}

void Matrix::print() const
{
	for (int i = 0; i < _sizeI; ++i)
	{
		std::cout << "( ";
		for (int j = 0; j < _sizeJ; ++j)
		{
			std::cout << get(i, j) << " ";
		}
		std::cout << ")\n";
	}
	std::cout << std::endl;
}
