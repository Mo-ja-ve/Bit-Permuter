#include <iostream>

using namespace std;


unsigned short p10(unsigned short p){
	
	int perm_scheme[10] = { 8, 6, 9, 4, 7, 1, 10, 2 , 3 , 5};
	unsigned short n = 0;// bit we're taking from old location to new location
	unsigned short permuted = 0;

	for(int i = 1; i <= 10; i++){
		n = (p << (16 - perm_scheme[i-1]));
		n = (n >> 15);
		n =  n << 10 - i;
		//cout<<endl<<"n: "<<n;
		permuted = permuted | n; 
	}
	
	return permuted;
}

int main() {

	unsigned short p = 682;
	//p10(p);
	cout<< endl<< "PERMUTED 10 BITS: "<< (unsigned short)p10(p);

	return 0;
}