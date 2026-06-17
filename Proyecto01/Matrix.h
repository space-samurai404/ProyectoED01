#pragma once
#include <stdexcept>
#include <iostream>
#define MATRIX_H


using std::runtime_error;
using std::cout;
using std::endl;

template<typename E>
class Matrix
{
private:
	int rows;
	int columns;
	E** matrix;

public:
	Matrix(int rows, int columns) {
		if (rows <= 0 || columns <= 0) {
			throw runtime_error("Number of rows and columns must be greater than zero.");
		}

		this->rows = rows;
		this->columns = columns;
		matrix = new E * [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new E[columns];
		}
	}

	

	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	E getValue(int row, int column) {
		if (row < 0 || row >= rows) {
			throw runtime_error("Invalid row. ");
		}
		if (column < 0 || column >= columns) {
			throw runtime_error("Invalid column. ");
		}
		return matrix[row][column];
	}

	void setValue(int row, int column, E value) {
		if (row < 0 || row >= rows) {
			throw runtime_error("Invalid row. ");
		}
		if (column < 0 || column >= columns) {
			throw runtime_error("Invalid column. ");
		}
		matrix[row][column] = value;

	}

	int getRows() {
		return rows;
	}

	int getColumns() {
		return columns;
	}

	void setAll(E value) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = value;
			}
		}
	}


	void expand(E value) {
		addRow(value);    
		addColumn(value);
	}


	void shrink(int x, int y) {
		removeRow(x);
		removeColumn(y);
	}

	void transpose() {

		E** new_matrix = new E * [columns];
		for (int i = 0; i < columns; i++) {
			new_matrix[i] = new E[rows];
		}

		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				new_matrix[i][j] = matrix[j][i];
			}
		}

		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = new_matrix;
		int temp = rows;
		rows = columns;
		columns = temp;
	}

	void addRow(E value) {

		E** new_matrix = new E * [rows + 1];
		for (int i = 0; i < rows + 1; i++) {
			new_matrix[i] = new E[columns];
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				new_matrix[i][j] = matrix[i][j];
			}
		}

		for (int j = 0; j < columns; j++) {
			new_matrix[rows][j] = value;
		}

		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = new_matrix;
		rows++;

	}

	void addColumn(E value) {
		E** new_matrix = new E * [rows];
		for (int i = 0; i < rows; i++) {
			new_matrix[i] = new E[columns + 1];
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				new_matrix[i][j] = matrix[i][j];
			}
		}

		for (int i = 0; i < rows; i++) {
			new_matrix[i][columns] = value;
		}

		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = new_matrix;
		columns++;
	}

	void removeRow(int row) {
		if (row < 0 || row >= rows) {
			throw runtime_error("Invalid row. ");
		}
		E** new_matrix = new E * [rows - 1];
		for (int i = 0; i < rows - 1; i++) {
			new_matrix[i] = new E[columns];
		}
		int k = 0;
		for (int i = 0; i < rows; i++) {
			if (i != row) {
				for (int j = 0; j < columns; j++) {
					new_matrix[k][j] = matrix[i][j];
				}
				k++;
			}
		}
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = new_matrix;
		rows--;

	}

	void removeColumn(int col) {
		if (col < 0 || col >= columns) {
			throw runtime_error("Invalid column. ");
		}
		E** new_matrix = new E * [columns - 1];
		for (int i = 0; i < rows; i++) {
			new_matrix[i] = new E[columns - 1];
		}

		for (int i = 0; i < rows; i++) {
			int k = 0;
			for (int j = 0; j < columns; j++) {
				if (j != col) {
					new_matrix[i][k] = matrix[i][j];
					k++;
				}
			}
		}

		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;

		matrix = new_matrix;
		columns--;
	}

	void print() {

		for (int i = 0; i < rows; i++) {
			cout << "[";
			for (int j = 0; j < columns; j++) {
				cout << matrix[i][j];
				if (j < columns - 1) {
					cout << ", ";
				}
			}
			cout << "]" << endl;
		}

	}

};


