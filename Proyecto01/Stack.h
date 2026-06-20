#pragma once
#include "util.h"
template <typename E>
class Stack {
public:
	Stack() {} //contructor
	Stack(const Stack<E>& other) = delete; //el "other no lo necitamos todavia, pero no sobra xd"
	void operator = (const Stack<E>&) = delete;
	virtual ~Stack() {} //destructor
	virtual void push(E element) = 0;
	virtual E pop() = 0;
	virtual E topValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};
