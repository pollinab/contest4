#include<iostream>
#include<vector>
#include<algorithm>

int main()
{
    int start, finish;
    std::vector <std::pair <int, int>> Requests;
    while (std::cin >> start >> finish)
    {
        Requests.push_back(std::make_pair(finish, start));
    }
    std::sort(Requests.begin(), Requests.end());
    int counter = 1;
    int currTime = Requests[0].first;
    for (int i = 1; i < Requests.size(); ++i)
    {
        while (i < Requests.size() && Requests[i].second < currTime)
            ++i;
        if (i < Requests.size())
        {
            ++counter;
            currTime = Requests[i].first;
        }
    }
    std::cout << counter;
    return 0;
}
