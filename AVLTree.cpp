#include <iostream>
#include <vector>
#include <algorithm>
#include "AVLTree.h"

AVLTree::AVLTree()
    : root(nullptr) {}

int AVLTree::getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    return newRoot;
}

AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    return newRoot;
}

AVLTree::Node* AVLTree::balanceNode(Node* node) {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLTree::Node* AVLTree::insertNode(Node* node, const Song& song) {
    if (node == nullptr)
        return new Node(song);

    if (song.trackName < node->song.trackName)
        node->left = insertNode(node->left, song);
    else if (song.trackName > node->song.trackName)
        node->right = insertNode(node->right, song);
    else
        return node; // Duplicate keys are not allowed in this implementation

    return balanceNode(node);
}

void AVLTree::insert(const Song& song) {
    root = insertNode(root, song);
}

void AVLTree::displayInOrder(Node* node) {
    if (node == nullptr)
        return;

    displayInOrder(node->left);
    std::cout << node->song.trackName << std::endl;
    displayInOrder(node->right);
}

void AVLTree::displayInOrder() {
    displayInOrder(root);
}


void AVLTree::inOrderTraversal(Node* node, std::vector<Song>& songs) const
{
    if (node != nullptr) {
        inOrderTraversal(node->left, songs);
        songs.push_back(node->song);
        inOrderTraversal(node->right, songs);
    }
}


std::vector<Song> AVLTree::getAllSongs() const
{
    std::vector<Song> songs;
    inOrderTraversal(root, songs);
    return songs;
}




