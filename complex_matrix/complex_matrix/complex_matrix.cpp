// complex_matrix.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <complex>
#include <vector>

int main()
{
	int n;
	std::cout << "Enter the matrix size: ";
	std::cin >> n;
	std::cout << "\nEnter the matrix in format (real, image):\n";

	std::vector<std::vector<std::complex<double>>> mtx;
	mtx.resize(n);

	for (int i = 0; i < n; ++i) {
		mtx[i].resize(n);
		for (int j = 0; j < n; ++j) std::cin >> mtx[i][j];
	}

	std::vector<std::vector<std::complex<double>>> answer = mtx;

	for (int k = 2; k <= 8; ++k) {
		std::vector<std::vector<std::complex<double>>> temp = mtx;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				temp[i][j] = 0;
				for (int l = 0; l < n; ++l) {
					temp[i][j] += answer[i][l] * mtx[l][j];
				}
			}

		}
		answer = temp;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << answer[i][j] << " ";
		}
		std::cout << "\n";
	}
    return 0;
}

