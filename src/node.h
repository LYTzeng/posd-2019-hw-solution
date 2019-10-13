#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <regex>
#include <iostream>

class Node
{
public:
    Node(std::string path) : _path(path)
    {
        if (stat(_path.c_str(), &_st) != 0)
            throw(std::string("Node is not exist!"));

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

    virtual Node *getChild(int num)
    {
        return nullptr;
    }

    virtual int infoByte()
    {
        return size();
    }

    std::string name()
    {
        // For example path:"test/TA_folder/hello.txt"
        // "hello.txt" is name
        // Return "hello.txt"
        std::smatch match;
        std::regex matchName("([^\\/]+$)");
        std::regex_search(_path, match, matchName);
        return match.str(0);
    }

    virtual std::string relativePath()
    {
        return _path;
    }

    virtual std::string findNode(std::string name)
    {
        // If the node is a file and == search string
        if (Node::name() == name)
            return _path + "/" + name;
        // else search no results
        else
            return "\0";
    }

    virtual std::string listNode()
    {
        // If node is file, it can't listNode.
        // It should throw "Not a directory"
        throw(std::string("Not a directory"));
    }

    virtual std::string traverseSearch(std::string name){}

private:
    std::string _path;
    struct stat _st;
};
#endif
