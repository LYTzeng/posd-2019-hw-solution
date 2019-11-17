#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <regex>
#include "node_iterator.h"
#include "find_visitor.h"

class Node
{
public:
    Node(std::string path) : _path(path)
    {
        if (lstat(_path.c_str(), &_st) != 0)
            throw(std::string("Node is not exist!"));
        switch (_st.st_mode & S_IFMT)
        {
        case S_IFREG:
            nodeType = "file";
            break;
        case S_IFDIR:
            nodeType = "folder";
            break;
        case S_IFLNK:
            nodeType = "symlink";
            break;
        }
    }
    virtual ~Node() {}

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

    virtual NodeIterator *createIterator() = 0;

    std::string getPath()
    {
        // Getter!
        // return node path
        return _path;
    }

    virtual void accept(FindVisitor* fv) = 0;

    // void renameNode(std::string new_name)
    // {
    //     //TODO: Implement renameNode() for Node Class.
    //     /* You should update
    //     1. The physical node name.
    //     2. The node name in your own file system
    //     */
    // }

private:
    struct stat _st;
    std::string _path;
};

#endif
