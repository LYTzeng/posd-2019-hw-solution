#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>

class Node
{
public:
    class Iterator
    {
    public:
        virtual bool isDone() = 0;
        virtual void first() = 0;
        virtual void next() = 0;
        virtual Node *currentItem() = 0;
    };

public:
    class NullIterator : public Iterator
    {
    public:
        bool isDone()
        {
            return true;
        }
        void first() {}
        void next() {}
        Node *currentItem()
        {
            return nullptr;
        }
    };

public:
    Node(std::string path) : _path(path)
    {
        stat(_path.c_str(), &_st);
    }

    int size()
    {
        return _st.st_size;
    }

    virtual void addChild(Node *child)
    {
        throw(std::string("Invalid add!"));
    }

    virtual Iterator *createIterator()
    {
        return new NullIterator();
    }

private:
    std::string _path;
    struct stat _st;
};

#endif
