#include <iostream>
#include <memory>
#include "src/LinkedList.hpp"
#include "src/Node.hpp"

int main() {
  list::linked<int> list(1,2,3,4,5);
  
  std::cout << "P C N" << std::endl;
  list.print();

  list.remove(1);
  list.remove(list.size() - 1);
  list.print();


  Node::Ptr root = std::make_unique<Node>('+');
  root->setFirst(std::make_unique<Node>('*'));
  root->getPair().first->setFirst(std::make_unique<Node>('+'));
  root->getPair().first->getPair().first->setFirst(std::make_unique<Node>('1'));
  root->getPair().first->getPair().first->setSecond(std::make_unique<Node>('2'));

  root->setSecond(std::make_unique<Node>('*'));
  root->getPair().second->setFirst(std::make_unique<Node>('+'));
  root->getPair().second->getPair().first->setFirst(std::make_unique<Node>('4'));
  root->getPair().second->getPair().first->setSecond(std::make_unique<Node>('3'));

  print(root);

  auto divided = nodeDivider(root, '+');

  print(divided.first);
  print(divided.second);
}
