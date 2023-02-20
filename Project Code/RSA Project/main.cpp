#include <iostream>
#include <string>
using namespace std;

#include "RSA.h"

int main() {

	cout << "This program is used to Encrypt and Decrypt Messages from a text file";
    int v = 0;
	char ans = 'Y';
	RSA a;
	string s;

	while (ans == 'Y') {
		cout << endl << endl << "If you want to Encrypt a Message, Enter (1)" << endl;
		cout << "If you want to Decrypt a Message, Enter (2)" << endl;

		cin >> v;
		while (v != 1 && v != 2 && v != -1) {
			cout << "Error!! Please Enter a Valid Input! (1, 2, or -1)!" << endl;
			cin >> v;
		}
		cin.ignore();

		if (v == 1)
		{
			cout << "Please Enter the File Name of the Original Message: ";
			getline(cin, s);
			a.Encryption(s);
			cout << endl << endl;
			cout << "p = " << a.get_p() << endl << endl;
			cout << "q = " << a.get_q() << endl << endl;
			cout << "n = " << a.get_n() << endl << endl;
			cout << "e = " << a.get_e() << endl << endl;
			cout << "d = " << a.get_d() << endl << endl;
		}

		if (v == 2)
		{
			cout << "Please Enter the File Name of the Encrypted Message:  ";
			getline(cin, s);
			a.Decryption(s);
			cout << endl << endl;
			cout << "p = " << a.get_p() << endl << endl;
			cout << "q = " << a.get_q() << endl << endl;
			cout << "n = " << a.get_n() << endl << endl;
			cout << "e = " << a.get_e() << endl << endl;
			cout << "d = " << a.get_d() << endl << endl;
		}


		cout << "Do you want to perform another operation? (Y / N):   ";
		cin >> ans;

		while (ans != 'Y' && ans != 'N') {
			cout << "Error!! Please Enter a Valid Input! (Y / N):   ";
			cin >> ans;
		}
		cin.ignore();

	}
	

	return 0;
}


