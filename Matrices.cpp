#include "Matrices.h"
#include <stdexcept>

namespace Matrices
{
	// Constructor to initialize a matrix of size _rows x _cols
	Matrix::Matrix(int _rows, int _cols)
	{
		// Resize the matrix to have _rows rows
		a.resize(_rows);

		// Loop through each row and resize each row to have _cols columns
		for (int i = 0; i < _rows; ++i)
		{
			a[i].resize(_cols, 0.0);  // Initialize each element to 0
		}
		// Set the number of rows and columns
		rows = _rows;
		cols = _cols;
	}
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), a.getCols());

		for (int i = 0; i < a.getRows(); i++)
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		return c;
	}

	bool operator==(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) return false;

		for (int i = 0; i < a.getRows(); i++)
			for (int j = 0; j < a.getCols(); j++)
				if (abs(a(i, j) - b(i, j)) < 0.001) return false;
		return true;
	}

	bool operator!=(const Matrix& a, const Matrix& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			os << "\n";
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j);
			}
			os << "\n";
		}
		return os;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		Matrix c(a.getRows(), b.getCols());
		if (a.getCols() != b.getRows())
			throw runtime_error("Error: dimensions must agree");

		for (int i = 0; i < c.getRows(); ++i)
		{
			for (int j = 0; j < c.getCols(); ++j)
			{
				for (int k = 0; k < a.getCols(); ++k)
				{
					c(i, j) += (a(i, k) * b(k, j));
				}
			}
		}
		return c;
	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
		a = { { cos(theta), -sin(theta)},{ sin(theta), cos(theta) } };
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
		a = { {scale, 0}, {0, scale } };
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
	{
		for (int col = 0; col < nCols; col++)
		{
			a[0][col] = xShift;
			a[1][col] = yShift;
		}
	}
}