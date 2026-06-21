#pragma once

#include<stdexcept>
#include<iostream>
#include "List.h"
#include "DNode.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class MinHeap {
private:
	E* elements;
	int max;
	int size;

	int leftChild(int pos) {
		return 2 * pos + 1;
	}
	int rightChild(int pos) {
		return 2 * pos + 2;
	}
	int parent(int pos) {
		return (pos - 1) / 2;
	}
	bool isLeaf(int pos) {
		return leftChild(pos) >= size;
	}
	int minChild(int pos) {
		if ((rightChild(pos) < size) && (elements[rightChild(pos)] < elements[leftChild(pos)])) {
			return rightChild(pos);
		}
		else {
			return leftChild(pos);
		}
	}
	void swap(int pos1, int pos2) {
		E temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}
	void siftUp(int pos) {
		while (pos > 0 && elements[pos] < elements[parent(pos)]) {
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}
	void sifDown(int pos) {
		while (!isLeaf(pos) && elements[minChild(pos)] < elements[pos]) {
			int minPos = minChild(pos);
			swap(pos, minPos);
			pos = minPos;
		}
	}

public:
	MinHeap(int max = DEFAULT_MAX) {
		elements = new E[max];
		this->max = max;
		size = 0;
	}
	~MinHeap() {
		delete[] elements;
	}
	void insert(E element) {
		if (size == max) {
			throw runtime_error("Heap is full");
		}
		elements[size] = element;
		siftUp(size);
		size++;
	}
	E first() {
		if (size == 0) {
			throw runtime_error("Heap is empty");
		}
		return elements[0];
	}
	E removeFirst() {
		return remove(0);
	}
	E remove(int pos) {
		if (size == 0) {
			throw runtime_error("List is empty");
		}
		if (pos < 0 || pos >= size) {
			throw runtime_error("Invalid index. ");
		}
		swap(pos, (size - 1));
		size--;
		sifDown(pos);
		return elements[size];
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[ ";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i != size - 1) {
				cout << ", ";
			}
		}
		cout << "] " << endl;
	}
	bool isEmpty() {
		return size == 0;
	}
};

