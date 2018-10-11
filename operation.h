#ifndef OPERATION_H
#define OPERATION_H
#include<iostream>
#include<map>
#include<vector>
#include"gate.h"
using namespace std;

map<string, Gate*> obj;
map<node*, Gate*> togate;
vector<string> glist;

void choosegate() {
	int chosen;
	cin >> chosen;
	string gatename;
	if (chosen == 1 || chosen == 2 || chosen == 3 || chosen == 4) {
		cout << "\n\nGive the gate a name:";
		cin >> gatename;
		if (obj.find(gatename) != obj.end()) {
			cout << "\n\nUsed name.Try again!" << endl;
			chosen = -1024;
		}
	}
	
	switch (chosen) {
	case 1:
		obj[gatename] = new AndGate(gatename);
		togate[obj[gatename]->output] = obj[gatename];
		glist.push_back(gatename);
		break;
	case 2:
		obj[gatename] = new OrGate(gatename);
		togate[obj[gatename]->output] = obj[gatename];
		glist.push_back(gatename);
		break;
	case 3:
		obj[gatename] = new NotGate(gatename);
		togate[obj[gatename]->output] = obj[gatename];
		glist.push_back(gatename);
		break;
	case 4:
		obj[gatename] = new XorGate(gatename);
		togate[obj[gatename]->output] = obj[gatename];
		glist.push_back(gatename);
		break;
	default:
		if (chosen != -1024) {
			cout << "Wrong number!Try again!" << endl;
			cout << "Please Please enter a new number:";
			choosegate();
		}
		break;
	}
}

void run(Gate* g) {
	if (g->input1->prev != NULL)
		run(togate[g->input1->prev]);
	if (g->input2->prev != NULL)
		run(togate[g->input2->prev]);
	g->function();
}

void operate() {
	int select;
	cin >> select;
	int flag = 0;
	switch (select) {
	case 1:
		cout << "\n\nSelect the type of gate you want to create:" << endl;
		cout << "1-andgate" << endl;
		cout << "2-orgate" << endl;
		cout << "3-notgate" << endl;
		cout << "4-xorgate" << endl;
		cout << "Enter number:";
		choosegate();
		break;
	case 2: {
		string from, to;
		cout << "\n\nEnter the gate's names you want to connect" << endl;
		cout << "From:";
		cin >> from;
		cout << "To:";
		cin >> to;
		if (obj.find(from) == obj.end() || obj.find(to) == obj.end())
			cout << "The connection does not exist" << endl;
		else {
			if (obj[to]->type != "not") {
				if (obj[to]->input1->prev != NULL&&obj[to]->input2->prev != NULL || from == to)
					cout << "There was an error in the connection" << endl;
				else {
					if (obj[to]->input1->prev == NULL) {
						obj[from]->output->next = obj[to]->input1;
						obj[to]->input1->prev = obj[from]->output;
					}
					else {
						obj[from]->output->next = obj[to]->input2;
						obj[to]->input2->prev = obj[from]->output;
					}
				}
			}
			else {
				if (obj[to]->input1->prev != NULL || from == to)
					cout << "There was an error in the connection" << endl;
				else {
					obj[from]->output->next = obj[to]->input1;
					obj[to]->input1->prev = obj[from]->output;
				}
			}
		}
		break;
	}
	case 3:
		for (int i = 0; i < glist.size(); i++) {
			cout << "name : " << glist[i] << endl;
			cout << "type : " << obj[glist[i]]->type << endl;
			cout << "input1 : " << obj[glist[i]]->input1->ele << endl;
			if (obj[glist[i]]->type != "not")
				cout << "input2 : " << obj[glist[i]]->input2->ele << endl;
			cout << "output : " << obj[glist[i]]->output->ele << endl << endl;
		}
		break;
	case 4:
	{
		string found;
		cout << "\n\nPlease enter the name of gate you want to input:" << endl;
		cin >> found;
		if (obj.find(found) == obj.end())
			cout << "Not found the gate!" << endl;
		else {
			cout << "Please enter input:" << endl;
			if (obj[found]->type != "not") {
				if (obj[found]->input1->prev == NULL) {
					cout << "input1:";
					cin >> obj[found]->input1->ele;
				}
				else
					cout << "Input1 is connected" << endl;
				if (obj[found]->input2->prev == NULL) {
					cout << "input2:";
					cin >> obj[found]->input2->ele;
				}
				else
					cout << "Input2 is connected" << endl;
			}
			else {
				cout << "input:";
				if (obj[found]->input1 == NULL)
					cin >> obj[found]->input1->ele;
				else
					cout << "Input is connected" << endl;
			}
		}
		break;
	}
	case 5:
		for (int i = 0; i < glist.size(); i++) {
			if (obj[glist[i]]->output->next == NULL) {
				flag++;
				run(obj[glist[i]]);
				cout << "The " << glist[i] << "'s output is : " << obj[glist[i]]->output->ele << endl;
			}
			if (flag == 0 && i == glist.size() - 1)
				cout << "There was an error in the connection" << endl;
		}
		break;
	default:
		cout << "Wrong number!Try again!" << endl;
		cout << "Please Please enter a new number:";
		operate();
		break;
	}
}

#endif
