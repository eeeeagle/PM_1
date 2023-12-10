#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <random>

template <typename T>
std::vector<T> random_vector(const size_t size) /* returns random vector with values in range [-100; 100] */
{
	std::vector<T> vector;
	srand((unsigned int)time(nullptr));
	for (size_t i = 0; i < size; i++)
		vector.push_back((rand() % 200) - 100);
	return vector;
}

template <typename T>
class TriangularMatrix
{
private:
	std::vector<T> matrix;
	const size_t size;
public:
	TriangularMatrix(const size_t size) : size(size)
	{
		matrix = random_vector<T>(size * (size + 1) / 2);
	}
	T operator()(const size_t row, const size_t column) const
	{
		if (row >= size || column < row || column >= size)
			throw std::out_of_range("Out of range");

		return matrix[row * size + column - row * (row + 1) / 2];
	}
	friend std::ostream& operator <<(std::ostream& out, const TriangularMatrix& m)
	{
		for (size_t i = 0; i < m.size; i++)
		{
			for (size_t j = 0; j < m.size; j++)
			{
				try
				{
					out << std::setw(5) << m(i, j) << std::right;
				}
				catch (const std::out_of_range& err)
				{
					out << std::setw(5) << ' ' << std::right;
				}
			}
			out << std::endl;
		}
		return out;
	}
	size_t get_size() const
	{
		return size;
	}
};