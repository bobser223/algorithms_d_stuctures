#include <iostream>
#include <stack>

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    ~TreeNode()
    {
        delete left;
        delete right;
    }

};

class Tree
{
public:
    TreeNode *head;
    Tree() : head(nullptr) {};
    void Insert(int val) // Вставка числа val в Бінарне Дерево Пошуку
    {
        auto* new_node = new TreeNode(val);
        if (!head)
        {
            head = new_node;
            return;
        }


        auto* curr = head;
        TreeNode* parent = nullptr;
        while(curr)
        {
            parent = curr;
            if (new_node->val < curr ->val)
                curr = curr->left;
            else
                curr = curr->right;
//            parent = curr;
        }

        if (new_node->val < parent->val)
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }
    }
    int IsSameTree(Tree *p) // Повернути 1, якщо поточне дерево дорівнює p, інакше повернути 0
    {
        std::stack<std::pair<TreeNode*, TreeNode*>> st;
        st.push({this->head, p->head});
        while(!st.empty())
        {
            auto [n1, n2] = st.top(); st.pop();
            if (!n1 && !n2)
                continue;

            if ((n1 && !n2) || (!n1 && n2))
                return 0;
            if (n1->val != n2->val)
                return 0;

            st.push({n1->left, n2->left});
            st.push({n1->right, n2->right});
        }
        return 1;
    }
};



int main(){
    int size_1, size_2, buff;
    std::cin >> size_1;
    Tree t1, t2;

    for (int i = 0; i < size_1; i++)
    {
        std::cin >> buff;
        t1.Insert(buff);
    }

    std::cin >> size_2;

    if (size_1 != size_2)
    {
        std::cout << 0 << std::endl;
        return 0;
    }

    for (int i = 0; i < size_2; i++)
    {
        std::cin >> buff;
        t2.Insert(buff);
    }

    std::cout << t1.IsSameTree(&t2) << std::endl;
}