#include<iostream>

int main()
{
    int N;
    std::cin >> N;
    long long **arr = new long long* [N + 1];
    for (int j = 0; j < N + 1; ++j)
    {
        arr[j] = new long long [N + 1];
        arr[j][0] = 0;
        arr[0][j] = 1;
    }
    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 1; j < N + 1; ++j)
        {
            if (i - j >= 0)
                arr[i][j] = arr[i][j - 1] + arr[i - j][j];
            else
                arr[i][j] = arr[i][i];
        }
    }
    std::cout << arr[N][N];
    for (int j = 0; j < N + 1; ++j)
    {
        delete []arr[j];
    }
    delete []arr;
    return 0;
}

