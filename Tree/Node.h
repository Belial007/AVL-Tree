#pragma once
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <sstream>
#include <queue>

class AVLTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int data);
        ~Node();
        friend std::ostream& operator<<(std::ostream& os, const Node& node)
        {
            os << node.toString();
            return os;
        }
        std::string toString() const;
    };
    Node* root;

    int height(Node* node) const;
    int balanceFactor(Node* node) const;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insertNode(Node* node, int data);
    Node* findNode(Node* node, int data) const;
    Node* findMinNode(Node* node) const;
    Node* deleteNode(Node* node, int data);
    void deleteSubtree(Node* node);

public:
    AVLTree();
    ~AVLTree();
    void insert(int data);
    bool find(int data) const;
    void remove(int data);
    std::string toString() const;
    void printTree() const;

    friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree);
    friend std::ofstream& operator<<(std::ofstream& os, const AVLTree& tree);
    friend std::ifstream& operator>>(std::ifstream& is, AVLTree& tree);
    friend std::istream& operator>>(std::istream& is, AVLTree& tree);
};

// Реализация методов Node
AVLTree::Node::Node(int data) : data(data), left(nullptr), right(nullptr), height(1) {}

AVLTree::Node::~Node() {
}

std::string AVLTree::Node::toString() const {
    std::stringstream ss;
    ss << "Node(" << data << ", h=" << height << ")";
    return ss.str();
}

// Реализация методов AVLTree
AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    deleteSubtree(root);
}

int AVLTree::height(Node* node) const {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(Node* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLTree::Node* AVLTree::insertNode(Node* node, int data) {
    if (!node) {
        return new Node(data);
    }

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    }
    else if (data > node->data) {
        node->right = insertNode(node->right, data);
    }
    else {
        return node; // Дубликаты не добавляем
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && data < node->left->data) {
        return rotateRight(node);
    }

    if (balance < -1 && data > node->right->data) {
        return rotateLeft(node);
    }

    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(int data) {
    root = insertNode(root, data);
}

AVLTree::Node* AVLTree::findNode(Node* node, int data) const {
    if (!node) {
        return nullptr;
    }

    if (data == node->data) {
        return node;
    }
    else if (data < node->data) {
        return findNode(node->left, data);
    }
    else {
        return findNode(node->right, data);
    }
}

bool AVLTree::find(int data) const {
    return findNode(root, data) != nullptr;
}

AVLTree::Node* AVLTree::findMinNode(Node* node) const {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

AVLTree::Node* AVLTree::deleteNode(Node* node, int data) {
    if (!node) {
        return node;
    }
    if (data < node->data) {
        node->left = deleteNode(node->left, data);
    }
    else if (data > node->data) {
        node->right = deleteNode(node->right, data);
    }
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            node = temp;

        }
        else {
            Node* temp = findMinNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
    }

    if (!node) {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::remove(int data) {
    root = deleteNode(root, data);
}

void AVLTree::deleteSubtree(Node* node) {
    if (node) {
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
}

std::string AVLTree::toString() const {
    if (!root) {
        return "Tree is empty";
    }
    std::stringstream ss;
    std::queue<Node*> queue;
    queue.push(root);

    while (!queue.empty()) {
        Node* node = queue.front();
        ss << node->toString() << ", ";
        queue.pop();
        if (node->left) queue.push(node->left);
        if (node->right) queue.push(node->right);
    }
    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }
    return "{" + result + "}";
}
void AVLTree::printTree() const {

    std::queue<Node*> queue;
    if (root)
        queue.push(root);

    while (!queue.empty())
    {
        Node* temp = queue.front();
        std::cout << temp->data << " ";
        queue.pop();

        if (temp->left)
            queue.push(temp->left);

        if (temp->right)
            queue.push(temp->right);
    }
    std::cout << std::endl;
}

// Объявление операторов вне класса
std::ostream& operator<<(std::ostream& os, const AVLTree& tree);
std::ofstream& operator<<(std::ofstream& os, const AVLTree& tree);
std::ifstream& operator>>(std::ifstream& is, AVLTree& tree);
std::istream& operator>>(std::istream& is, AVLTree& tree);

#endif