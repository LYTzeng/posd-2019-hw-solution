#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>

#include "node.h"

class Folder: public Node {
public:
  class FolderIterator:public Node::Iterator {
  public:
    FolderIterator(Folder * f): _f(f) {}

    void first() {
      _current = _f->_v.begin();
      // _current = *(_f->_v.begin());
    }

    Node * currentItem() {
      return *_current;
    }

    void next() {
      ++_current;
    }

    bool isDone() {
      return _current == _f->_v.end();
    }
  private:
    Folder * _f;
    std::vector<Node *>::iterator _current;
    // Node * _current;
  };
public:
  Folder(std::string path): Node(path) {}

  void addChild(Node* child) {
    _v.push_back(child);
  }

  Node::Iterator * createIterator() {
    return new FolderIterator(this);
  }

private:
  std::vector<Node*> _v;
};
#endif
