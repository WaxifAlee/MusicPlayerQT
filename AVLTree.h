#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>
#include <iostream>

struct Song {
    std::string trackName;
    std::string genre;
    std::string artist;

    Song(const std::string& trackName, const std::string& genre, const std::string& artist)
        : trackName(trackName), genre(genre), artist(artist) {}
};

class AVLTree {
private:
    struct Node {
        Song song;
        Node* left;
        Node* right;
        int height;

        Node(const Song& song)
            : song(song), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Private member functions
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balanceNode(Node* node);
    Node* insertNode(Node* node, const Song& song);
    void inOrderTraversal(Node* node, std::vector<Song>& songs) const;


public:
    // Public member functions
    AVLTree();
    void insert(const Song& song);
    void displayInOrder();
    std::vector<Song> getAllSongs() const;
    void displayInOrder(Node* node);

};

#endif // AVLTREE_H
