#include "pch.h"
#include "CppUnitTest.h"
#include "../Tree/Node.h" // Убедись, что путь к tree.h верный
#include "../AVL-Tree/main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AVLTreeTests
{
    TEST_CLASS(AVLTreeTest)
    {
    public:
        TEST_METHOD(ConstructorDestructor)
        {
            AVLTree* tree = new AVLTree();
            delete tree;
            Assert::IsTrue(true);
        }

        TEST_METHOD(InsertFind)
        {
            AVLTree tree;
            tree.insert(10);
            tree.insert(20);
            tree.insert(30);

            Assert::IsTrue(tree.find(20));
            Assert::IsFalse(tree.find(40));
        }

        TEST_METHOD(Remove)
        {
            AVLTree tree;
            tree.insert(10);
            tree.insert(20);
            tree.insert(30);

            tree.remove(20);
            Assert::IsFalse(tree.find(20));
            Assert::IsTrue(tree.find(10));
            Assert::IsTrue(tree.find(30));
        }

        TEST_METHOD(ToString)
        {
            AVLTree tree;
            tree.insert(10);
            tree.insert(20);
            tree.insert(30);
            std::string expected = "{Node(20, h=2), Node(10, h=1), Node(30, h=1)}";
            Assert::AreEqual(expected, tree.toString());
        }

        TEST_METHOD(EmptyTreeToString)
        {
            AVLTree tree;
            std::string expected = "Tree is empty";
            Assert::AreEqual(expected, tree.toString());
        }
        TEST_METHOD(FileOutputInput)
        {

            AVLTree tree;
            tree.insert(10);
            tree.insert(20);
            tree.insert(30);

            std::ofstream outputFile("output.txt");
            outputFile << tree;
            outputFile.close();


            AVLTree tree2;
            tree2.insert(10);
            tree2.insert(20);
            tree2.insert(30);
            std::ifstream inputFile("output.txt");
            inputFile >> tree2;
            inputFile.close();

            Assert::AreEqual(tree.toString(), tree2.toString());
        }
        TEST_METHOD(ConsoleInput)
        {
            AVLTree tree;
            std::stringstream ss;
            ss << "10 20 30 40 abc";
            std::istream is(ss.rdbuf());
            is >> tree;
            std::string expected = "{Node(20, h=3), Node(10, h=1), Node(30, h=2), Node(40, h=1)}";
            Assert::AreEqual(expected, tree.toString());
        }
    };

    // Переопределение операторов сдвига (чтобы работало с тестами)
    std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
        os << tree.toString();
        return os;
    }

    std::ofstream& operator<<(std::ofstream& os, const AVLTree& tree)
    {
        os << tree.toString();
        return os;
    }

    std::ifstream& operator>>(std::ifstream& is, AVLTree& tree) {
        int value;
        while (is >> value) {
            tree.insert(value);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, AVLTree& tree) {
        int value;
        while (is >> value) {
            tree.insert(value);
        }
        return is;
    }
}