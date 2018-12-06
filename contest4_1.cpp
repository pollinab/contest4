#include<iostream>
#include<vector>

long long HashFunction(std::string str, long long tableSize);

struct HashTable //хеш-таблица
{
    std::vector <std::pair<int, std::string>> table;
    long long number;
    HashTable()
    {
        table.assign(8, std::make_pair(-1, "")); //начальный размер таблицы 8, все элементы помечены -1
        number = 0;
    }
    void NewHash() //перехеширование
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
    void Insert(std::string str) //добавление строки
    {
        if ((number + 1) * 4 >= table.size() * 3)
            NewHash();                             //если нужно, выполняем перехеширование
        long long Hash = HashFunction(str, table.size());
        long long index = Hash;
        for (int j = 1; table[index].first == 1; ++j) //элемент помечен 1, если он был добавлен и не удален
        {
            index = (index + j) % table.size(); //квадратичное пробирование
        }
        table[index].first = 1; 
        table[index].second = str;
        ++number;
    }
    bool Find(std::string str) //поиск строки
    {
        long long Hash = HashFunction(str, table.size());
        long long index = Hash;
        for (long long j = 1; table[index].first != -1; ++j) //элемент помечен -1, если он не был добавлен
        {
            if (table[index].first == 1 && table[index].second == str)
            {
                return true;
            }
            index = (index + j) % table.size();
            if (index == Hash) //если обошли всю таблицу, возвращаем false
                return false;
        }
        return false;
    }
    bool Delete(std::string str) //удаление строки, возвращает false, если строка не найдена
    {
        int Hash = HashFunction(str, table.size());
        int index = Hash;
        for (long long j = 1; table[index].first != -1; ++j)
        {
            if (table[index].first == 1 && table[index].second == str)
            {
                table[index].first = -2; //помечаем -2 удаленные элементы
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

long long HashFunction(std::string str, long long tableSize) //хеш-функция методом Горнера
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
            if (table.Find(s)) //проверяем, чтобы не возникло повторений
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
