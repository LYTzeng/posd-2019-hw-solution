#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <dirent.h>
#include <iostream>
#include <iterator>
#include <set>
#include "node.h"

using strIterator = std::vector<std::string>::iterator;
using nodePtrIterator = std::vector<Node *>::iterator;

class Folder : public Node
{
public:
    Folder(std::string path) : Node(path), _path(path)
    {
        if (nodeType != "folder")
            throw(std::string("It is not Folder!"));

        traverseAdd();
    }

    void addChild(Node *child)
    {
        _v.push_back(child);
    }

    Node *getChild(int num)
    {
        // Get nth child
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

    std::string findNode(std::string name) override
    {
        // implementation findNode
        // folder->findNode(name) that should find all nodes(include child nodes and all offspring) under it.
        // file->findNode(name) that should find itself.
        // if find two nodes or more than two nodes.
        // Result should be separated by '\n'.
        std::string searchResult = traverseSearch(name);
        if (searchResult.size() > 0)
            searchResult.erase(searchResult.size() - 1);
        return searchResult;
    }

    std::string listNode() override
    {
        // implementation list child Node and Sort by dictionary
        // Result should be separated by space
        // For example:
        // Folder contains childnode "a.out" and "TA_folder" and "hello.txt"
        // It should return "TA_folder a.out hello.txt"
        // For Example: TA_file->listNode()
        std::string nodeList;
        std::set<std::string> sortedNodes;

        for (int childNum = 0; childNum < _v.size(); ++childNum)
        {
            Node *currentNode = getChild(childNum);
            sortedNodes.insert(currentNode->name());
        }

        for (std::string node : sortedNodes)
        {
            nodeList.append(node);
            nodeList.append(" ");
        }

        if (nodeList.size() > 0)
            nodeList.erase(nodeList.size() - 1);

        return nodeList;
    }

    std::string relativePath() override
    {
        return _path + "/" + Node::name();
    }

    void traverseAdd()
    {
        std::vector<std::string> children = _collectChildren();
        for (strIterator it = children.begin(); it != children.end(); ++it)
        {
            try
            {
                Node *childFolder = new Folder(_path + "/" + *it);
                Folder::addChild(childFolder);
            }
            catch (std::string err)
            {
                Node *childFile = new File(_path + "/" + *it);
                Folder::addChild(childFile);
            }
        }
    }

    std::string traverseSearch(std::string name)
    {
        std::string searchResult;
        // if the folder path is the result itself
        if (Node::name() == name)
        {
            searchResult.append(Node::relativePath());
            searchResult.append("\n");
        }
        int childNum = 0;
        for (childNum; childNum < _v.size(); ++childNum)
        {
            Node *currentNode = getChild(childNum);
            // file name match the search string
            if (currentNode->nodeType == "file" && currentNode->name() == name)
            {
                searchResult.append(currentNode->relativePath());
                searchResult.append("\n");
            }
            // search for nodes under folder
            if (currentNode->nodeType == "folder")
            {
                std::string subSearchResult;
                subSearchResult = currentNode->traverseSearch(name);
                searchResult.append(subSearchResult);
            }
        }
        return searchResult;
    }

private:
    std::vector<Node *> _v;
    std::string _path;

    std::vector<std::string> _collectChildren()
    {
        DIR *opendir(const char *name);
        struct dirent *readdir(DIR * dirp);
        int closedir(DIR * dirp);
        DIR *directory;
        directory = opendir(_path.c_str());
        struct dirent *currentEntry;

        std::vector<std::string> children;
        while ((currentEntry = readdir(directory)) != NULL)
        {
            std::string s;
            s.assign(currentEntry->d_name);
            if (s == "." || s == "..")
                continue;
            children.push_back(s);
        }
        closedir(directory);
        return children;
    }
};
#endif
