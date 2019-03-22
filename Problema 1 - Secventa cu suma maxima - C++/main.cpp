//Modificare Ana 2
//Test pull
/*
Consideram un sir format din n numere intregi. Sa se determine o secventa a sa avand suma elementelor maxima.
O secventa a unui sir este formata din elemente ale sirului aflate pe pozitii consecutive.

Explicatii: https://infoarena.ro/problema/ssm
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;

//functie care genereaza un fisier de intrare format din n numere intregi cuprinse intre min si max
void genereaza(char nf[100], int n, int min, int max)
{
    int x;

    srand(time(NULL));

    ofstream fout(nf);
    fout << n << endl;

    for(int i = 0; i < n; i++)
    {
        x = min + rand()%(max - min + 1);
        fout << x << " ";
    }

    fout.close();
}

//complexitate O(n^3)
void varianta_1(int p[], int n)
{
    int	i, j, k, st, dr, scrt,smax;

    smax = p[0];
    st = dr = 0;
    for(i = 0; i < n; i++)
        for(j = i; j < n; j++)
        {
            scrt = 0;
            for(k = i; k <= j; k++)
                scrt = scrt + p[k];

            if(scrt > smax)
            {
                smax = scrt;
                st = i;
                dr = j;
            }
        }

    cout << "Varianta 1:" << endl;
    cout << "\tSuma maxima: " << smax << endl << "\tIndici: " << st << " -> " << dr << endl;
}

//complexitate O(n^2)
void varianta_2(int p[], int n)
{
    int	i, j, st, dr, scrt,smax;

    smax = p[0];
    st = dr = 0;
    for(i = 0; i < n; i++)
    {
        scrt = 0;
        for(j = i; j < n; j++)
        {
            scrt = scrt + p[j];

            if(scrt > smax)
            {
                smax = scrt;
                st = i;
                dr = j;
            }
        }
    }

    cout << "Varianta 2:" << endl;
    cout << "\tSuma maxima: " << smax << endl << "\tIndici: " << st << " -> " << dr << endl;
}

//complexitate O(n)
void varianta_3(int p[], int n)
{
    int	i, aux, st, dr, scrt,smax;

    smax = INT_MIN;
    aux = 0;
    scrt = 0;

    for(i = 0; i < n; i++)
    {
        if(scrt < 0)
        {
            scrt = p[i];
            aux = i;
        }
        else
            scrt = scrt + p[i];

        if(scrt > smax)
        {
            smax = scrt;
            st = aux;
            dr = i;
        }
    }

    cout << "Varianta 3:" << endl;
    cout << "\tSuma maxima: " << smax << endl << "\tIndici: " << st << " -> " << dr << endl;
}

int main()
{
    ifstream fin("date.in");

    int n, min, max;

    cout << "n = ";
    cin >> n;

    cout << "min = ";
    cin >> min;

    cout << "max = ";
    cin >> max;

    genereaza("date.in", n, min, max);

    fin >> n;

    int *p = new int[n];

    for(int i = 0; i < n; i++)
        fin >> p[i];

    fin.close();

    cout << endl;

    double t3 = clock();
    varianta_3(p, n);
    t3 = clock() - t3;
    cout << "    Timp: " << t3/CLOCKS_PER_SEC << " s" << endl << endl;

    double t2 = clock();
    varianta_2(p, n);
    t2 = clock() - t2;
    cout << "    Timp: " << t2/CLOCKS_PER_SEC << " s" << endl << endl;

    double t1 = clock();
    varianta_1(p, n);
    t1 = clock() - t1;
    cout << "    Timp: " << t1/CLOCKS_PER_SEC << " s" << endl << endl;

    return 0;
}
