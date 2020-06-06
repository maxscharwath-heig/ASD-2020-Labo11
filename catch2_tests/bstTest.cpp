#include "catch.hpp"
#include "../bst.h"

#include <sstream>
#include <string>
using namespace std;

template<typename T>
string to_string(T const& t) {
    ostringstream oss;
    oss << t;
    return oss.str();
}

TEST_CASE( "operator<<", "[bst]") {

    bst<int> tree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);
        REQUIRE( to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION( "Empty tree" ) {
        REQUIRE( to_string(tree) == "" );
    }
}

TEST_CASE( "insert", "[bst]") {

    bst<int> tree;

    SECTION( "Insert 42" ) {
        tree.insert(42);
        REQUIRE( to_string(tree) == "42" );
    }

    SECTION( "Insert smaller to the left" ) {
        tree.insert(3);
        tree.insert(2);
        REQUIRE( to_string(tree) == "3(2,.)" );
    }

    SECTION( "Insert larger to the right" ) {
        tree.insert(3);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }

    SECTION( "Insert twice has no effect" ) {
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }
}

TEST_CASE("display_indented", "[bst]") {
    bst<int> tree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "8\n"
                              "|_ 4\n"
                              "|  |_ 1\n"
                              "|  |  |_ .\n"
                              "|  |  |_ 2\n"
                              "|  |     |_ .\n"
                              "|  |     |_ 3\n"
                              "|  |_ 6\n"
                              "|     |_ 5\n"
                              "|     |_ 7\n"
                              "|_ 11\n"
                              "   |_ 10\n"
                              "   |_ 12\n" );
    }
}

TEST_CASE("search max and min", "[bst]") {
   bst<int> tree;
   for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
      tree.insert(i);
   SECTION( "get min" ) {
      REQUIRE(tree.min() == 1);// right key
      REQUIRE(tree.min() != 6);// random key in tree
      REQUIRE(tree.min() != 12);// max key in tree
      REQUIRE(tree.min() != -1);// no key in tree
   }
   SECTION( "get max" ) {
      REQUIRE(tree.max() == 12);// right key
      REQUIRE(tree.max() != 1);// min key in tree
      REQUIRE(tree.max() != 6);// random key in tree
      REQUIRE(tree.max() != -1);// no key in tree
   }
}

TEST_CASE("erase min, max and this", "[bst]") {
   bst<int> tree;
   for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
      tree.insert(i);
   SECTION( "erase_min()" ) {
      bst<int> tree2{tree};
      tree2.erase_min();
      REQUIRE(to_string(tree2) == "8(4(2(.,3),6(5,7)),11(10,12))");
   }
   SECTION( "erase_max()" ) {
      bst<int> tree2{tree};
      tree2.erase_max();
      REQUIRE(to_string(tree2) == "8(4(1(.,2(.,3)),6(5,7)),11(10,.))");
   }
   SECTION( "erase()" ) {
      bst<int> tree2{tree};
      tree2.erase(6);
      REQUIRE(to_string(tree2) == "8(4(1(.,2(.,3)),7(5,.)),11(10,12))");
   }
}

TEST_CASE("copy constructor and operator =", "[bst]"){
   bst<int> tree;
   for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
      tree.insert(i);
   SECTION("copy constructor"){
      bst<int> tree2{tree};
      REQUIRE(to_string(tree2) == to_string(tree));
   }
   SECTION("Operator ="){
      bst<int> tree2 = tree;
      REQUIRE(to_string(tree2) == to_string(tree));
   }
}

TEST_CASE("linearize & balance", "[bst]"){
   bst<int> tree;
   for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
      tree.insert(i);
   SECTION("linearize"){
      bst<int> tree2{tree};
      tree2.linearize();
      REQUIRE(to_string(tree2) == "1(.,2(.,3(.,4(.,5(.,6(.,7(.,8(.,10(.,11(.,12))))))))))");
   }
   SECTION("balance"){
      bst<int> tree2{tree};
      tree2.balance();
      REQUIRE(to_string(tree2) == "6(3(1(.,2),4(.,5)),10(7(.,8),11(.,12)))");
   }
}

TEST_CASE("contains", "[bst]"){
   bst<int> tree;
   for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
      tree.insert(i);
   SECTION("contains"){
      REQUIRE(tree.contains(11) == true);
      REQUIRE(tree.contains(9)  == false);
      REQUIRE(tree.contains(12) == true);
      REQUIRE(tree.contains(1)  == true);
      REQUIRE(tree.contains(8)  == true);
      REQUIRE(tree.contains(-1) == false);
   }
}

TEST_CASE("visit_in_order", "[bst]"){
   bst<int> tree;
   for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
      tree.insert(i);
   SECTION("visit_in_order"){
      std::string s;
      tree.visit_in_order([&s](Node<int>* r){ s += " " + to_string(r->key) ; });
      REQUIRE(s == " 1 2 3 4 5 6 7 8 10 11 12");
   }
}