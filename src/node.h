#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <regex>
#include <stdio.h>
#include "iterator.h"
#include "find_visitor.h"
#include "update_path_visitor.h"

class Node
{
public:
    Node(std::string path) : _path(path)
    {
        struct stat st;
        std::string s("Node is not exist!");
        s.append(path);
        if (lstat(_path.c_str(), &st) != 0)
            throw(s);
        _size = st.st_size;
    }
    virtual ~Node() {}

    std::string nodeType;

    int size()
    {
        return _size;
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

    virtual Iterator *createIterator() = 0;

    std::string getPath()
    {
        // Getter!
        // return node path
        return _path;
    }

    virtual void accept(FindVisitor *fv) = 0;

    virtual void accept(UpdatePathVisitor *upv) = 0;

    void renameNode(std::string new_name)
    {
        /* You should update
        1. The physical node name.
        2. The node name in your own file system
        */
        std::string newPath;
        newPath.assign(_path.begin(), _path.begin() + _path.length() - name().length());
        newPath.insert(newPath.length(), new_name);
        char *char_newPath = new char[newPath.length()];
        strcpy(char_newPath, newPath.c_str());
        char *char_path = new char[_path.length()];
        strcpy(char_path, _path.c_str());
        int returnCode = rename(char_path, char_newPath);
        if (returnCode != 0)
            perror("Error renaming file");
        else
            _path = newPath;
    }

    void moveToNewPath(std::string newDir)
    {
        std::string currentName = name();
        _path.assign(newDir);
        _path.append(currentName);
    }

private:
    std::string _path;
    int _size;
};

#endif
