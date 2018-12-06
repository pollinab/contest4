#include<iostream>
#include<vector>

long long HashFunction(std::string str, long long tableSize);

struct HashTable
{
    std::vector <std::pair<int, std::string>> table;
    long long number;
    HashTable()
    {
        table.assign(8, std::make_pair(-1, ""));
        number = 0;
    }
    void NewHash()
    {
        std::vector <std::pair<int, std::string>> prev;
        prev = table;
        table.assign(table.size() * 2, std::make_pair(-1, ""));
        for (long long i = 0; i < prev.size(); ++i)
        {
            if (prev[i].first == 1)
                Insert(prev[i].second);
        }
    }
    void Insert(std::string str)
    {
        if ((number + 1) * 4 >= table.size() * 3)
            NewHash();
        long long Hash = HashFunction(str, table.size());
        long long index = Hash;
        for (int j = 1; table[index].first == 1; ++j)
        {
            index = (index + j) % table.size();
        }
        table[index].first = 1;
        table[index].second = str;
        ++number;
    }
    bool Find(std::string str)
    {
        long long Hash = HashFunction(str, table.size());
        long long index = Hash;
        for (long long j = 1; table[index].first != -1; ++j)
        {
            if (table[index].first == 1 && table[index].second == str)
            {
                return true;
            }
            index = (index + j) % table.size();
            if (index == Hash)
                return false;
        }
        return false;
    }
    bool Delete(std::string str)
    {
        int Hash = HashFunction(str, table.size());
        int index = Hash;
        for (long long j = 1; table[index].first != -1; ++j)
        {
            if (table[index].first == 1 && table[index].second == str)
            {
                table[index].first = -2;
                --number;
                return true;
            }
            index = (index + j) % table.size();
            if (index == Hash)
                return false;
        }
        return false;
    }
};

long long HashFunction(std::string str, long long tableSize)
{
    const int a = 179;
    long long Hash = 0;
    for(long long i = 0; i < str.size(); ++i)
        Hash = (Hash * a + str[i]) % tableSize;
    return Hash;
}

int main()
{
    char c;
    std::string s;
    HashTable table;
    while (std::cin >> c >> s)
    {
        if (c == '+')
        {
            if (table.Find(s))
                std::cout << "FAIL" << std::endl;
            else
            {
                table.Insert(s);
                std::cout << "OK" << std::endl;
            }
        }
        else if (c == '-')
        {
            std::cout << (table.Delete(s) ? "OK" : "FAIL") << std::endl;
        }
        else
        {
            std::cout << (table.Find(s) ? "OK" : "FAIL") << std::endl;
        }
    }
    return 0;
}
