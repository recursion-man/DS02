#define CATCH_CONFIG_MAIN


#include "HashTable.h"
#include "UpsideNode.h"
#include "catch.hpp"

TEST_CASE("Find and union", "find")
{
    Player player1(1);
    Player player2(2);
    HashTable hash;
    hash.insert(player1);
    hash.insert(player2) ;
    REQUIRE(hash[1]);
//    REQUIRE(find(&node2)->data == 2);
//    REQUIRE(union_tree(&node1, &node2)->data == 1);
//    REQUIRE(node2.isRoot == false);
//    REQUIRE(find(&node2)->data == 1);
//    Upside_Node<int> node3(3);
//    Upside_Node<int> node4(4);
//    REQUIRE(find(&node3)->data == 3);
//    REQUIRE(find(&node4)->data == 4);
//    REQUIRE(union_tree(&node3, &node4)->data == 3);
//    REQUIRE(find(&node4)->data == 3);
//    REQUIRE(union_tree(&node3, &node1)->data == 3);
//    REQUIRE(node2.father->data == 1);
//    REQUIRE(find(&node2)->data == 3);
//    REQUIRE(node2.father->data == 3);
//    REQUIRE(node1.isRoot == false);
}
