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
bst<Key>::bst(bst const& other) {
   this->root = copy(other.root);
}

template<typename Key>
bst<Key>::~bst() {
   // à mettre en oeuvre
   destroy(root);
}

template<typename Key>
bst<Key>& bst<Key>::operator=(bst const& other) {
   if (this == &other) return *this;
   bst<Key> tmp{other};
   std::swap(root, tmp.root);
   return *this;
}

template<typename Key>
void bst<Key>::insert(Key const& k) {
   insert(root, k);
}

template<typename Key>
void bst<Key>::display_indented(std::ostream& s) const noexcept {
   std::string prefix = "";
   indent(root, s, prefix, false);
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
Node<Key>* bst<Key>::copy(Node<Key>* r) {
   if (r != nullptr) {
      Node<Key>* r2 = new Node<Key>{r->key, nullptr, nullptr};
      r2->left = copy(r->left);
      r2->right = copy(r->right);
      return r2;
   }
   return r;
}

template<typename Key>
void bst<Key>::linearize() noexcept {
   linearize(root, nullptr, 0);
}

template<typename Key>
void bst<Key>::balance() noexcept {
   Node<Key>* l = nullptr;
   size_t n = 0;
   linearize(root, l, n);
   root = arborization(l, n);
}

template<typename Key>
void bst<Key>::destroy(Node<Key>*& r) {
   if (r != nullptr) {
      destroy(r->left);
      destroy(r->right);
      delete r;
   }
}

template<typename Key>
void bst<Key>::linearize(Node<Key>* r, Node<Key>*& l, size_t n) {
   if (r == nullptr) return;
   linearize(r->right, l, n);
   r->right = l;
   l = r;
   n = n + 1;
   linearize(r->left, l, n);
   r->left = nullptr;
}

template<typename Key>
Node<Key>* bst<Key>::arborization(Node<Key>*& l, size_t n) {
   if (n == 0) return nullptr;
   Node<Key>* rg = arborization(l, (n - 1) / 2);
   Node<Key>* r = l;
   r->left = rg;
   l = l->right;
   r->right = arborization(l, n / 2);
   return r;
}


template<typename Key>
std::ostream& operator<<(std::ostream& s, bst<Key> const& t) {
   bst<Key>::to_stream(t.root, s);
   return s;
}

template<typename Key>
void bst<Key>::indent(Node<Key> *r, std::ostream &s, std::string& prefix, bool enfantDroit) {
   s << prefix;
   if (r != nullptr) s << r->key;
   else s << ".";
   s << "\n";

   if (r == nullptr) return;

   if (r->left != nullptr || r->right != nullptr) {

      std::string prefixMod = prefix;

      if (prefix.empty()) {
         prefixMod = "|_ ";
      }else if (enfantDroit){
         prefixMod.insert(prefix.length() - 3, "   ");
      }else{
         prefixMod.insert(prefix.length() - 3, "|  ");
      }
      indent(r->left, s, prefixMod, false);
      indent(r->right, s, prefixMod, true);
   }
}


#endif //ASD1_LABS_2020_BST_IMPL_H
