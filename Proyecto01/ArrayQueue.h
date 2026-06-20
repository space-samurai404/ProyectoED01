#pragma once
#include <iostream>
#include <stdexcept>
#include "Queue.h"
#include "util.h"

using std::runtime_error;
using std::cout;
using std::endl;


template <typename E>
class ArrayQueue : public Queue<E>
{
private:
	E* elements;
	int front;
	int back;
	int size;
	int max;

public:
	ArrayQueue(int max = DEFAULT_MAX)
	{
		if (max < 1)
		{
			throw runtime_error("Invalid max size");
		}

		elements = new E[max];
		this->max = max;
		front = back = size = 0;
	}

	~ArrayQueue()
	{
		delete[] elements;
	}

	void enqueue(E element)
	{
		if (size == max)
		{
			throw runtime_error("Stack is full");
		}

		elements[back] = element;
		back = (back + 1) % max;
		size++;
	}

	E dequeue()
	{
		if (size == 0)
		{
			throw runtime_error("Queue is empty");
		}

		front = (front + 1) % max;
		size--;
		return elements[(front + max - 1) % max];
	}

	E frontValue()
	{
		if (size == 0)
		{
			throw runtime_error("Queue is empty");
		}

		return elements[front];
	}
	void clear()
	{
		front = size = back = 0;
	}
	bool isEmpty()
	{
		return size == 0;
	}
	int getSize()
	{
		return size;
	}
	void print()
	{
		cout << "[";

		for (int i = front; i != back; i = (i + 1) % max)
		{
			cout << elements[i];

			if (i != (back + max) % max)
			{
				cout << ",";
			}

		}

		cout << "]" << endl;
	}
};
