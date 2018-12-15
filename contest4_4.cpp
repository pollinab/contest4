/*Дано невзвешенное дерево. Расстоянием между двумя вершинами будем называть количество ребер в пути, соединяющем эти две вершины. 
Для каждой вершины определите расстояние до самой удаленной от нее вершины.*/

#include<iostream>
#include<vector>

struct CNode //вершина дерева
{
    int height; //длина максимального пути вниз до листа
    int index_of_child1; //номер ребёнка, через которого проходит самый длинный путь вниз до листа
    int index_of_child2; //номер ребёнка, через которого проходит второй по длине путь вниз до листа
    int way_through_parent; //наибольшая длина пути через родителя
    std::vector <CNode*> children; //дети
    CNode()
    {
        height = 0;
        index_of_child1 = -1;
        index_of_child2 = -1;
        way_through_parent = 0;
    }
};

void Up(std::vector <CNode*> tree) //обход дерево снизу вверх с нахождением height для каждой вершины
{
    int max1, max2;
    for (int j = tree.size() - 1; j >= 0; --j)
    {
        if (tree[j] -> children.size() != 0)
        {
            max1 = -1; //максимум из height детей
            max2 = -1; //второе по величине значение
            for (int i = 0; i < tree[j] -> children.size(); ++i)
            {
                if (tree[j] -> children[i] -> height > max1)
                {
                    max2 = max1;
                    tree[j] -> index_of_child2 = tree[j] -> index_of_child1;
                    tree[j] -> index_of_child1 = i;
                    max1 = tree[j] -> children[i] -> height;
                }
                else if (tree[j] -> children[i] -> height > max2)
                {
                    tree[j] -> index_of_child2 = i;
                    max2 = tree[j] -> children[i] -> height;
                }
            }
            tree[j] -> height = max1 + 1;
        }
    }
}
//обход дерева сверху вниз с нахождением way_through_parent для каждой вершины
void Down(CNode* root, int longest_way) //второй аргумент - наибольшая длина пути через родителя
{
    root -> way_through_parent = longest_way;
    for (int i = 0; i < root -> children.size(); ++i)
    {
        if (i != root -> index_of_child1)
        {
            longest_way = std::max(root -> height, root -> way_through_parent);
            Down(root -> children[i], longest_way + 1);
        }
        else
        {
            if (root -> index_of_child2 != -1)
                longest_way = std::max(root -> children[root -> index_of_child2] -> height + 1, root -> way_through_parent);
            else //если ребёнок один
                longest_way = root -> way_through_parent;
            Down(root -> children[i], longest_way + 1);
        }
    }
}

int main()
{
    int n, v1, v2;
    std::cin >> n;
    std::vector <CNode*> tree(n);
    for (int i = 0; i < n; ++i)
    {
        tree[i] = new CNode;
    }
    for (int i = n - 1; i > 0; --i)
    {
        std::cin >> v1 >> v2;
        if (v1 > v2)
        {
            tree[v2] -> children.push_back(tree[v1]);
        }
        else
        {
            tree[v1] -> children.push_back(tree[v2]);
        }
    }
    Up(tree);
    Down(tree[0], 0);
    for (int i = 0; i < n; ++i)
    {
        std::cout << std::max(tree[i] -> height, tree[i] -> way_through_parent) << std::endl;
    }
    for (int i = 0; i < n; ++i)
    {
        delete tree[i];
    }
    return 0;
}
