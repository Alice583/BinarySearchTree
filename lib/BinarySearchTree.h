#include <memory>
// T - type data, Compare - для сравнения, Alloc - память
template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T>>
class BinarySearchTree {
public:
    struct Node {
        Alloc alloc;
        T* key;
        Node* parent;
        Node* right;
        Node* left;

        Node() {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        // construct_at(where - allocate(how match, what))
        Node(T key) :key(std::construct_at(alloc.allocate(1), key)), parent(nullptr), right(nullptr), left(nullptr) {}

        Node(Node* other) : alloc(other->alloc) {
            if (other->key == nullptr) {
                key = nullptr;
            } else {
                key = std::construct_at(alloc.allocate(1), *other->key);
            }

            if (other->right == nullptr) {
                right = nullptr;
            } else {
                right = new Node(*other->right);
                right->parent = this;
            }

            if (other->left == nullptr) {
                left = nullptr;
            } else {
                left = new Node(*other->left);
                left->parent = nullptr;
            }
            parent = nullptr;
        }

        ~Node() {
            std::destroy_at(key); // здесь вызываем деструктор у key, тк чистим сначала то, что внутри ячейки
            alloc.deallocate(key, 1); // освобождает ячейку памяти
        }

        Node& operator=(const Node& other) {
            if (this != &other) {
                if (other.key == nullptr) {
                    if (key != nullptr) {
                        alloc.deallocate(key, 1);
                    }
                    key = nullptr;
                } else {
                    key = alloc.allocate(1);
                    *key = *other.key;
                }

                left = other.left;
                right = other.right;
            }
            return *this;
        }
    };

    BinarySearchTree() {
        root_ = nullptr;
        begin_ = nullptr;
        end_ = nullptr;
        size_ = 0;
    }

    BinarySearchTree(T i) {
        Node* new_node = new Node(i);
        root_ = new_node;
        begin_ = root_;
        end_ = root_;
        size_ = 1;
    }

    BinarySearchTree(BinarySearchTree& otherBinarySearchTree) {
        root_ = otherBinarySearchTree.root_;
        begin_ = otherBinarySearchTree.begin_;
        end_ = otherBinarySearchTree.end_;
        size_ = otherBinarySearchTree.size_;
    }

    BinarySearchTree(T i, T j, Compare c) {
        for (T cnt = i; c(cnt, j); ++cnt) {
            Insert(cnt);
        }
    }

    BinarySearchTree(T i, T j) {
        Compare checker;
        for (T cnt = i; checker(cnt, j); ++cnt) {
            Insert(cnt);
        }
    }


    ~BinarySearchTree() {
        DeleteTree(root_);
    }


    using key_type = T;
    using mapped_type = T;
    using value_type = T;
    using key_compare = Compare;
    using value_compare = Compare;
    using node_type = Node;

    struct PostOrder {
        Node* next(Node* start, Node* prev) {
            if (start == nullptr) {
                return prev;
            }

            if (start->parent == nullptr) {
                return nullptr;
            }
            if (start->parent->right == start) {
                return start->parent;
            }
            if (start == start->parent->left) {
                if (start->parent->right != nullptr) {
                    start = start->parent->right;
                    while (start->left != nullptr && start->right != nullptr) {
                        start = start->left;
                        if (start->right != nullptr && start->left == nullptr) {
                            start = start->right;
                        }
                    }
                    if (start->right != nullptr && start->left == nullptr) {
                        start = start->right;
                    }
                    if (start->right == nullptr && start->left != nullptr) {
                        start = start->left;
                    }
                    return start;
                }
                return start->parent;
            }
        }

        Node* prev(Node* start, Node* prev_step) {
            if (start == nullptr) {
                return prev_step;
            }
            if (start->right != nullptr) {
                return start->right;
            }
            if (start->left != nullptr) {
                return start->left;
            }
            if (start->parent->right == start && start->parent->left != nullptr) {
                return start->parent->left;
            }
            while (start->parent != nullptr) {
                if (start->parent->right == start) {
                    break;
                }
                start = start->parent;
            }
            if (start->parent != nullptr && start->parent->right == start && start->parent->left != nullptr) {
                return start->parent->left;
            }
            else return nullptr;
        }
    };

    struct InOrder {
        Node* next(Node*& start, Node*& prev) {
            if (start == nullptr) {
                return prev;
            }
            if (start->right != nullptr) {
                Node* cur = start->right;
                while (cur->left != nullptr) {
                    cur = cur->left;
                }
                start = cur;
                return cur;
            }
            else {
                while (start->parent != nullptr && start != start->parent->left) {
                    start = start->parent;
                }
                if (start->parent == nullptr || start->parent == nullptr) {
                    return nullptr;
                }
                start = start->parent;
                return start;
            }
        }

        Node* prev(Node* start, Node* prev_step) {
            if (start == nullptr) {
                return prev_step;
            }
            if (start->left != nullptr) {
                start = start->left;
                while (start->right != nullptr) {
                    start = start->right;
                }
                return start;
            }

            while (start->parent != nullptr && start != start->parent->right) {
                start = start->parent;
            }
            start = start->parent;
            return start;
        }
    };

    struct PreOrder {
        Node* prev(Node* start, Node* prev_step) {
            if (prev_step == nullptr) {
                return prev_step;
            }

            if (start->parent == nullptr) {
                return nullptr;
            }

            if (start->parent->left != nullptr && start != start->parent->left) {
                start = start->parent->left;
                while (start->right != nullptr) {
                    start = start->right;
                }
                return start;
            }
            return start->parent;
        }

        Node* next(Node* start, Node* prev_step) {
            if (start == nullptr) {
                return prev_step;
            }
            if (start->left != nullptr) {
                return start->left;
            }
            if (start->right != nullptr) {
                return start->right;
            }
            if (start->left == nullptr && start->right == nullptr) {
                if (start->parent != nullptr && start == start->parent->left && start->parent->right != nullptr) {
                    return start->parent->right;
                }
                while (start->parent != nullptr && start != start->parent->left && start->parent->right != nullptr) {
                    start = start->parent;
                }
                if (start->parent != nullptr && start->parent->right != nullptr) {
                    return start->parent->right;
                }
                else {
                    return nullptr;
                }
            }
        }
    };

    template<typename Order>
    class Iterator {

    protected:
        Node* pointer;
        Node* prev_pointer;
        friend BinarySearchTree;

    public:
        Iterator(Node* node = nullptr) {
            pointer = node;
            prev_pointer = nullptr;
        }

        Iterator(const Iterator& otherIterator) = default;

        ~Iterator() = default;

        Iterator& operator++() {
            Order order;
            if (pointer != nullptr) {
                prev_pointer = pointer;
            }
            pointer = order.next(pointer, prev_pointer);
            return *this;
        }

        Iterator& operator++(int) {
            pointer = Order::next(pointer);
            return *this;
        };

        Iterator& operator--() {
            Order order;
            if (pointer == nullptr && pointer->parent == nullptr && pointer->parent->left == pointer && pointer->parent->right == pointer) {
                if (pointer != nullptr) {
                    prev_pointer = pointer;
                }
                pointer = order.prev(pointer, prev_pointer);
            }
            else {
                pointer = pointer->parent;
            }
            return *this;
        }

        bool operator==(const Iterator<Order>& otherIterator) const {
            return (pointer == otherIterator.getConstPtr());
        }

        bool operator!=(const Iterator<Order>& otherIterator) const {
            return (pointer != otherIterator.getConstPtr());
        }

        Node* operator*() const {
            return pointer;
        }

        Node* operator->() {
            return pointer;
        }

        Node* getPtr() const { return pointer; }

        const Node* getConstPtr() const { return pointer; }
    };


    template<typename order=InOrder>
    Iterator<order> begin() {
        if constexpr (std::is_same<order, PreOrder>::value) {
            Iterator<order> iterator(root_);
            return iterator;
        }
        else if constexpr (std::is_same<order, PostOrder>::value) {
            Node* first = root_;
            while (first->left != nullptr && first->right != nullptr) {
                first = first->left;
                if (first->right != nullptr && first->left == nullptr) {
                    first = first->right;
                }
                if (first->right == nullptr && first->left != nullptr) {
                    first = first->left;
                }
            }

            if (first->right != nullptr && first->left == nullptr) {
                first = first->right;
            }
            if (first->right == nullptr && first->left != nullptr) {
                first = first->left;
            }
            Iterator<order> i(first);
            first = nullptr;
            delete first;
            return i;
        }
        else {
            Iterator<order> iterator(begin_);
            return iterator;
        }
    }
    template<typename order=InOrder>
    Iterator<order> end() {
        if (std::is_same<order, PostOrder>::value
            || (*end_->key < *root_->key && std::is_same<order, InOrder>::value)) {
            Node* after_end = new Node();
            after_end->parent = root_;
            Iterator<order> i(after_end);
            return i;
        }

        else {
            Node* after_end = new Node();
            after_end->parent = end_;

            Iterator<order> i(after_end);
            return i;
        }
    }



    template<typename order=InOrder>
    Iterator<order> rend() {
        return begin<order>();
    }

    template<typename order=InOrder>
    const Iterator<order> crend() {
        return cbegin<order>();
    }

    template<typename order=InOrder>
    const Iterator<order> cbegin() {
        return const_cast<const BinarySearchTree&>(this).begin();
    }

    template<typename order=InOrder>
    const Iterator<order> crbegin() {
        return cend<order>();
    }

    template<typename order=InOrder>
    const Iterator<order> rbegin() {
        return end<order>();
    }

    template<typename order=InOrder>
    const Iterator<order> cend() {
        return const_cast<const BinarySearchTree&>(this).end();
    }

    void clear() {
        DeleteTree();
        end_ = begin_;
    }


    size_t max_size() {
        return size_ + 1;
    }

    key_compare key_comp() {
        Compare i;
        return i;
    }

    value_compare value_comp() {
        Compare i;
        return i;
    }


    bool empty() {
        return root_ == nullptr;
    }

    size_t size() {
        return size_;
    }

    void Insert(T value) {
        InsertNode(root_, value);
    }

    void Insert(Node*& node) {
        InsertNode(root_, *node->key);
    }

    void Insert(T i, T j) {
        for (T cnt = i; Compare(cnt, j); ++cnt)
            InsertNode(root_, cnt);
    }

    BinarySearchTree& operator=(const BinarySearchTree& other_tree) {
        DeleteTree(root_);
        root_ = nullptr;
        if (*this != other_tree) {
            DeleteTree(other_tree.root_);
        }
        return *this;
    }

    BinarySearchTree& operator=(const std::initializer_list<T>& il_initializer_list) {
        DeleteTree(root_);
        for (T cnt: il_initializer_list)
            insert(cnt);
        return *this;
    }

    bool operator==(const BinarySearchTree& other) {
        if (size_ != other.size_) {
            return false;
        }
        return CompareTrees(root_, other.root_);
    }

    bool operator!=(const BinarySearchTree& other) {
        return *this != other;
    }

    void merge(BinarySearchTree &other) {
        for (size_t i = 0; i < other.size_; ++i) {
            Node* extracted = Extract(*other.root->key);
            if (extracted != nullptr) {
                Insert(*extracted->key);
                extracted = nullptr;
                delete extracted;
            }
        }
    }
    BinarySearchTree& swap(BinarySearchTree& other_tree) {
        std::swap(root_, other_tree.root_);
        std::swap(begin_, other_tree.begin_);
        std::swap(end_, other_tree.end_);
        auto tmp = size_;
        size_ = other_tree.size_;
        other_tree.size_ = tmp;
        return *this;
    }

    template<typename order = InOrder>
    Iterator<order> get_allocator() {
        Iterator<order> iterator;
        return iterator;
    }

    bool contains(T k) {
        if (Find(k, root_) != nullptr) {
            return true;
        }
        return false;
    }

    template<typename order = InOrder>
    Iterator<order> find(T num) {
        Node* found = Find(num, root_);
        Iterator<order> iterator(found);
        return iterator;
    }


    template<typename order = InOrder>
    Iterator<order> upper_bound(T x) {
        Node* current = root_;
        Node* last_suitable = nullptr;
        while (current != nullptr) {
            if (x >= *current->key) {
                current = current->right;
            }
            else {
                last_suitable = current;
                current = current->left;
            }
        }
        Iterator<order> iterator(last_suitable);
        current = nullptr;
        last_suitable = nullptr;
        delete current;
        delete last_suitable;
        return iterator;
    }


    template<typename order = InOrder>
    Iterator<order> lower_bound(T x) {
        Node* current = root_;
        Node* last_suitable = nullptr;
        while (current != nullptr) {
            if (x <= *current->key) {
                current = current->left;
            }
            else {
                last_suitable = current;
                current = current->right;
            }
        }
        Iterator<order> iterator(last_suitable);
        current = nullptr;
        last_suitable = nullptr;
        delete current;
        delete last_suitable;
        return iterator;
    }

    size_t count(T k) {
    if (Find(k, root_) != nullptr) {
        return 1;
    }
    else return 0;
    }

    template<typename order=InOrder>
    Iterator<order> extract(Iterator<order> x) {
        return extract(x.getPtr());
    }

    void erase(const T x) {
        extract(x);
    }

    template<typename order=InOrder>
    Node* extract(T x) {
        Node* cur = root_;
        while (cur != nullptr) {
            if (*cur->key == x) {
                break;
            }
            if (x > *cur->key) {
                cur = cur->right;
            }
            else {
                cur = cur->left;
            }
        }
        if (cur == nullptr) {
            delete cur;
            return end_;
        }
        size_--; {
            if (cur->left == nullptr && cur->right == nullptr) {
                if (cur == root_) {
                    root_ = nullptr;
                    return cur;
                }
                if (cur->parent->right == cur) {
                    cur->parent->right = nullptr;
                }
                else if (cur->parent->left == cur) {
                    cur->parent->left = nullptr;
                }
                return cur;
            }
            else if (cur->right == nullptr || cur->left == nullptr) {
                if (cur->left == nullptr) {
                    if (cur == root_) {
                        root_ = cur->right;
                        root_->parent = nullptr;
                        return cur;
                    }
                    if (cur->parent->left == cur) {
                        cur->parent->left = cur->right;
                    }
                    else {
                        cur->parent->right = cur->right;
                    }
                    cur->right->parent = cur->parent;
                    return cur;
                }
                else {
                    if (cur == root_) {
                        root_ = cur->left;
                        root_->parent = nullptr;
                        return cur;
                    }
                    if (cur->parent->left == cur) {
                        cur->parent->left = cur->left;
                    }
                    else {
                        cur->parent->right = cur->left;
                    }
                    cur->left->parent = cur->parent;
                    return cur;
                }
            }
            else if (cur->right != nullptr && cur->left != nullptr) {
                Node* last_correct = next(*cur->key);
                cur->key = last_correct->key;
                if (last_correct->parent->right == last_correct) {
                    last_correct->parent->right = last_correct->right;
                    if (last_correct->right != nullptr) {
                        last_correct->right->parent = last_correct->parent;
                    }
                }
                else {
                    last_correct->parent->left = last_correct->right;

                    if (last_correct->right != nullptr) {
                        last_correct->right->parent = last_correct->parent;
                    }
                }
                return cur;
            }
        }
    }

    template<typename order=InOrder>
    void swap(BinarySearchTree a, BinarySearchTree b) {
        a.swap(b);
    }


private:
    Node* root_;
    Node* begin_;
    Node* end_;
    size_t size_;
    Iterator<InOrder> inorder_iterator;
    Iterator<PreOrder> preorder_iterator;
    Iterator<PostOrder> postorder_iterator;

    void DeleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }

    void ReBuildTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        Insert(*node->key);
        ReBuildTree(node->left);
        ReBuildTree(node->right);
    }

    bool CompareTrees(Node* node1, Node* node2) {
        if (node1 == nullptr && node2 == nullptr)
            return true;
        else if ((node1 == nullptr && node2 != nullptr) || (node1 != nullptr && node2 == nullptr)) {
            return false;
        } else if (node1->key != node2->key) {
            return false;
        }
        return (CompareTrees(node1->left, node2->left) && CompareTrees(node1->right, node2->right));
    }

    Node* InsertNode(Node* node, T value) {
        if (node == nullptr) {
            root_ = new Node(value);
            size_++;
            begin_ = root_;
            end_ = root_;
            return root_;
        }
        if (value < *node->key) {
            if (node->left != nullptr) {
                InsertNode(node->left, value);
            }
            else {
                Node* new_leaf = new Node(value);
                node->left = new_leaf;
                new_leaf->parent = node;
                if (*new_leaf->key < *begin_->key) {
                    begin_ = new_leaf;
                }
                if (new_leaf == end_->left)
                    end_ = new_leaf;
                size_++;
                return node;
            }
        }
        if (value > *node->key) {
            if (node->right != nullptr) {
                InsertNode(node->right, value);
            }
            else {
                Node* new_leaf = new Node(value);
                node->right = new_leaf;
                new_leaf->parent = node;
                if (*new_leaf->key > *end_->key)
                    end_ = new_leaf;
                size_++;
                return node;
            }
        }
        return node;
    }

    Node* Find(T name, Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            while (!((*node->key > name && node->left == nullptr) || (
                    *node->key < name && node->right == nullptr))) {
                if (*node->key == name) {
                    return node;
                }
                else if (*node->key > name) {
                    node = node->left;
                }
                else {
                    node = node->right;
                }
            }

            return nullptr;
        }
    }

    Node* next(T x) {
        Node* current = root_;
        Node* last_suitable = nullptr;
        while (current != nullptr) {
            if (x >= *current->key) {
                current = current->right;
            }
            else {
                last_suitable = current;
                current = current->left;
            }
        }
        return last_suitable;
    }

    void set_begin() {
        Node* cur = root_;
        while (cur->left != nullptr) {
            cur = cur->left;
        }
        begin_ = cur;
        cur = nullptr;
        delete cur;
    }

    void set_end() {
        Node* cur = root_;
        while (cur->right != nullptr) {
            cur = cur->right;
        }
        end_ = cur;
        cur = nullptr;
        delete cur;
    }

};
