#pragma once
#include <iostream>
#include <stdexcept>
#include "Stack.h"
#include "util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayStack : public Stack<E> {
private:
	E* elements;
	unsigned int max;
	unsigned int top;

public:
	ArrayStack(int max = DEFAULT_MAX) {
		if (max < 1) {
			throw runtime_error("tiene que ser un numero entero mayor que 1");
		}
		elements = new E[max];
		this->max = max;
		top = 0;

	}
	~ArrayStack() {
		delete[] elements;
	}

	void push(E element)
	{
		if (top == max)
		{
			throw runtime_error("Stack overflow");
		}

		elements[top] = element;
		top++;
	}

	E pop()
	{

		if (top == 0)
		{
			throw runtime_error("Stack is empty");
		}

		top--;

		return elements[top];

	}

	E topValue()
	{
		if (top == 0)
		{
			throw runtime_error("Stack is empty");
		}

		return elements[top - 1];
	}

	void clear()
	{
		top = 0;
		//delete[] elements;
		//elements = new E[max]; son para borrar el elemento e iniciar nuevamente el arreglo
	}

	bool isEmpty()
	{
		return top == 0;
	}

	int getSize()
	{
		return top;
	}

	void print()
	{
		cout << "[";

		for (int i = top - 1; i >= 0; i--)
		{
			cout << elements[i];

			if (i != 0)
			{
				cout << ",";
			}

		}

		cout << "]" << endl;
	}
};

