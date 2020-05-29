//
// Created by Olivier Cuisenaire on 23.05.20.
//

#ifndef ASD1_LABS_2020_BST_IMPL_H
#define ASD1_LABS_2020_BST_IMPL_H

// fonctions récursives n'ayant pas à connaitre root

template<typename Key>
void bst<Key>::insert(Node<Key> *&r, Key const &k) {
        if (r == nullptr) {
            r = new Node<Key>{k, nullptr, nullptr};
        } else if (k == r->key) {
            // k already there : do nothing.
        } else if (k < r->key) {
            insert(r->left, k);
        } else { // k > r->key
            insert(r->right, k);
        }
    }

template<typename Key>
void bst<Key>::to_stream(Node<Key> *r, std::ostream &s) noexcept {
    if (r) {
        s << r->key;
        if (r->right or r->left) { // r has children
            s << "(";
            if (r->left) to_stream(r->left, s);
            else s << ".";

            s << ",";

            if (r->right) to_stream(r->right, s);
            else s << ".";

            s << ")";
        }
    }
}

// méthodes de la classe bst

template<typename Key>
bst<Key>::bst() : root(nullptr) {
}

template<typename Key>
bst<Key>::~bst() {
    // à mettre en oeuvre
}

template<typename Key>
void bst<Key>::insert(Key const& k) {
    insert(root, k);
}

template<typename Key>
void bst<Key>::display_indented(std::ostream &s) const noexcept {
    s << "does not work yet obviously";
}

template <typename Key>
std::ostream& operator<<(std::ostream& s, bst<Key> const& t)
{
    bst<Key>::to_stream(t.root, s);
    return s;
}

#endif //ASD1_LABS_2020_BST_IMPL_H
