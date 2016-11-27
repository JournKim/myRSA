#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;;

// set bit length
int bitlen = 15;

// return base^exp % mod
int mod_exp(int base, int exp, int mod)
{
	// tmp : pointer for square and multiply
	int tmp = 1;
	while (exp >= tmp)
		tmp <<= 1;
	tmp >>= 2;

	//sqare and multiply
	long long ret = base;
	while (tmp > 0)
	{
		// square
		ret = ret*ret;
		ret %= mod;

		// multiply
		if (exp & tmp)
		{
			ret = ret * base;
			ret %= mod;
		}
		tmp >>= 1;
	}
	return (int)ret;
}

// Miller-Rabin test
bool Test(int n)
{
	int a = rand() % n-1;
	while(a <= 1)
		a = rand() % n-1;
	int k = 0, q;
	q = n - 1;
	while (q % 2 == 0)
	{
		++k;
		q = q / 2;
	}

	int x = mod_exp(a, q, n);

	if (x == 1)
		return true;

	for (int i = 0; i < k; i++)
	{
		if (x == n - 1)
			return true;
		
		x = mod_exp(x, 2, n);
	}
	return false;
}

// Run Test() round time.
// If num is prime number, return true;
bool miller_rabin(int num, int round)
{
	while (round--)
	{
		if (Test(num) == false)
			return false;
	}
	return true;
}

// return a 15bit prime number
int create_prime_number()
{
	int ret = rand() % (1 << bitlen);

	while (miller_rabin(ret, 20) == false)
	{
		ret = rand() % (1 << bitlen);
	}

	return ret;
}

// return gcd of a and b. (Euclidean Algorithm)
int gcd(int a, int b)
{
	int tmp;
	if (a < b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	if (a % b == 0)
		return b;

	else
		return gcd(b, a%b);
}

// Useless.
// return 30bit integer
int create_big_number()
{
	int ret = rand() % (1 << bitlen);
	ret <<= bitlen;
	ret += rand() % (1 << bitlen);
	return ret;
}

// return inverse of b for mod m
int extended_euclid(int m, int b)
{
	int A1 = 1, A2 = 0, A3 = m;
	int B1 = 0, B2 = 1, B3 = b;
	int Q;
	int t1, t2, t3;
	while (1)
	{
		if (B3 == 0)
			return -1;
		if (B3 == 1)
		{
			if (B2 < 0)
				B2 += m;
			return B2;
		}
			
		Q = A3 / B3;
		t1 = A1 - Q*B1;
		t2 = A2 - Q*B2;
		t3 = A3 - Q*B3;
		A1 = B1; A2 = B2; A3 = B3;
		B1 = t1; B2 = t2; B3 = t3;
	}
}

// RSA Encryption.
// Cyphertext is (M^e mod N)
int encrypt(int M, int e, int N)
{
	int C = mod_exp(M, e, N);
	return C;
}

// RSA Decryption.
// Decrypted text is (C^d mod N)
int decrypt(int C, int d, int N)
{
	int D = mod_exp(C, d, N);
	return D;
}

int main()
{
	srand((unsigned int)time(NULL));
	int p, q, N, phi;
	
	// get prime number p,q
	p = create_prime_number();
	q = create_prime_number();

	// set N, phi(totient N)
	N = p * q;
	phi = (p - 1)*(q - 1);

	// get 30bit e that gcd(phi,e)=1
	//int e = create_big_number();
	//while (gcd(phi, e) != 1)
	//{
	//	e = create_big_number();
	//}
	int e = 257;

	// set d is inverse of e
	int d = extended_euclid(phi, e);
				 
	// print values
	printf("p = %d\n", p);
	printf("q = %d\n", q);
	printf("N = %d\n", N);
	printf("phi = %d\n", phi);
	printf("e = %d\n", e);
	printf("d = %d\n", d);
	
	// Input Message Number
	int M;
	cout << "Message Input : ";
	cin >> M;
	cout << "Message = " << M << endl;
	
	// Encryption
	cout << "**Encryption" << endl;
	int C = encrypt(M, e, N);
	cout << "cipher = " << C << endl;
	
	// Decryption
	cout << "**Decryption" << endl;
	int D = decrypt(C, d, N);
	cout << "decrypted cipher : " << D << endl;
	
}