#include "../Tree/Node.h"
#include <iostream>
#include <fstream>

std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
    os << tree.toString();
    return os;
}

std::ofstream& operator<<(std::ofstream& os, const AVLTree& tree) {
    os << tree.toString();
    return os;
}

std::ifstream& operator>>(std::ifstream& is, AVLTree& tree) {
    int data;
    while (is >> data) {
        tree.insert(data);
    }
    return is;
}
std::istream& operator>>(std::istream& is, AVLTree& tree)
{
    int data;
    while (is >> data)
    {
        tree.insert(data);
    }
    return is;
}

int main() {

    setlocale(LC_ALL, "Russian");

    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "������: " << tree << std::endl;
    std::cout << "����� ������: "; tree.printTree();

    std::cout << "����� 25: " << tree.find(25) << std::endl;
    std::cout << "����� 60: " << tree.find(60) << std::endl;

    tree.remove(30);

    std::cout << "������ ����� �������� 30: " << tree << std::endl;
    std::cout << "������� ������ ����� ��������: "; tree.printTree();

    AVLTree tree2;
    std::ofstream outputFile("output.txt");
    outputFile << tree;
    outputFile.close();

    std::ifstream inputFile("output.txt");
    inputFile >> tree2;
    inputFile.close();

    std::cout << "������ ��������� � �����: " << tree << std::endl;

    AVLTree tree3;
    std::cout << "������� ����� ��� �������� ������: " << std::endl;
    std::cin >> tree3;
    std::cout << "������ �� �������: " << tree3 << std::endl;


    return 0;
}