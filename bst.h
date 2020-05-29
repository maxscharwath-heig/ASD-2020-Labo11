#ifndef ASD1_2020_LABO11_BST_H
#define ASD1_2020_LABO11_BST_H

#include <string>
#include <iostream>

template <typename Key> struct Node {
    Key const key;
    Node* left;
    Node* right;
};

template<typename Key> class bst;

template <typename Key> std::ostream& operator<<(std::ostream& s, bst<Key> const& tree);

template<typename Key>
class bst { // binary search tree

    friend std::ostream &operator<<<>(std::ostream &, bst<Key> const &);

    Node<Key> *root;

public:

    bst();
    void insert(Key const &k);

    // les fonctions suivantes sont à mettre en oeuvre et à tester.

    bst(bst const &other);               // doit offrir la garantie de base
    bst &operator=(bst const &other);    // doit offrir la garantie forte
    ~bst();                              // doit libérer proprement toute la mémoire
                                         // une définition vide est actuellement fournie pour que le projet compile.

    bool contains(Key const& k) const noexcept ; // recherche de l'élément

    // toutes les fonctions se référant à min ou max lèvent une std::exception si l'arbre est vide
    Key const& min() const ;
    Key const& max() const ;
    void erase_min() ;
    void erase_max() ;

    void erase(Key const& k) noexcept ;

    template<typename Fn> void visit_in_order(Fn f) const ; // la fonction f prend un élément de type Key en paramètre
                                                            // elle est appelée pour tous les éléments de l'arbre par
                                                            // ordre croissant.

    // pour la fonction suivante un test vous est fourni et échoue actuellement

    void display_indented(std::ostream &s) const noexcept ;

    // les fonctions suivantes seront expliquées dans la video 5.14

    void linearize() noexcept ;
    void balance() noexcept ;

private:
    // fonctions récursives utilisées par les fonctions publiques ci-dessus
    // elles sont static car elles n'ont pas besoin d'accéder à l'attribut root.

    static void insert(Node<Key> *&r, Key const &k);
    static void to_stream(Node<Key> *r, std::ostream &s) noexcept;
};

// toutes les fonctions sont définies dans le fichier inclus ci-dessous

#include "bst_impl.h"

#endif //ASD1_2020_LABO11_BST_H
