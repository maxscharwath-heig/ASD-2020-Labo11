//
// Created by Olivier Cuisenaire on 23.05.20.
//

#ifndef ASD1_LABS_2020_BST_IMPL_H
#define ASD1_LABS_2020_BST_IMPL_H

// fonctions récursives n'ayant pas à connaitre root

#include "bst.h"

template<typename Key>
void bst<Key>::insert(Node<Key>*& r, Key const& k) {
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
void bst<Key>::to_stream(Node<Key>* r, std::ostream& s) noexcept {
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
void bst<Key>::display_indented(std::ostream& s) const noexcept {
   s << "does not work yet obviously";
}

template<typename Key>
Key const& bst<Key>::min() const {
   Node<Key>* m = root;
   while (m->left != nullptr) {
      m = m->left;
   }
   return m->key;
}

template<typename Key>
Key const& bst<Key>::max() const {
   Node<Key>* m = root;
   while (m->right != nullptr) {
      m = m->right;
   }
   return m->key;
}

template<typename Key>
void bst<Key>::erase_min() {
   erase_min(*root);
}

template<typename Key>
void bst<Key>::erase_max() {
   erase(root, max());
}

template<typename Key>
void bst<Key>::erase(const Key& k) noexcept {
   erase(root, k);
}

template<typename Key>
void bst<Key>::erase_min(Node<Key>*& r) {
   if (r == nullptr) throw "Error";
   else if (r->left != nullptr) {
      erase_min(r->left);
   } else {
      Node<Key>* d = r->right;
      delete r;
      r = d;
   }
}

template<typename Key>
void bst<Key>::erase(Node<Key>*& r, const Key& k) {
   if (r == nullptr) {// k est absent
   } else if (k < r->key) erase(r->left, k);
   else if (k > r->key) erase(r->right, k);
   else {// k est trouvé
      Node<Key>*& temp = r;
      if (r->left == nullptr) r = r->right;
      else if (r->right == nullptr)r = r->left;
      else {
         Node<Key>*& m = sort_min(r->right);
         m->right = r->right;
         m->left = r->left;
         r = m;
      }
      delete temp;
   }
}

template<typename Key>
Node<Key>*& bst<Key>::sort_min(Node<Key>*& r) {
   if (r->left != nullptr) {
      return sort_min(r->left);
   } else {
      Node<Key>*& tmp = r;
      r = r->right;
      return tmp;
   }
}

template<typename Key>
std::ostream& operator<<(std::ostream& s, bst<Key> const& t) {
   bst<Key>::to_stream(t.root, s);
   return s;
}


#endif //ASD1_LABS_2020_BST_IMPL_H
