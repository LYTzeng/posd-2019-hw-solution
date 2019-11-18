#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <map>
#include <sys/stat.h>

#include "node.h"
#include "iterator.h"

class Folder : public Node
{
public:
    class FolderIterator : public Iterator
    {
    public:
        FolderIterator(Folder *f) : _f(f) {}

        void first() override
        {
            _current = _f->_map.begin();
        }

        Node *currentItem() override
        {
            if (_f->_map.size() == 0 || (_current) == _f->_map.end())
                throw std::string("No current item!");
            return _current->second;
        }

        void next() override
        {
            if (_f->_map.size() == 0 || (_current++) == _f->_map.end())
                throw std::string("Moving past the end!");
        }

        bool isDone() override
        {
            return _current == _f->_map.end();
        }

        int size() override
        {
            return _f->_map.size();
        }

    private:
        Folder *_f;
        std::map<std::string, Node *>::iterator _current;
    };

public:
    Folder(std::string path) : Node(path)
    {
        struct stat st;
        stat(path.c_str(), &st);
        if (!S_ISDIR(st.st_mode))
            throw(std::string("It is not Folder!"));
        else
            nodeType = "folder";
    }

    void addChild(Node *child) override
    {
        _map[child->name()] = child;
    }

    Iterator *createIterator() override
    {
        return new FolderIterator(this);
    }

    void accept(FindVisitor *fv) override
    {
        fv->visitFolder(this);
    }

    void accept(UpdatePathVisitor *upv) override
    {
        upv->visitFolder(this);
    }

private:
    std::map<std::string, Node *> _map;
};
#endif
