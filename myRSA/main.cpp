#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;;

int bitlen = 15;

int mod_exp(int base, int exp, int mod)
{
	int tmp = 1;
	while (exp >= tmp)
		tmp <<= 1;
	tmp >>= 2;
	long long ret = base;
	//sqare and multiply;
	while (tmp > 0)
	{
		ret = ret*ret;
		ret %= mod;
		if (exp & tmp)
		{
			ret = ret * base;
			ret %= mod;
		}
		tmp >>= 1;
	}

	return ret;
}

bool miller_rabin(int num)
{
	// Real

	//blah;;;

	// Test
	int sq_rt = sqrt(num);
	for (int i = 2; i <= sq_rt; i++)
	{
		if (num % i == 0)
			return false;
	}
	return true;
}

bool Test(int a, int n)
{
	int t = 0, u;
	u = n - 1;
	while (u % 2 == 0)
	{
		++t;
		u = u / 2;
	}
	bool tmp;
	int x = mod_exp(a, u, n);
	for (int i = 1; i <= t; i++)
	{
		tmp = false;
		if (x == 1 || x == n - 1)
			tmp = true;
		x = mod_exp(x, 2, n);
		if (x = 1 && tmp)
			return true;
	}
	if (x != 1)
		return true;	
	else
		return false;
}

bool mill(int n)
{
	int a = rand() % n;
	while (1)
	{
		if (a > 1)
			break;
		a = rand() % n;
	}

	int t = 0;
	int d = n - 1;
	while (d % 2 == 0)
	{
		++t;
		d /= 2;
	}

	if (mod_exp(a, d, n) != 1)
		return false;
	
	int tmp = 1;
	for (int i = 0; i < t; i++)
	{
		if (mod_exp(a,tmp*d,n) != (n-1))
			return false;
		tmp *= 2;
	}
	return true;
	/*int a = rand() % n;
	while (1)
	{
		if (a > 1)
			break;
		a = rand() % n;
	}
		
	for (int i = 1; i < 9; i++)
	{
		int t;
		if (t = Test(a, n))
		{
			cout << "a : " << a << ", n : " << n << endl;
			cout << "Test : " << t << endl;
			return false;
		}
	}
	return true;
*/


	/*int q = num-1;
	int k = 0;
	while (q % 2 == 0)
	{
		k++;
		q /= 2;
	}
	int a;
	while ((a = rand() % (num - 1)) <= 1);

	if (mod_exp(a, q, num) == 1)
		return true;
	int tmp = 1;
	for (int j = 0; j < k; j++)
	{
		if (mod_exp(a, tmp*q, num) == num - 1)
			return true;
	}
	return false;*/
}

int create_prime_number()
{
	int ret = rand() % (1 << bitlen);

	while (miller_rabin(ret) == false)
	{
		ret = rand() % (1 << bitlen);
		//cout << ret << endl;
	}

	return ret;
}

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
int create_big_number()
{
	int ret = rand() % (1 << bitlen);
	ret <<= bitlen;
	ret += rand() % (1 << bitlen);
	return ret;
}

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
			return B2;
		Q = A3 / B3;
		t1 = A1 - Q*B1;
		t2 = A2 - Q*B2;
		t3 = A3 - Q*B3;
		A1 = B1; A2 = B2; A3 = B3;
		B1 = t1; B2 = t2; B3 = t3;
	}
}

int encrypt(int M, int e, int N)
{
	int C = mod_exp(M, e, N);
	return C;
}

int decrypt(int C, int d, int N)
{
	int D = mod_exp(C, d, N);
	return D;
}

int Extended_Euclid(int r1, int r2)
{
	int r, q, s, s1 = 1, s2 = 0, t, t1 = 0, t2 = 1, tmp = r1;

	while (r2)
	{
		q = r1 / r2;
		r = r1%r2;
		s = s1 - q*s2;
		t = t1 - q*t2;

		//printf("%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d\n", q, r1, r2, r, s1, s2, s, t1, t2, t);

		r1 = r2;
		r2 = r;
		s1 = s2;
		s2 = s;
		t1 = t2;
		t2 = t;
	}
	//printf("%4d %4d %4d      %4d %4d      %4d          \n\n", q, r1, r2, s1, s2, t1);

	//printf("s : %d , t : %d \n", s1, t1);

	if (r1 == 1) //역원이 있음
	{
		if (t1 < 0)
			t1 += tmp;
		return t1;
	}

	return 0;
}

int main()
{
	// Miller Rabin Test ......
	/////////////////////////////////
	for (int i = 4; i < 100; i++)
	{
		if (miller_rabin(i))
		{
			cout << "Number : " << i << endl;
			cout << mill(i) << endl;
		}
	}
	return 0;
	/////////////////////////////////

	srand(time(NULL));
	int p, q, N, phi;
	
	p = create_prime_number();
	q = create_prime_number();

	//testcase;
	//p = 17293;
	//q = 19051;

	N = p * q;
	phi = (p - 1)*(q - 1);

	int e = create_big_number();

	while (gcd(phi, e) != 1)
	{
		e = create_big_number();
	}

	//e = 17;

	int d;
	d = extended_euclid(phi, e);
	if (d < 0)
		d += phi;
	//int k = Extended_Euclid(phi, e); // test용
	
									 
	////////
	printf("p : %d\n", p);
	printf("q : %d\n", q);
	printf("N : %d\n", N);
	printf("phi : %d\n", phi);
	printf("e : %d\n", e);
	printf("d : %d\n", d);
	//printf("k : %d\n", k); // test용
	
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
	//////
}