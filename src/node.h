#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <regex>
#include "iterator.h"

class Node
{
public:
    Node(std::string path) : _path(path)
    {
        // if (stat(_path.c_str(), &_st) != 0)
        //     throw(std::string("Node is not exist!"));
        stat(_path.c_str(), &_st);
        switch (_st.st_mode & S_IFMT)
        {
        case S_IFREG:
            nodeType = "file";
            break;
        case S_IFDIR:
            nodeType = "folder";
            break;
        }
    }

    std::string nodeType;

    int size()
    {
        return _st.st_size;
    }

    virtual void addChild(Node *child)
    {
        throw(std::string("Invalid add!"));
    }

    std::string name()
    {
        std::smatch match;
        std::regex matchName("([^\\/]+$)");
        std::regex_search(_path, match, matchName);
        return match.str(0);
    }

    virtual std::string relativePath()
    {
        return _path;
    }

    virtual std::string traverseSearch(std::string name) {}

    virtual Iterator *createIterator() = 0;

private:
    struct stat _st;
    std::string _path;
};

#endif
