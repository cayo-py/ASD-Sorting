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

void sort(int *data, int L, int R)
{
    // ... sorting algorithm implementation goes here ...
    int i, j, x, temp;
    x = data[(L+R)/2];
    i = L;
    j = R;
    while (i <= j)
    {
        while (data[i] < x)
        {
            i++;
        }
        while (data[j] > x)
        {
            j--;
        }
        if (i <= j)
        {
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++; j--;
        }
    }

    if (L < j)
    {
        sort(data, L, j);
    }
    if (i < R)
    {
        sort(data, i, R);
    }
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
    sort(data, 0, n-1);
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
        sort(data, 0, n-1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << n << ", " << duration.count() << "\n";
        delete[] data;
    }

    return 0;
}