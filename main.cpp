#include <iostream>
#include <memory>
#include "src/LinkedList.hpp"
#include "src/Node.hpp"


int main() {
  list::linked<int> list = {1,2,3,4,5,6,7,8,9};

  list::print(list);

  std::cout << std::endl;

  list.dublicateValues();
  list[10] = 5;
  list::print(list);

  Node::Ptr root = std::make_unique<Node>('+');
  root->setFirst(std::make_unique<Node>('*'));
  root->getPair().first->setFirst(std::make_unique<Node>('+'));
  root->getPair().first->getPair().first->setFirst(std::make_unique<Node>('1'));
  root->getPair().first->getPair().first->setSecond(std::make_unique<Node>('2'));

  Node::Ptr root1 = std::make_unique<Node>('+');
  root1->setFirst(std::make_unique<Node>('*'));
  root1->getPair().first->setFirst(std::make_unique<Node>('+'));
  root1->getPair().first->getPair().first->setFirst(std::make_unique<Node>('1'));
  root1->getPair().first->getPair().first->setSecond(std::make_unique<Node>('2'));

  std::cout << areEqual(root, root1) << std::endl;
}
