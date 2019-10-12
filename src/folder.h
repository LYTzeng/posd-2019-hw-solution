#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <dirent.h>
#include "node.h"

class Folder : public Node
{
public:
    Folder(std::string path) : Node(path)
    {
        if (nodeType != "folder")
            throw(std::string("It is not Folder!"));

        DIR *opendir(const char *name);
        _directory = opendir(path.c_str());
    }

    void addChild(Node *child)
    {
        _v.push_back(child);
    }

    Node *getChild(int num)
    {
        return _v[num];
    }

    int infoByte()
    {
        int total = 0;
        for (int i = 0; i < _v.size(); i++)
        {
            total += _v.at(i)->infoByte();
        }
        return total;
    }

    std::string findNode(std::string name)
    {
        //TODO:
        // implementation findNode
        // folder->findNode(name) that should find all nodes(include child nodes and all offspring) under it.
        // file->findNode(name) that should find itself.
        // if find two nodes or more than two nodes.
        // Result should be separated by '\n'.
    }

    std::string listNode()
    {
        //TODO:
        // implementation list child Node and Sort by dictionary
        // Result should be separated by space
        // For example:
        // Folder contains childnode "a.out" and "TA_folder" and "hello.txt"
        // It should return "TA_folder a.out hello.txt"
        // If node is file, it can't listNode.
        // It should throw "Not a directory"
        // For Example: TA_file->listNode()
        struct dirent *readdir(DIR * dirp);
        int closedir(DIR * dirp);
        struct dirent *currentEntry;

        while ((currentEntry = readdir(_directory)) != NULL)
        {
            std::string S;
            S.assign(currentEntry->d_name);
            if (S == "." || S == "..")
                continue;
            nodeList.append(currentEntry->d_name);
            nodeList.append(" ");
        }
        if (nodeList.size() > 0)
            nodeList.erase(nodeList.size() - 1);

        return nodeList;
    }

private:
    std::vector<Node *> _v;
    DIR *_directory;
    std::string nodeList;
};
#endif
