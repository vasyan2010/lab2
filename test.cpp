//
// Created by admin on 19.05.2019.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RB_Tree.h"

using testing::Eq;
namespace {
    class ClassDeclaration:public testing::Test{
    public:
        RB_Tree <int >tree;
        ClassDeclaration(){
            tree;
        }
    };
}

TEST_F(ClassDeclaration, nameOfTheTest1){
    tree.insert(2,11);
    tree.insert(3,13);
    tree.insert(1,12);
    if (tree.getHead()!= NULL)
        SUCCEED();
    else
        FAIL();
}

TEST_F(ClassDeclaration, nameOfTheTest2){

    tree.insert(2,11);
    tree.insert(3,13);
    tree.insert(1,12);
    if (tree.getHead()->rht== tree.brother(tree.getHead()->lft))
        SUCCEED();
    else
        FAIL();
}

TEST_F(ClassDeclaration, nameOfTheTest3){
    tree.insert(2,11);
    tree.insert(3,13);
    tree.insert(1,12);
    tree.insert(0,13);
    if (tree.getHead()->rht== tree.uncle(tree.getHead()->lft->lft))
        SUCCEED();
    else
        FAIL();
}

TEST_F(ClassDeclaration, nameOfTheTest4){
    tree.insert(2,11);
    tree.insert(3,13);
    tree.insert(1,12);
    tree.insert(0,13);
    if (tree.getHead()== tree.grandparent(tree.getHead()->lft->lft))
        SUCCEED();
    else
        FAIL();
}