/*
Consideram un sir de numere naturale ordonate strict crescator si un numar natural s.
Sa se determine toate perechile cu elemente distincte din sir care su suma s.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

//functie pentru generarea unui fisier de test
void generareSirStrictCrescator(char nf[] , unsigned int n)
{
	unsigned int i , j , *r;

	r = new unsigned int[n];

	srand(time(NULL));

	r[0] = rand() % 100;
	for(i = 1; i < n; i++)
		r[i] = r[i - 1] + 1 + rand () % 20;

	i = (rand() * rand()) % n;

	do
	{
		j = (rand() * rand()) % n;
	}
	while(i == j);

	ofstream fout(nf);

	fout << n << " " << r[i] + r[j] << endl;

	for(i = 0; i < n; i++)
		fout << r[i] << " ";

	delete []r;

	fout.close();
}

//cautarea directa a perechilor, respectiv
//cautarea liniara a valorii s-p[i] complementara valorii p[i]
void varianta_1(unsigned int p[] , unsigned int n , unsigned int s)
{
	unsigned int i , j;

	for(i = 0; i < n - 1; i++)
		if(p[i] != 0)
			for(j = i + 1; j < n; j++)
				if(p[j] == s - p[i])
				{
					cout << "Produsul " << i + 1 << " (" << p[i] << " RON) si produsul " << j + 1 << " (" << p[j] << " RON)" << endl;
					p[j] = 0;
					break;
				}
}

//cautarea binara a valorii s-p[i] complementara valorii p[i]
void varianta_2(unsigned int p[] , unsigned int n , unsigned int s)
{
	unsigned int i , st , dr , m;

	for(i = 0; i < n - 1; i++)
	{
		st = i + 1;
		dr = n - 1;

		while(st <= dr)
		{
			m = (st + dr) / 2;
			if(s - p[i] == p[m])
			{
				cout << "Produsul " << i + 1 << " (" << p[i] << " RON) si produsul " << m + 1 << " (" << p[m] << " RON)" << endl;
				break;
			}
			else
				if(s - p[i] < p[m])
					dr = m - 1;
				else
					st = m + 1;
		}
	}
}

//vector de marcaje, respectiv
//cautarea directa a valorii s-p[i] complementara valorii p[i]
void varianta_3(unsigned int p[] , unsigned int n , unsigned int s)
{
	unsigned int i;

	int *m = new int[s];

	for(i = 0; i < s; i++)
		m[i] = -1;

	for(i = 0; i < n; i++)
		if(p[i] < s)
			m[p[i]] = i;
		else
			break;

	for(i = 0; i < n; i++)
		//if(p[i] < s/2 && 2*p[i] != s && p[i] != 0 && m[s - p[i]] != -1)
		if(p[i] < s/2 && m[s - p[i]] != -1)
		{
			cout << "Produsul " << i + 1 << " (" << p[i] << " RON) si produsul " << m[s - p[i]] + 1 << " (" << s - p[i] << " RON)" << endl;
			//p[m[s - p[i]]] = 0;
		}
}

//arderea lumanarii la doua capete
void varianta_4(unsigned int p[] , unsigned int n , unsigned int s)
{
	unsigned int st , dr;

	st = 0;
	dr = n - 1;

	while(st < dr)
	{
		if(p[st] + p[dr] == s)
		{
			cout << "Produsul " << st + 1 << " (" << p[st] << " RON) si produsul " << dr + 1 << " (" << p[dr] << " RON)" << endl;
			st++;
			dr--;
		}
		else
			if(p[st] + p[dr] < s)
				st++;
			else
				dr--;
	}
}

int main()
{
	unsigned int i , n , s , *p, *aux;
	double t;

	generareSirStrictCrescator("date.in" , 1000);

	ifstream fin("date.in");

	fin >> n >> s;
	p = new unsigned int[n];

	for(i = 0; i < n; i++)
		fin >> p[i];

	fin.close();

	aux = new unsigned int[n];
	memcpy(aux , p , n * sizeof(unsigned int));


	cout << "Suma dorita: " << s << endl << endl;

	t = clock();
	varianta_4(p , n , s);
	t = clock() - t;
	cout << endl << "Timp de executare pentru varianta 4: " << t / CLOCKS_PER_SEC << "s" << endl << endl << endl;

	t = clock();
	varianta_3(p , n , s);
	t = clock() - t;
	cout << endl << "Timp de executare pentru varianta 3: " << t / CLOCKS_PER_SEC << "s" << endl << endl << endl;

	memcpy(p , aux , n * sizeof(unsigned int));

	t = clock();
	varianta_2(p , n , s);
	t = clock() - t;
	cout << endl << "Timp de executare pentru varianta 2: " << t / CLOCKS_PER_SEC << "s" << endl << endl << endl;

	t = clock();
	varianta_1(p , n , s);
	t = clock() - t;
	cout << endl << "Timp de executare pentru varianta 1: " << t / CLOCKS_PER_SEC << "s" << endl << endl << endl;

	delete []p;
	delete []aux;

	return 0;
}
