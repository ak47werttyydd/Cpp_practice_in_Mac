#include <stdexcept>
#include <string>
#include <iostream>

// The Node class is provided to you.
// NOTE: you **MAY** alter this class if you wish
namespace CopyTwoTrees
{
    class Node
    {
    public:
        Node(int value, Node* left = nullptr, Node* right = nullptr)
        {
            this->value = value;
            this->left = left;
            this->right = right;
        }

        int getValue() const
        {
            return value;
        }

        Node* getLC() const
        {
            return left;
        }

        Node* getRC() const
        {
            return right;
        }

        void setValue(int value){
            this->value = value;
        }
        void setLC(Node* left){
            this->left = left;
        }
        void setRC(Node* right){
            this->right = right;
        }

    private:
        int value;
        Node* left;
        Node* right;
    };

    class BinaryTreeAdd
    {
    public:
        // Deep copy of a node, post-order
        //how to connect children and parent? creating new nodes connected to left and right children from bottom up
        static Node* cpNode1(Node* t) {
            if (t == nullptr) {
                return nullptr;
            }
            // Recursively copy the left and right children
            Node* leftCopy = cpNode1(t->getLC());
            Node* rightCopy = cpNode1(t->getRC());
            // Return a new node with the same value and copied children
            return new Node(t->getValue(), leftCopy, rightCopy);
        }

        //or pre-order copy
        static Node* cpNode2(Node* t) {
            if (t == nullptr) {
                return nullptr;
            }

            // Create a new node with the same value as t (process the node itself). And set left and right as nullptr(because don't exist)
            Node* newNode = new Node(t->getValue(), nullptr, nullptr);

            // Recursively copy the left subtree and attach to the new node
            newNode->setLC(cpNode2(t->getLC()));

            // Recursively copy the right subtree and attach to the new node
            newNode->setRC(cpNode2(t->getRC()));

            return newNode;
        }


        // Function to add two binary trees， without using copy, pre_order
        static Node* add1(Node* t1, Node* t2)
        {
            //terminal condition
            if (t1 == nullptr && t2 == nullptr) {
                return nullptr;
            }

            // Get the values from each node (or 0 if the node is nullptr)
            int value1 = (t1 != nullptr) ? t1->getValue() : 0;
            int value2 = (t2 != nullptr) ? t2->getValue() : 0;

            // Create a new node with the sum of values
            Node* newNode = new Node(value1 + value2);

            // Recursively add left and right children
            newNode->setLC(add1(t1 ? t1->getLC() : nullptr, t2 ? t2->getLC() : nullptr));  //if t1 or t2 is is nullptr, pass nullptr as children
            newNode->setRC(add1(t1 ? t1->getRC() : nullptr, t2 ? t2->getRC() : nullptr));

            return newNode; //the first call will return a root newNode
        }

        // Function to add two binary trees, pre_order, with cpNode
        static Node* add2(Node* t1, Node* t2)
        {
            //termination condition
            //all null
            if (t1 == nullptr && t2 == nullptr) {
                return nullptr;
            }

            //one of it null
            if(!t1){ //t1 null,t2 exists
                return cpNode1(t2);
            }else if(!t2){ //t1 exists, t2 null
                return cpNode1(t1);
            }

            //both t1 and t2 exist
            //Get the values from each node
            int value1 = t1->getValue();
            int value2 = t2->getValue();

            // Create a new node with the sum of values
            Node* newNode = new Node(value1 + value2);

            // Recursively add left and right children
            newNode->setLC(add2(t1->getLC(), t2->getLC()));
            newNode->setRC(add2(t1->getRC(), t2->getRC()));

            return newNode;
        }
    };
}

#ifndef RunTests
#endif
