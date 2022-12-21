#define CATCH_CONFIG_MAIN

#include "UpsideNode.h"
#include "catch.hpp"

TEST_CASE("Find and union", "find")
{

    SECTION("simple find ")
    {
        Upside_Node<int> node1(1);
        Upside_Node<int> node2(2);
        REQUIRE(find(&node1)->data == 1);
        REQUIRE(find(&node2)->data == 2);
        Upside_Node<int> node3(3);
        Upside_Node<int> node4(4);
        REQUIRE(find(&node3)->data == 3);
        REQUIRE(find(&node4)->data == 4);
    }

    SECTION("simple find with union")
    {
        Upside_Node<int> node1(1);
        Upside_Node<int> node2(2);
        REQUIRE(find(&node1)->data == 1);
        REQUIRE(find(&node2)->data == 2);
        REQUIRE(union_tree(&node1, &node2)->data == 1);
        REQUIRE(node2.isRoot == false);
        REQUIRE(find(&node2)->data == 1);
        Upside_Node<int> node3(3);
        Upside_Node<int> node4(4);
        REQUIRE(find(&node3)->data == 3);
        REQUIRE(find(&node4)->data == 4);
        REQUIRE(union_tree(&node3, &node4)->data == 3);
        REQUIRE(find(&node4)->data == 3);
        REQUIRE(union_tree(&node3, &node1)->data == 3);
        REQUIRE(node2.father->data == 1);
        REQUIRE(find(&node2)->data == 3);
        REQUIRE(node2.father->data == 3);
        REQUIRE(node1.isRoot == false);
    }
    SECTION("find shrink path")
    {
        // checking if 6 also points diractly to the root 8 after find(5)
        Upside_Node<int> node5(5);
        Upside_Node<int> node6(6);
        Upside_Node<int> node7(7);
        Upside_Node<int> node8(8);
        node5.father = &node6;
        node6.father = &node7;
        node7.father = &node8;
        node5.isRoot = false;
        node6.isRoot = false;
        node7.isRoot = false;

        REQUIRE(find(&node5)->data == 8);
        REQUIRE(node6.father->data == 8);
        REQUIRE(node7.father->data == 8);
        REQUIRE(find(&node7)->data == 8);
    }
}
