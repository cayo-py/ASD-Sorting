#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

int *generate_random_int(int n)
{
    int *data = new int[n];
    for (int i = 0; i < n; i++)
    {
        data[i] = rand();
    }
    return data;
}

bool is_sorted(int *data, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (data[i - 1] > data[i])
        {
            return false;
        }
    }
    return true;
}

void sort(int *data, int n)
{
    // ... sorting algorithm implementation goes here ...
    if (n <= 1)
        return;
        
    int mid = n/2; //85671 423 n=8 mid=4
    int J1 = mid; // J1=4
    int J2 = n - mid; // J2=4

    int *T1 = new int[J1];
    int *T2 = new int[J2];

    for (int i = 0; i < J1; i++)
        T1[i] = data[i];
    for (int j = 0; j < J2; j++)
        T2[j] = data[mid + j];

    sort (T1, J1);
    sort (T2, J2);

    int i = 0;
    int j = 0;
    int t = 0;
    
    while ((i < J1) || (j < J2))
    {
        if (i < J1 && (j >= J2 || T1[i] < T2[j]))
        {
            data[t] = T1[i];
            i++;
        }
        else
        {
            data[t] = T2[j];
            j++;
        }
        t++;
    }

    if (i > J1)
        for (i=j; i<J2; i++)
        {
            data[t] = T2[i];
            t++;
        }
    if (j > J2)
        for (j=i; j<J1; j++)
        {
            data[t] = T1[j];
            t++;
        }

    delete[] T1;
    delete[] T2;
}

int main()
{
    int num_of_experiments = 100;
    int *data;
    int n;

    // DEBUG
    // The program will stop if the sorting is incorrect
    n = 100;
    data = generate_random_int(n);
    sort(data, n);
    if (!is_sorted(data, n))
    {
        throw runtime_error("Sorting function ERROR.");
    }

    // EXPERIMENTS
    cout << "data, time (ms)\n";
    cout << " \n";
    for (int i = 1; i <= num_of_experiments; i++)
    {
        n = i * 1000;
        data = generate_random_int(n);
        auto start = chrono::high_resolution_clock::now();
        sort(data, n);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << n << ", " << duration.count() << "\n";
        delete[] data;
    }

    return 0;
}
