
#include <iostream>

template <typename KeyType, typename DataType>

class BST {

};

/*protected:

public:
    class Node {

    public:

        KeyType key;
        DataType data;
        Node* left;
        Node* right;

        Node(KeyType key, DataType data) {
            this->key = key;
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }

    };

    Node* root;
    int size;

    int stepCount; // число шагов предыдущей операции


public:
    BST(); // конструктор
    BST(const BST<KeyType, DataType>& tree); // конструктор копирования
private:
    void copy(Node* node);
public:
    ~BST(); // деструктор
private:
    //destroyNode(Node* node);
public:
    int getSize(); // опрос размера дерева
    void clear(); // очистка дерева
private:
    void clearNode(Node* node); // рекурсивная очистка поддерева
public:
    bool isEmpty(); // проверка дерева на пустоту
    DataType read(KeyType key); // чтение по ключу
    bool write(KeyType key, DataType data); // запись по [существующему] ключу
    bool insert(KeyType key, DataType data); // включение данных по [новому] ключу
private:
    Node* insert_recursively(KeyType key, DataType data, Node* node); // рекурсивное включение данных по ключу
public:
    bool remove(KeyType key); // удаление данных по ключу
private:
    bool remove(KeyType key, Node* parent, Node* current); // рекурсивное удаление данных по ключу
public:
    void printKeys(); // вывод списка ключей дерева в порядке обхода узлов
    int serialNumber(KeyType key); // определение порядкового номера для элемента с заданным ключом (исключение)
    void show(); // вывод
    int getStepCount(); // число узлов, просмотренных предыдущей операцией

private:

    Node* getNode(KeyType key, Node* node); //  рекурсивная функция поиска нужного узла

    Node* getNext(Node* cur);
    Node* getPrev(Node* cur);

public:

    class Iterator
    {

    private:

        Node* cur;
        BST* tree;

    public:

        Iterator(Node* ptr = nullptr) {
            cur = ptr;
        }
        Iterator(const Iterator& iterator) {
            cur = iterator.cur;
        }

        bool operator==(const Iterator& lhs) const
        {
            return (cur == lhs.cur);
        }

        bool operator!=(const Iterator& lhs) const
        {
            return (cur != lhs.cur);
        }

        Iterator operator++()
        {
            if (cur == nullptr) throw std::exception("exception");

            cur = tree->getNext(cur);
            return cur;


            // симметричный обход: left -> t -> right
            if (cur->right == nullptr) 
            {
                cur = curRoot; // если нет правых потомков, идем к корню
            }
            else {
                cur = cur->right; // если есть правый потомок, идем к нему
                while (cur->left != nullptr) cur = cur->left; // если у правого потомка есть левые, находим самый левый
            }

            return *this;

        }

        Iterator operator--()
        {
            if (cur == nullptr) throw std::exception("exception");
            
            cur = tree->getPrev(cur);
            return cur;

            return *this;
        }

        DataType& operator*() const {
            if (cur == nullptr) throw std::exception("exception");
            return cur->data;
        }

    };


    class ReverseIterator
    {

    private:

        Node* cur;

    public:

        ReverseIterator(Node* ptr = nullptr) {
            cur = ptr;
        }
        ReverseIterator(const ReverseIterator& iterator) {
            cur = iterator.cur;
        }

        bool operator==(const ReverseIterator& lhs) const
        {
            return (cur == lhs.cur);
        }

        bool operator!=(const ReverseIterator& lhs) const
        {
            return (cur != lhs.cur);
        }

        ReverseIterator operator++()
        {
            if (cur == nullptr) throw std::exception("exception");
            //cur = cur->prev;
            return *this;
        }

        ReverseIterator operator--()
        {
            if (cur == nullptr) throw std::exception("exception");
            //cur = cur->next;
            return *this;
        }

        KeyType& operator*() const {
            if (cur == nullptr) throw std::exception("exception");
            return cur->data;
        }

    };

    friend class Iterator;
    friend class ReverseIterator;

    using iterator = Iterator;
    using reverse_iterator = ReverseIterator;

    iterator begin() { // возвращает самый левый узел
        //if (root != nullptr) return iterator();
        //else return iterator();
    }
    iterator end() { // возвращает самый правый узел
        //if (tail != nullptr) return iterator(tail->next);
        //else return iterator(); 
    }

    reverse_iterator rbegin() {
        //if (tail != nullptr) return reverse_iterator(tail);
        //else return reverse_iterator();
    }
    reverse_iterator rend() {
        //if (head != nullptr) return reverse_iterator(head->prev);
        //else return reverse_iterator();
    }


};


template<typename KeyType, typename DataType>
inline BST<KeyType, DataType>::BST()
{
    root = nullptr;
    size = 0;
    stepCount = 0;
}

template<typename KeyType, typename DataType>
inline BST<KeyType, DataType>::BST(const BST<KeyType, DataType>& tree)
{
    root = tree.root;
    size = tree.size;

    if (root) copy(tree.root);

}

template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::copy(Node* node)
{
    if (!node) return;

    add(node);

    if (node->left) copy(node->left);
    if (node->right) copy(node->right);
}

template<typename KeyType, typename DataType>
inline BST<KeyType, DataType>::~BST()
{
    clear();
}

template<typename KeyType, typename DataType>
inline int BST<KeyType, DataType>::getSize()
{
    return size;
}



template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::clear()
{
    clear(root);
    root = nullptr;
}


template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::clearNode(Node* node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);

        delete node;
        this->size--;
    }
}

template<typename KeyType, typename DataType>
inline bool BST<KeyType, DataType>::isEmpty()
{
    return (root == nullptr);
}

/*
template<typename KeyType, typename DataType>
inline DataType BST<KeyType, DataType>::read(KeyType key)
{
    Node* node = getNode(key, root);
    if (node == nullptr) throw std::exception("exception");
    else return node->data;
}


template<typename KeyType, typename DataType>
inline bool BST<KeyType, DataType>::write(KeyType key, DataType data)
{
    Node* node = getNode(key, root);
    if (node == nullptr) throw std::exception("exception");
    else node->data = data;
    
}


template<typename KeyType, typename DataType>
inline bool BST<KeyType, DataType>::insert(KeyType key, DataType data)
{
    root = insert_recursively(key, data, this.root);
    
}

template<class KeyType, class DataType>
BST<KeyType, DataType>::Node* BST<KeyType, DataType>::insert_recursively(KeyType key, DataType data, Node* node)
{

    if (!node) {
        return new Node(key, data);
    }

    if (key < node->key) {
        node->left = insert_recursively(key, data, node->left);
    }

    else if (key > node->key) {
        node->right = insert_recursively(key, data, node->right);
    }

    else // if (key == node->key)
    {
        return node;
    }
}
*/