#include <iostream>
#include <string>
#include <bitset>

using namespace std;

//  p 10 permutation
unsigned short p10(unsigned short p){
	//  Locations which we're taking bits from and moving them to
	//  The instructions suggest that the left most bit is bit 1
	//  However our implementation treats the left most bit as last
	//  So if the instructions call to move the 2nd bit the the fihrst,
	//  place we would use the 8th bit
	//  The necessary order of bits which the instructiosn tell us to
	//  permute are saved in perm_scheme in their respective orders
	int perm_scheme[10] = { 8, 6, 9, 4, 7, 1, 10, 2 , 3 , 5};
	unsigned short n = 0;// bit we're taking from old location to new location
	unsigned short permuted = 0;

	//  This for loop then ioslates the desired bit then sorts it into it's correct place
	//  If we want bit 2 we shift 16 - 8 spaces to the left - isolating our 8th bit in,
	//  the left most location then push it all the way right againt by traveling 15 spaces
	//  we then place this new single isolated bit into it's index i location
	//  we then bit or n with permuted to give us our correct bit in it's correct final location
	for(int i = 1; i <= 10; i++){
		n = (p << (16 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << 10 - i);
		permuted = permuted | n; 
	}

	return permuted;
}

//  This function shares an almost identical permutation scheme - Only mix 8 spots not 10
//  Hence this time the for loop only goes to 8
//  Hoever this function also differs when it comes to the Left and Right splitting
//  The L and R splitting process is documented below as such: 
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

unsigned short p8_shift2(unsigned short p){
	
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

	mask = (L << 12);
	mask = (mask >> 11); 
	L = (L >> 4);
	L = L | mask;

	mask = (L << 12);
	mask = (mask >> 11);
	L = (L >> 4);
	L = L | mask;


	// left shit - 1 RIGHT half 5 bits
	mask = (R << 12);
	mask = (mask >> 11);
	R = (R >> 4);
	R = R | mask;

	mask = (R << 12);
	mask = (mask >> 11);
	R = (R >> 4);
	R = R | mask;

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


//  Initial permutation scheme as outlined in the insturctions
unsigned short IP(unsigned short a){

	unsigned short p = a;
	unsigned short permuted = 0;
	unsigned short n = 0;
	//cout<<endl<<"A: "<<a;
	int perm_scheme[8] = { 6, 2, 5, 7, 4, 0, 3, 1};
	for(int i = 1; i <= 8; i++){
		//cout<<endl<<"I: "<<i;
		//cout<<endl<<"P: "<<p;
		n = (p << (15 - perm_scheme[i-1]));
		//cout<<endl<<"n: "<<n;
		n = (n >> 15);
		//cout<<endl<<"n: "<<n;
		n = (n << 8 - i);
		//cout<<endl<<"n: "<<n;
		permuted = permuted | n;
		//cout<<endl<<"Permuted: "<<permuted;
	}
	//cout<<endl<<"IP: "<<permuted;
	return permuted;
}

//  Inverse permutation
unsigned short IP_inverse(char a){

	unsigned short p = (unsigned short)a;
	unsigned short permuted = 0;
	unsigned short n = 0;

	int perm_scheme[8] = { 4, 7, 5, 1, 6, 0, 2};
	for(int i = 1; i <= 8; i++){
		n = (p << (15 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << 8 - i);
		permuted = permuted | n;
	}

	return permuted;
}

unsigned short sbox(unsigned short p){
	
	unsigned short s0[4][4] = {{1, 0, 3, 2}, 
	 						   {3, 2, 1, 0},
							   {0, 2, 1, 3},
							   {3, 1, 3, 2}};
	
	unsigned short s1[4][4] = {{0, 1, 2, 3},
							   {2, 0, 1, 3},
							   {3, 0, 1, 0},
							   {2, 1, 0, 3}};
	
	unsigned short top = p / 4;
	unsigned short bottom = p % 4;

	unsigned short top_row = (top & 8) / 4 + (top & 1);
	unsigned short top_column = (top & 4) / 2 + (top & 2) / 2;

	unsigned short bottom_row = (bottom & 8) / 4 + (top & 1);
	unsigned short bottom_column = (top & 4) / 2 + (top & 2) / 2;

	unsigned short top_permute = s0[top_row][top_column];
	unsigned short bottom_permute = s1[bottom_row][bottom_column];

	return top_permute * 4 + bottom_permute;
}

unsigned short p4(unsigned short p){
	
	int perm_scheme[4] = { 2, 0, 1, 3};
	unsigned short permuted = 0;
	unsigned  short n = 0;
	
	for(int i = 1; i <= 4; i++){
		n = (p << (15 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << 4 - i);
		permuted = permuted | n;
	}
	return permuted;
}

// fiestil function 
char f(char a, unsigned short sk){

	unsigned short nibble = (unsigned short)a;
	unsigned short permuted = 0;
	unsigned short n = 0;
	unsigned short p = 0;
	
	//cout<<endl<<"a: "<<bitset<8>(a);

	nibble = (nibble << 12);
	//cout<<endl<<"NIB: "<<bitset<8>(nibble);
	nibble = (nibble >> 12);
	//cout<<endl<<"NIB: "<<bitset<8>(nibble);

	int perm_scheme[8] = { 0, 3, 2, 1, 2, 1, 0, 3};
	for(int i = 1; i <= 8; i++){
		n = (nibble << (15 - perm_scheme[i-1]));
		n = (n >> 15);
		n = (n << (8 - i));
		//cout<<endl<<"N: "<<bitset<8>(n)<<"I: "<<i;
		//cout<<endl<<" EP: "<<bitset<8>(permuted);
		permuted = permuted | n;
		//cout<<endl<<"permuted: "<<bitset<8>(permuted);
		//cout<<endl<<" ";
	}
	//cout<<endl<<"permuted: "<<bitset<8>(permuted);
	//cout<<endl<<"SK: "<<sk;
	// cout<<endl;
	
	permuted = permuted ^ sk;
	permuted = (a >> 4) ^ permuted;


	permuted = sbox(permuted);
	cout<<endl<<"permuted: "<<permuted;
	permuted = p4(permuted);
	

	permuted = (a >> 4) ^ permuted;
	permuted = (permuted << 4);
	a = (a << 12);
	a = (a >> 12);
	permuted = permuted | a;

	return permuted;
}


unsigned short switch_nibs(unsigned short byte)
{
	//cout<<endl<<"byte: "<<byte;
	unsigned short nib1 = (byte << 12);
	nib1 = (nib1 >> 8);
	unsigned short nib2 = (byte >> 4);
	return nib1 | nib2; 
}

int main() {
	string message;
	unsigned short key1 = 0;
	unsigned short key2 = 0;
	
	char a = 'a';
	unsigned short sk = 0;

	//cout<<endl<<"P: "<<p;
	// sk = p;
	// p = f(a,sk);

	// p = sbox(p);
	// p = p4(p);

	cout<<endl<<"Enter Plain Text Message: ";
	getline(cin, message);
	cout<<endl<<"Enter 10-bit key as an unsigned short: ";
	cin >> key1;

	key1 = p10(key1);
	key2 = p10(key1);
	key1 = p8(key1);
	key2 = p8_shift2(key2);

	unsigned short plain_byte, cipher_byte;
	for(int i =0; i < message.length(); i++){
		plain_byte = message[i];
		cipher_byte = IP(plain_byte);
		cipher_byte = f(cipher_byte, key1);
		//cout<<endl<<"byte :"<<cipher_byte;
		cipher_byte = switch_nibs(cipher_byte);
		//cout<<endl<<"cipher byte: "<<cipher_byte;
		//cipher_byte = f(cipher_byte, key2);
		//cipher_byte = IP_inverse(cipher_byte);
		//cout << (char)cipher_byte;
		//cout << " ";
		//cout << cipher_byte;
	}
	cout << endl;


	//cout<<endl<<"CIRCLE LEFT SHIFT : "<< fk(a, sk);

	return 0;
}