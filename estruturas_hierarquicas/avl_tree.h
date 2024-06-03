// Copyright [2024] <Emanuelle Guse>

#include "array_list.h"

namespace structures {

template<typename T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data);

        T data;
        int height_;
        Node* left;
        Node* right;

        void insert(const T& data_, Node*& node);
        bool remove(const T& data_, Node*& node);
        bool contains(const T& data_) const;
        void updateHeight();
        int balanceFactor() const;

        Node* simpleLeft();
        Node* simpleRight();
        Node* doubleLeft();
        Node* doubleRight();

        void pre_order(ArrayList<T>& v) const;
        void in_order(ArrayList<T>& v) const;
        void post_order(ArrayList<T>& v) const;
    };

    Node* root;
    std::size_t size_;

    void clear(Node* node);
};

template<typename T>
AVLTree<T>::AVLTree() : root(nullptr), size_(0) {}

template<typename T>
AVLTree<T>::~AVLTree() {
    clear(root);
}

template<typename T>
void AVLTree<T>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename T>
void AVLTree<T>::insert(const T& data) {
    if (empty()) {
        root = new Node(data);
    } else {
        root->insert(data, root);
    }
    size_++;
}

template<typename T>
void AVLTree<T>::remove(const T& data) {
    if (!empty()) {
        if (root->remove(data, root)) {
            size_--;
        }
    }
}

template<typename T>
bool AVLTree<T>::contains(const T& data) const {
    return !empty() && root->contains(data);
}

template<typename T>
bool AVLTree<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t AVLTree<T>::size() const {
    return size_;
}

template<typename T>
int AVLTree<T>::height() const {
    return root != nullptr ? root->height_ : -1;
}

template<typename T>
ArrayList<T> AVLTree<T>::pre_order() const {
    ArrayList<T> v{};
    if (!empty()) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
ArrayList<T> AVLTree<T>::in_order() const {
    ArrayList<T> v{};
    if (!empty()) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
ArrayList<T> AVLTree<T>::post_order() const {
    ArrayList<T> v{};
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}

template<typename T>
AVLTree<T>::Node::Node(const T& data) : data(data),
    height_(0), left(nullptr), right(nullptr) {}

template<typename T>
void AVLTree<T>::Node::insert(const T& data_, Node*& node) {
    if (data_ < node->data) {
        if (node->left == nullptr) {
            node->left = new Node(data_);
        } else {
            node->left->insert(data_, node->left);
        }
    } else {
        if (node->right == nullptr) {
            node->right = new Node(data_);
        } else {
            node->right->insert(data_, node->right);
        }
    }
    node->updateHeight();
    if (node->balanceFactor() > 1) {
        if (data_ < node->left->data) {
            node = node->simpleRight();
        } else {
            node = node->doubleRight();
        }
    } else if (node->balanceFactor() < -1) {
        if (data_ > node->right->data) {
            node = node->simpleLeft();
        } else {
            node = node->doubleLeft();
        }
    } else {
        node = node;
    }
}

template<typename T>
bool AVLTree<T>::Node::remove(const T& data_, Node*& node) {
    if (data_ == node->data) {
        if (node->left != nullptr && node->right != nullptr) {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->data = temp->data;
            return node->right->remove(node->data, node->right);
        } else {
            Node* temp = node;
            node = node->left != nullptr ? node->left : node->right;
            delete temp;
            return true;
        }
    } else if (data_ < node->data) {
        return node->left != nullptr && node->left->remove(data_, node->left);
    } else {
        return node->right != nullptr &&
            node->right->remove(data_, node->right);
    }
    node->updateHeight();
    if (node->balanceFactor() > 1) {
        if (data_ < node->left->data) {
            node = node->simpleRight();
        } else {
            node = node->doubleRight();
        }
    } else if (node->balanceFactor() < -1) {
        if (data_ > node->right->data) {
            node = node->simpleLeft();
        } else {
            node = node->doubleLeft();
        }
    }
    return true;
}

template<typename T>
bool AVLTree<T>::Node::contains(const T& data_) const {
    if (data_ == data) {
        return true;
    } else if (data_ < data) {
        return left != nullptr && left->contains(data_);
    } else {
        return right != nullptr && right->contains(data_);
    }
}

template<typename T>
void AVLTree<T>::Node::updateHeight() {
    if (left && right) {
        height_ = 1 + (left->height_ > right->height_ ? 
            left->height_ : right->height_);
    } else if (left) {
        height_ = 1 + left->height_;
    } else if (right) {
        height_ = 1 + right->height_;
    } else {
        height_ = 0;
    }
}

template<typename T>
int AVLTree<T>::Node::balanceFactor() const {
    return (left ? left->height_ : -1) - (right ? right->height_ : -1);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::Node::simpleLeft() {
    Node* temp = right;
    right = temp->left;
    temp->left = this;
    updateHeight();
    temp->updateHeight();
    return temp;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::Node::simpleRight() {
    Node* temp = left;
    left = temp->right;
    temp->right = this;
    updateHeight();
    temp->updateHeight();
    return temp;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::Node::doubleLeft() {
    right = right->simpleRight();
    return simpleLeft();
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::Node::doubleRight() {
    left = left->simpleLeft();
    return simpleRight();
}

template<typename T>
void AVLTree<T>::Node::pre_order(ArrayList<T>& v) const {
    v.push_back(data);
    if (left != nullptr) {
        left->pre_order(v);
    }
    if (right != nullptr) {
        right->pre_order(v);
    }
}

template<typename T>
void AVLTree<T>::Node::in_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->in_order(v);
    }
    v.push_back(data);
    if (right != nullptr) {
        right->in_order(v);
    }
}

template<typename T>
void AVLTree<T>::Node::post_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->post_order(v);
    }
    if (right != nullptr) {
        right->post_order(v);
    }
    v.push_back(data);
}
}  // namespace structures
