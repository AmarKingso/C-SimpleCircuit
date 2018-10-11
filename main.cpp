#include<iostream>
#include<string>
#include"gate.h"
#include"operation.h"
using namespace std;

int main() {
	while (1) {
		cout << "Type a number to perform the operation!" << endl;
		cout << "1-create a gate" << endl;
		cout << "2-connect a gate to other gate" << endl;
		cout << "3-List all the current gates" << endl;
		cout << "4-setinput" << endl;
		cout << "5-Running the current connection" << endl;
		cout << "Enter the number:";
		operate();
		cout << "\n\n";
	}
	return 0;
}