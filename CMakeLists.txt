cmake_minimum_required(VERSION 3.21)
project(DataStructureReview)

set(CMAKE_CXX_STANDARD 17)


#add_executable(DataStructureReview "Chapter12 SelectionAndSort/orderVectorMedian.cpp")

add_executable(Heap "Chapter10 Heap/PQ_test.cpp" "Chapter10 Heap/PQ.hpp" "Chapter10 Heap/PQ_ComplHeap.hpp")

add_executable(BinaryTree "Chapter5 BinaryTree/BinNode.hpp" "Chapter5 BinaryTree/BinTree.hpp" "Chapter5 BinaryTree/BinaryTreeTest.cpp")

add_executable(BST "Chapter7 BinarySearchTree/bstTest.cpp" "Chapter7 BinarySearchTree/BST.hpp" "Chapter7 BinarySearchTree/AVL.hpp")
