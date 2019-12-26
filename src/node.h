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
        lstat(_path.c_str(), &_stUpdate);
        return _stUpdate.st_size;
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
        return _path;
    }

    virtual void accept(FindVisitor *fv) = 0;

    virtual void accept(UpdatePathVisitor *upv) = 0;

    void renameNode(std::string new_name)
    {
        std::string newPath;
        newPath.assign(_path.begin(), _path.begin() + _path.length() - name().length());
        newPath.insert(newPath.length(), new_name);
        char *char_newPath = &newPath[0];
        char *char_path = &_path[0];
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
    struct stat _st;
    struct stat _stUpdate;
    std::string _path;
};

#endif
