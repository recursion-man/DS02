
#ifndef AVL_TREE
#define AVL_TREE

#include <memory>
#include <iostream>

template <class T>
struct Node
{
    Node *left, *right, *father;
    int height, nodes_in_sub_tree;
    T data;
    explicit Node(T data) : left(nullptr), right(nullptr), father(nullptr), height(0), nodes_in_sub_tree(0), data(data){};
};

template <class T>
void printPostOrder(Node<T> *v)
{
    if (v == nullptr)
        return;
    printPostOrder(v->left);
    printPostOrder(v->right);
    std::cout << v->data << " : " << v->nodes_in_sub_tree << std::endl;
}
template <class T>
Node<T> *find(Node<T> *v, T target)
{

    if (v == nullptr)
    {
        throw std::invalid_argument("no arg");
    }

    else if (target < v->data)
    {
        return find(v->left, target);
    }
    else if (target > v->data)
    {
        return find(v->right, target);
    }
    else
    {
        return v;
    }
}

template <class T>
int rank(Node<T> *const node)
{
    if (node == nullptr)
        return 0;
    return node->nodes_in_sub_tree;
}

template <class T>
Node<T> *selectInSubTree(Node<T> *v, int k)
{
    if (rank(v->left) == k - 1)
        return v;
    if (rank(v->left) > k - 1)
    {
        if (v->left == nullptr)
            throw std::invalid_argument("caught in Select, index was too small");
        return selectInSubTree(v->left, k);
    }
    else
    {
        if (v->right == nullptr)
            throw std::invalid_argument("caught in Select, index was too big");
        return selectInSubTree(v->right, k - 1 - rank(v->left));
    }
}

template <class T>
class Tree
{
public:
    Tree() : root(nullptr){};

    void printPost() { printPostOrder(root); }
    T findInTree(T target)
    {
        return find(root, target)->data;
    }

    const T &select(int k)
    {
        if (root == nullptr)
            throw std::invalid_argument("tree is epmty");
        return selectInSubTree(root, k)->data;
    }

    virtual void insertToTree(T new_data)
    {
        if (root == nullptr)
        {
            root = new Node<T>(new_data);
        }
        else
        {
            insert(root, new_data);
        }
    }

    virtual void removeFromTree(T data)
    {
        if (root == nullptr)
        {
            return;
        }
        root = remove(root, data);
    }

    virtual ~Tree()
    {
        deleteNodes(root);
    }

    void setRoot(Node<T> *new_root)
    {
        root = new_root;
    }

protected:
    Node<T> *root;
};

template <class T>
void deleteNodes(Node<T> *v)
{
    if (v != nullptr)
    {
        deleteNodes(v->left);
        deleteNodes(v->right);
        delete v;
    }
}

template <class T>
Node<T> *findMin(Node<T> *v)
{
    if (v == nullptr)
    {
        throw std::invalid_argument("no next arg");
    }
    while (v->left != nullptr)
    {
        v = v->left;
    }
    return v;
}

template <class T>
int h(Node<T> *const node)
{
    if (node == nullptr)
        return -1;
    return node->height;
}

template <class T>
void updateRank(Node<T> *node)
{
    int result = rank(node->left) + rank(node->right) + 1;
    node->nodes_in_sub_tree = result;
}

template <class T>
int updateHeight(Node<T> *node)
{
    int result = std::max(h(node->left), h(node->right)) + 1;
    node->height = result;
    return result;
}

template <class T>
Node<T> *insert(Node<T> *v, T new_data)
{
    if (v == nullptr)
    {
        return new Node<T>(new_data);
    }
    if (new_data < v->data)
    {
        v->left = insert(v->left, new_data);
        v->left->father = v;
    }
    else if (new_data > v->data)
    {
        v->right = insert(v->right, new_data);
        v->right->father = v;
    }
    else
    {
        throw std::invalid_argument("already exists");
    }
    updateRank(v);
    updateHeight(v);
    return v;
}
template <class T>
Node<T> *remove(Node<T> *v, T target)
{
    if (v == nullptr)
    {
        throw std::invalid_argument("arg doesn't exists");
    }
    if (target < v->data)
    {

        v->left = remove(v->left, target);
    }
    else if (target > v->data)
    {
        v->right = remove(v->right, target);
    }
    else
    {
        if (v->left == nullptr && v->right == nullptr)
        {
            delete v;
            return nullptr;
        }
        else if (v->left == nullptr)
        {
            v->right->father = v->right->father->father;
            Node<T> *temp = v->right;
            delete v;
            return temp;
        }
        else if (v->right == nullptr)
        {
            v->left->father = v->left->father->father;
            Node<T> *temp = v->left;
            delete v;
            return temp;
        }
        Node<T> *temp = findMin(v->right);
        v->data = temp->data;
        v->right = remove(v->right, temp->data);
    }
    updateRank(v);
    updateHeight(v);
    return v;
}

template <class T>
bool isBlanced(Node<T> *const node)
{
    if (std::abs(getBalance(node)) >= 2)
    {
        return false;
    }
    return true;
}

template <class T>
int getBalance(Node<T> *const node)
{
    return h(node->left) - h(node->right);
}

template <class T>
void increaseNumOfNodes(Node<T> *v)
{
    while (v != nullptr)
    {
        v->nodes_in_sub_tree++;
        v = v->father;
    }
}

template <class T>
void decreaseNumOfNodes(Node<T> *v)
{
    while (v != nullptr)
    {
        v->nodes_in_sub_tree--;
        v = v->father;
    }
}

template <class T>
class AVL_Tree : public Tree<T>
{
public:
    AVL_Tree() : Tree<T>(){};
    AVL_Tree(const AVL_Tree &) = delete;
    AVL_Tree(const AVL_Tree &&) = delete;
    void insertToTree(T new_data) override
    {
        this->Tree<T>::insertToTree(new_data);
        Node<T> *v, *p;
        v = find(this->root, new_data);
        increaseNumOfNodes(v);
        while (v->father != nullptr)
        {
            p = v->father;
            if (!isBlanced(p))
            {
                fix(p, this);
                return;
            }
            v = p;
        }
    };

    void removeFromTree(T target) override
    {
        Node<T> *v;
        v = find(this->root, target);
        v = v->father;
        this->Tree<T>::removeFromTree(target);
        decreaseNumOfNodes(v);
        while ((v != nullptr))
        {
            if (!isBlanced(v))
            {
                fix(v, this);
            }
            updateRank(v);
            updateHeight(v);
            v = v->father;
        }
    };
};
template <class T>
void changeFather(Node<T> *father, Node<T> *prev_son, Node<T> *new_son, AVL_Tree<T> *tree)
{
    if (father == nullptr)
    {
        new_son->father = nullptr;
        prev_son->father = new_son;
        tree->setRoot(new_son);
        return;
    }
    if (father->right == prev_son)
        father->right = new_son;

    else
        father->left = new_son;
    new_son->father = father;
    prev_son->father = new_son;
}

template <class T>
void LL(Node<T> *v, AVL_Tree<T> *tree)
{
    Node<T> *temp_father, *w;
    temp_father = v->father;
    w = v->left;
    Node<T> *w_right = w->right;
    changeFather<T>(temp_father, v, w, tree);
    v->left = w_right;
    if (w_right != nullptr)
        w_right->father = v;
    w->right = v;
    updateRank(v);
    updateRank(w);

    while (v != nullptr)
    {
        updateRank(v);
        updateHeight<T>(v);
        v = v->father;
    }
}
template <class T>
void RR(Node<T> *v, AVL_Tree<T> *tree)
{
    Node<T> *temp_father, *w;
    temp_father = v->father;
    w = v->right;
    Node<T> *w_left = w->left;
    changeFather<T>(temp_father, v, w, tree);
    v->right = w_left;
    if (w_left != nullptr)
        w_left->father = v;
    w->left = v;
    updateRank(v);
    updateRank(w);

    while (v != nullptr)
    {
        updateRank(v);
        updateHeight<T>(v);
        v = v->father;
    }
}

template <class T>
void RL(Node<T> *v, AVL_Tree<T> *tree)
{
    LL(v->right, tree);
    RR(v, tree);
}

template <class T>
void LR(Node<T> *v, AVL_Tree<T> *tree)
{
    RR(v->left, tree);
    LL(v, tree);
}

template <class T>
void fix(Node<T> *node, AVL_Tree<T> *tree)
{
    if (getBalance(node) == -2)
    {
        if (getBalance(node->right) < 1)
        {
            RR(node, tree);
        }
        else if (getBalance(node->right) == 1)
        {
            RL(node, tree);
        }
    }
    else if (std::abs(getBalance(node)) == 2)
    {
        if (getBalance(node->left) > -1)
        {
            LL(node, tree);
        }
        else if (getBalance(node->left) == -1)
        {
            LR(node, tree);
        }
    }
}

#endif // AVL_TREE
