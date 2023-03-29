#include <iostream>

#include "Matrix.h"

#define MAIN
#ifdef MAIN
int main()
{
	unsigned int n;
	float t;

	std::vector<float> mat;

	std::cout << "Résolution d'équations:" << '\n';

	std::cout << "Nombre d'équations/inconnues:";

	std::cin >> n;

	Matrix m(n, n);
	Matrix x(n, 1);

	for(int i = 0; i < n; ++i)
	{
		std::cout << "equation " << i+1 << ":\n";
		for (int j = 0; j < n; ++j)
		{
			std::cout << char('a' + j) << ": ";
			std::cin >> t;
			m.set(i, j, t);
		}
		std::cout << "= ";
		std::cin >> t;
		x.set(i, 0, t);
	}
	m.Invert().Multiply(x).print();
	//x.print();
	return 0;
}
#else
int main()
{
	std::vector<float> v{ 1, -2, 3, 0, -1, 4, 0, 0, 1 };

	Matrix m(3, 3);

	for (int i = 0; i < m.getSizeI(); ++i)
	{
		for (int j = 0; j < m.getSizeJ(); ++j)
		{
			m.set(i, j, v[i * m.getSizeI() + j]);
		}
	}

	Matrix m2(2, 2);

	for (int i = 0; i < m2.getSizeI(); ++i)
	{
		for (int j = 0; j < m2.getSizeJ(); ++j)
		{
			m2.set(i, j, rand()%10);
		}
	}
	m2.print();
	std::cout << m2.Det() << std::endl << std::endl;

	m.print();
	std::cout << m.Det() << std::endl << std::endl;
	m.Invert().print();
}
#endif