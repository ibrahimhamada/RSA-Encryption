#pragma once
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

class RSA
{
public:
	RSA();
	~RSA();
	long int GeneratePrime();           
	bool isPrime(long int x);
	bool isPrime(long long int x);
	bool Coprime(long long int x, long long int y);
	void PublicKey();
	void PrivateKey();
	void ReadOriginalMessage(string filename);
	void ReadEncryptedMessage(string filename);
	void Encryption(string filename);
	void Decryption(string filename);
	void StoreMessage();
	long long int GCD(long long int x, long long int y);
	long long int ModularExponent(long long int base, long long int exponent, long long int m);
	long long int MultiplicativeInverse(long long int x, long long int m);

	//Getters
	long int get_p();
	long int get_q();
	long long int get_n();
	long long int get_k();
	long long int get_e();
	long long int get_d();

	int z;
	string filename;

	long int p;
    long int q;
	long long int n ;
	long long int k;
	long long int e;
	long long int d;

	int characters = 0;
	wchar_t* Cmessages;
	long long int** Nmessages;


private:
};

