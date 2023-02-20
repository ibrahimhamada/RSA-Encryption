#include "RSA.h"

RSA::RSA()
{
}

RSA::~RSA()
{
}

//This function is used to determine weather a given number is a prime number or not.
bool RSA::isPrime(long int x)
{
	if (x == 1 || x == 0)
		return false;
	else
		for (long int i = 2; i <= x / 2; i++)
		{
			if (x % i == 0)
			{
				return false;
			}
		}
	return true;
}


//This function is used to determine weather a given number is a prime number or not.
bool RSA::isPrime(long long int x)
{
	if (x == 1 || x == 0)
		return false;
	else
		for (long long int i = 2; i <= x / 2; i++)
		{
			if (x % i == 0)
			{
				return false;
			}
		}
	return true;
}


//This function is used to generate large prime numbers
long int RSA::GeneratePrime()
{
	srand(time(NULL));
    long int a = 10000 + (rand()% (15000 - 10000 + 1));

	while (!isPrime(a))
	{
		a = 10000 + (rand() % (15000 - 10000 + 1));
	}
	return a;
}


//This function is used to calculate the GCD between two integers.
long long int RSA::GCD(long long int x, long long int y)
{
	long long int temp;
	if (y > x)
	{
		temp = x;
		x = y;
		y = temp;
	}
	if (y == 0)
		return x;
	else
		GCD(y, x % y);
}


//This function is used to deterine weather the given two numbers are coprime or not by calling the GCD function.
bool RSA::Coprime(long long int x, long long int y)
{
	if (GCD(x, y) == 1)
		return true;
	else
		return false;
}


//This functoin is used to calculate the parameters (p, q, n, k, e)
void RSA::PublicKey()
{
	p = GeneratePrime();
	q = GeneratePrime();
	while (p == q) {
		q = GeneratePrime();
	}
	n = p * q;
	k = (p - 1) * (q - 1);
	
	srand(time(NULL));

	e = 2 + (rand() % (k-2));
	
	while(!Coprime(e, k))
		e = 2 + (rand() % (k - 2));

	return;
}


//This function is used to obtain the multiplicative inverse of (x mod m).
long long int RSA::MultiplicativeInverse(long long int x, long long int m)
{
	x = x % m;
	for (long long int i = 1; i < m; i++)
	{
		if ((x * i) % m == 1)
		{
			return i;
		}
	}
}


//This function is used to obtain the private key (d).
void RSA::PrivateKey()
{
	d = MultiplicativeInverse(e, k);
}


//This function is used to calculate the Modular Exponentation of (base ^ exponent) mod n 
long long int RSA::ModularExponent(long long int base, long long int exponent, long long int n)
{
	if (base % n == 0) return 0;
	else {
	    long long int result = 1;
		base = base % n;
		while (exponent > 0) {
			if (exponent % 2 != 0)
				result = (result * base) % n;

			exponent /= 2;
			base = (base * base) % n;
		}
		return result;
	}
}


//This function is used to read the Original message from the text file and store it in a 
//(wchar_t) array which is of bigger size than the normal (char) array as we will deal with large numbers. 
void RSA::ReadOriginalMessage(string filename)
{
	characters = 0;
	fstream input_file;
	input_file.open(filename, ios::in);
	string f = filename;
	while (!input_file) {
		cout << "File Not Found! Please Enter a valid file name:  ";
		getline(cin, f);
		input_file.open(f, ios::in);
	}
	
	char y;
	while (input_file.read((char*)&y, sizeof(y))) { 
		characters++;
	}
	input_file.close();
	input_file.open(f, ios::in);
	wchar_t* cmessages = new wchar_t [characters];

	y = ' ';
	
	for (int i = 0; i < characters; i++) {
		input_file.read((char*)&y, sizeof(y));
		cmessages[i] = y;
	}

	input_file.close(); 
	Cmessages = cmessages; 
}



//This function is used to read the Original message from the text file and store it in a (wchar_t) array which is of bigger size 
//than the normal (char) array as we will deal with large numbers. 
void RSA::ReadEncryptedMessage(string filename)
{
	characters = 0;
	fstream input_file;
	input_file.open(filename, ios::in);
	string f = filename;
	while (!input_file) {
		cout << "File Not Found! Please Enter a valid file name: ";
		getline(cin, f);	
		input_file.open(f, ios::in);
	}

	string y;
	while (getline(input_file, y)) { 
		characters++;
	}
	input_file.close();
	input_file.open(f, ios::in);

	long long int** temp = new long long int* [characters];

	for (int i = 0; i < characters; ++i)
		temp[i] = new long long int[1];

	y = " ";
	for (int i = 0; i < characters; i++) {
		input_file >> temp[i][0];
	}
	input_file.close(); 
	Nmessages = temp;
}



//This function is used for Encryption using the public keys
void RSA::Encryption(string filename)
{
	PublicKey();
	z = 1;
	long long int temp;

	ReadOriginalMessage(filename);

	long long int** temparr = new long long int* [characters];

	for (int i = 0; i < characters; i++)
		temparr[i] = new long long int[1];

	for (int i = 0; i < characters; i++) {
		temp = ModularExponent(Cmessages[i], e, n);
		temparr[i][0] = temp;
	}

	Nmessages = temparr;
	StoreMessage();
}


//This function is used for Decryption using the private keys
void RSA::Decryption(string filename)
{
	PrivateKey();
	long long int temp;
	z = 2;			

	ReadEncryptedMessage(filename);
	for (int i = 0; i < characters; i++) {
		temp = Nmessages[i][0];
		temp = ModularExponent(temp, d, n);
		Cmessages[i] = temp;
	}
	StoreMessage();
}


//This function is used to store the encrypted or the decrypted message in a text file.
void RSA::StoreMessage()
{
	char y;
	if (z == 1) {
		ofstream file;
		string f;
		cout << "Please Enter a valid file name for the Encrypted Message. Ex: (Encrypted.txt):  ";
		getline(cin, f);	
		file.open(f, ios::out);
		for (int i = 0; i < characters; i++)
		{
			file << Nmessages[i][0];
			if (i != characters - 1)
				file << "\n";
		}
		file.flush();
		file.close();
		cout << endl << "Encrypted Message File Generation Done!" << endl;
	}
	else {
		ofstream file;
		string f;
		cout << "Please Enter a valid file name for the Encrypted Message. Ex: (Decrypted.txt):   ";
		getline(cin, f);
		file.open(f, ios::out);
		for (int i = 0; i < characters; i++)
		{
			file << (char)Cmessages[i];
		}
		file.flush();
		file.close();
		cout << endl << "Decrypted Message File Generation Done!" << endl;
	}
}


////Getters to ge the parameters///
long int RSA::get_p() {
	return p;
}


long int RSA::get_q() {
	return q;
}


long long int RSA::get_n() {
	return n;
}


long long int RSA::get_k() {
	return k;
}


long long int RSA::get_e() {
	return e;
}


long long int RSA::get_d() {
	return MultiplicativeInverse(e, k);
}
