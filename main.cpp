#include <iostream>

using namespace std;


unsigned short p10(unsigned short p){
	
	int perm_scheme[10] = { 8, 6, 9, 4, 7, 1, 10, 2 , 3 , 5};
	unsigned short n = 0;// bit we're taking from old location to new location
	unsigned short permuted = 0;

	for(int i = 1; i <= 10; i++){
		n = (p << (16 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << 10 - i);
		permuted = permuted | n; 
	}

	return permuted;
}

unsigned short p8(unsigned short p){
	
	unsigned short mask = 0;
	unsigned short L = 0;// Left half 5 bits
	unsigned short R = 0;// Right half 5 bits

	unsigned short n = 0;// bit we're taking from old location to new location
	unsigned short permuted = 0;

	L = (p >> 5);
	R = (p << 11);
	R = (R >> 11);
	
	// left shit - 1 LEFT half 5 bits
	mask = (L << 12);
	mask = (mask >> 11);
	L = (L >> 4);
	L = L | mask;

	// left shit - 1 RIGHT half 5 bits
	mask = (R << 12);
	mask = (mask >> 11);
	R = (R >> 4);
	R = R | mask;

	//Combining left 5 and right 5 back together
	p = (L << 5) | R;

	// now we P8
	int perm_scheme[10] = { 4, 7, 3, 6, 2, 5, 0, 1};
	for(int i = 1; i <= 8; i++){
		n = (p << (15 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << 8 - i);
		permuted = permuted | n;
	}

	return permuted;
}

unsigned short IP(char a){

	unsigned short p = (unsigned short)a;
	unsigned short permuted = 0;
	unsigned short n = 0;

	int perm_scheme[8] = { 6, 2, 5, 7, 4, 0, 3, 1};
	for(int i = 1; i <= 8; i++){
		n = (p << (15 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << 8 - i);
		permuted = permuted | n;
	}

	return permuted;
}

unsigned short IP_inverse(char a){

	// unsigned short p = (unsigned short)a;
	// unsigned short permuted = 0;
	// unsigned short n = 0;

	// int perm_scheme[8] = { 6, 2, 5, 7, 4, 0, 3, 1};
	// for(int i = 1; i <= 8; i++){
	// 	n = (p << (15 - perm_scheme[i-1]));
	// 	n = (n >> 15);
	// 	n = (n << 8 - i);
	// 	permuted = permuted | n;
	// }
	// return permuted;
	return 0;
}

char fk(char a, unsigned short sk){

	unsigned short nibble = (unsigned short)a;
	unsigned short EP = 0;
	unsigned short n = 0;
	unsigned short p = 0;

	nibble = (nibble << 4);
	nibble = (nibble >> 4);
	
	int perm_scheme[8] = { 0, 3, 2, 1, 2, 1, 0, 3};
	for(int i = 1; i <= 8; i++){
		n = (nibble << (15 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << 8 - i);
		EP = EP | n;
	}

	cout<<endl<<"SK: "<<sk;
	cout<<endl;
	EP = EP ^ sk;
	cout<<endl<<"EP: "<<EP;

	return EP;
}




int main() {

	unsigned short p = 682;
	char a = 'a';
	unsigned short sk = 0;

	p = p10(p);
	p = p8(p);
	cout<<endl<<"P: "<<p;
	sk = p;
	fk(a,sk);
	//cout<<endl<<"CIRCLE LEFT SHIFT : "<< fk(a, sk);

	return 0;
}


