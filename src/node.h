#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <regex>

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

    std::string nodeType;

    virtual std::string findNode(std::string name) {}

    virtual std::string listNode() 
    {
        throw(std::string("Not a directory"));
    }

private:
    std::string _path;
    struct stat _st;
};

//pratice here
int infoByte(Node *node)
{
    int total = 0;
    if (node->getChild(0) != nullptr)
    { //it's a folder
        for (int i = 0; i < 2; i++)
        {
            total += node->getChild(i)->size();
        }
    }
    return total;
}
#endif
