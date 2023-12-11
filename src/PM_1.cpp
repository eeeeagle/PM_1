#include "TriangularMatrix.hpp"
#include <string>

bool is_value(const std::string& str)
{
	for (auto it : str)
		if (!isdigit(it))
			return false;
	return !str.empty();
}

int get_value()
{
	while (true)
	{
		std::cout << "Enter matrix dimension: ";
		std::string input_string;
		getline(std::cin, input_string);

		if (is_value(input_string))
			return std::stoi(input_string);
		else
			std::cout << "Incorrect input. Try again." << std::endl << std::endl;
	}
}

template <typename T>
std::vector<T> back_substitution(const TriangularMatrix<T>& a, const std::vector<T>& b)
{
	size_t size = a.get_size();
	if (size != b.size())
		throw std::invalid_argument("Mismatch size");

	std::vector<T> x(size);
	for (int k = (int)size - 1; k >= 0; k--)
	{
		x[k] = b[k];
		for (int i = k + 1; i < size; i++)
			x[k] -= a(k, i) * x[i];
		x[k] /= a(k, k);
	}
	return x;
}

int main()
{
	const size_t size = get_value();
	std::cout << std::endl;

	TriangularMatrix<double> a(size);
	std::vector<double> b = random_vector<double>(size);
	std::vector<double> x = back_substitution(a, b);

	std::cout << "Triangle matrix A:" << std::endl << a << std::endl;

	std::cout << "Constant term B:" << std::endl;
	for (auto it : b)
		std::cout << std::setw(4) << it << std::right << std::endl;
	std::cout << std::endl;

	std::cout << "Solution X:" << std::endl;
	for (auto it : x)
		std::cout << std::setw(4) << it << std::right << std::endl;
	std::cout << std::endl;

	return 0;
}
