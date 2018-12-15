#include<iostream>
#include<vector>

struct CNode
{
    int height;
    int index_of_child1;
    int index_of_child2;
    int way_through_parent;
    std::vector <CNode*> children;
    CNode()
    {
        height = 0;
        index_of_child1 = -1;
        index_of_child2 = -1;
        way_through_parent = 0;
    }
};

void Up(std::vector <CNode*> tree)
{
    int max1, max2;
    for (int j = tree.size() - 1; j >= 0; --j)
    {
        if (tree[j] -> children.size() != 0)
        {
            max1 = -1;
            max2 = -1;
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

void Down(CNode* root, int longest_way)
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
            else
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
