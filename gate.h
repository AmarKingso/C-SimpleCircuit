#ifndef GATE_H
#define GATE_H
#include<iostream>
#include<string>
using namespace std;
struct node {
		int ele;
		node* next;
		node* prev;
		node(int element = 0, node* _next = NULL,node* _prev=NULL) {
			ele = element;
			next = _next;
			prev = _prev;
		}
	};
typedef struct node node;
class Gate {
private:
	string name;
public:
	string type;
	node* output;
	node* input1;
	node* input2;
	explicit Gate(string n):name(n) {
		output = new node;
		input1 = new node(0, output);
		input2 = new node(0, output);
	}
	virtual ~Gate(){
		delete output;
		delete input1;
		delete input2;
	}
	virtual void function() = 0;
};

class AndGate:public Gate {
public:
	AndGate(string n):Gate(n) {
		type = "and";
	}
	void function() {
		output->ele = input1->ele*input2->ele;
		if (output->next != NULL)
			output->next->ele = output->ele;
	}
};

class OrGate :public Gate {
public:
	OrGate(string n):Gate(n){
		type = "or";
	}
	void function() {
		if (input1->ele == 0 && input2->ele == 0)
			output->ele = 0;
		else
			output->ele = 1;
		if (output->next != NULL)
			output->next->ele = output->ele;
	}
};

class NotGate :public Gate {
public:
	NotGate(string n) :Gate(n) {
		type = "not";
	}
	void function() {
		output->ele = input1->ele == 0 ? 1 : 0;
		if (output->next != NULL)
			output->next->ele = output->ele;
	}
};

class XorGate :public Gate {
public:
	XorGate(string n) :Gate(n) {
		type = "xor";
	}
	void function() {
		output->ele = input1->ele == input2->ele ? 0 : 1;
		if (output->next != NULL)
			output->next->ele = output->ele;
	}
};
#endif