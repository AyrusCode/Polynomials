// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef lab1_polynomial
#define lab1_polynomial
#define NOMINMAX

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <istream>
#include <ostream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <filesystem>
using namespace std;

class Polynomial {
	vector<int> data;

public:
	Polynomial() {
		
		data.resize(rand() % 1001);

		for (int i = 0; i < data.size(); i++) {
			data[i] = rand() % 1000;
			bool is_negative = rand() % 2;

			if (is_negative) data[i] *= -1;
		}

	}

	Polynomial(int A[], int size) {
	 
		//

		if ((size < 0 )) {
			int i1[] = {0};
			Polynomial(i1, 0);
		}
		else {
			data.resize(size);

			for (int i = 0; i <size; i++) {
				data[i] = A[i];
			}
		}
		
	}

	Polynomial(string fileName) {
		ifstream poly_stream;
		
		poly_stream.open(fileName.c_str());

		int size;
		poly_stream >> size;

		data.resize(size);

		int value = 0;

		for (int i = 0;i < size; i++) {
			poly_stream >> value;
			data[i] = value;
		}
	

		poly_stream.close();
	}

	int val_at_index(int index) {
		return data[index];
	}

	int vector_size() {
		return data.size();
	}

	~Polynomial() {
		data.erase(data.begin(), data.end());
	}

	bool operator==(const Polynomial& target) {
		if (data.size() != target.data.size()) return false;
		for (int i = 0; i < data.size(); ++i) {
			if (data[i] != target.data[i]) return false;
		}
		return true;
	}

	Polynomial operator+(const Polynomial& target) {
		int max_size = max(data.size(), target.data.size());
		int min_size = min(data.size(), target.data.size());

		int* array = new int[max_size];

		for (int i = 0; i < max_size; i++) {
			if (i < min_size)
				array[i] = data[i] + target.data[i];
			else if (data.size() > min_size)
				array[i] = data[i];
			else
				array[i] = target.data[i];
		}

		Polynomial new_poly(array, max_size);
		return new_poly;
	}

	// make one that auto sets it to 0.
	// maybe combine + and - into one.
	Polynomial operator-(const Polynomial& target) {
		int max_size = max(data.size(), target.data.size());
		int min_size = min(data.size(), target.data.size());

		int* array = new int[max_size];

		for (int i = 0; i < max_size; i++) {
			if (i < min_size) array[i] = data[i] - target.data[i];
			else if (data.size() > min_size) array[i] = data[i];
			else array[i] = -1 * target.data[i];
		}

		Polynomial new_poly(array, max_size);
		return new_poly;
	}

	Polynomial operator*(const Polynomial& target) {
		int new_size = data.size() + target.data.size() - 1;

		int* array = new int[new_size];

		for (int k = 0; k < new_size; k++) array[k] = 0;

		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < target.data.size(); j++)
			{
				int power = i + j;
				array[power] += data[i] * target.data[j];
			}
		}
		Polynomial new_poly(array, new_size);
		return new_poly;
	}

	Polynomial derivative() {
		int new_size = data.size() - 1;
		int* array = new int[new_size];


		if (data.size() == 1) {
			int i1[] = { 0 };
			Polynomial der_poly(i1, 0);
			return der_poly;
		}

		else {
			for (int i = 0; i < new_size; i++) {
				array[i] = data[i + 1] * (i + 1);
			}
			Polynomial der_poly(array, new_size);
			return der_poly;
		}
	}

	// check for things like zero length polynomial?

	void print() {
		for (int i = data.size() - 1; i >= 0; i--)
		{
			if (data[i] != 0) {
				if (i != data.size() - 1) {
					cout << " + ";
				}
				if (data[i] >= 0) {
					cout << data[i] << "x^" << i;
				}
				else cout << "(" << data[i] << ")" << "x^" << i;
			}
		}
		cout << endl;
	}

	void trunc_print() {
		if (data.size() <= 5) print();
		else {
			for (int i = data.size() - 1 ; i >= data.size() - 5; i--) {
				if (data[i] != 0) {
					if (i != data.size() - 1)
						cout << " + ";
					if (data[i] >= 0) {
						cout << data[i] << "x^" << i;
					}
					else cout << "(" << data[i] << ")" << "x^" << i;
				}
			}
		}
	}

	void zero_poly() {
		bool all_zero = true;
		for (int i = 0; i < data.size(); i++) {
			if (data[i] != 0)
				all_zero = false;
		}
		if (all_zero) {
			data.resize(1);
		}
	}
	

	friend class PolynomialTest;

};



// TODO: add headers that you want to pre-compile here

#endif 
