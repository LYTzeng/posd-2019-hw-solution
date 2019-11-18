#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

#include "node.h"
#include "folder.h"
#include "iterator.h"

//pratice here
int infoByte(Node *node)
{
    int total = 0;
    Folder *folder = dynamic_cast<Folder *>(node); // down cast
    if (folder != nullptr)
    { //it's a folder
        Iterator *it = folder->createIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            total += it->currentItem()->size();
        }
    }
    else
    {
        total += node->size();
    }
    return total;
}

class Utilities
{
public:
    std::string listNode(Node *node)
    {
        // You should use iterator pattern to access node in folder!
        // You can use dynamic_cast if you need
        // If node is file that it should throw string "Not a directory"
        // This function is same as Hw4 listNode()
        Folder *folder = dynamic_cast<Folder *>(node);
        if (folder == nullptr)
        {
            throw(std::string("Not a directory"));
        }

        std::string nodeList;
        std::set<std::string> sortedNodes;
        Iterator *it = folder->createIterator();
        it->first();

        for (int childNum = 0; childNum < it->size(); ++childNum)
        {
            Node *currentNode = it->currentItem();
            it->next();
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

    std::string findNode(Node *node, std::string name)
    {
        // You should use iterator pattern to access node in folder!
        // You can use dynamic_cast if you need
        // This function is same as Hw4 findNode()
        Folder *folder = dynamic_cast<Folder *>(node);

        if (folder == nullptr)
        {
            File *file = dynamic_cast<File *>(node);
            if (file->name() == name)
                return name;
            else
                return "\0";
        }
        // Result should be separated by '\n'.
        std::string searchResult;
        std::set<std::string> searchSet;

        std::string traverseResult = traverseSearch(node, name);

        std::string delimiter = "\n";
        size_t pos = 0;
        std::string singleNodeName;
        while ((pos = traverseResult.find(delimiter)) != std::string::npos)
        {
            singleNodeName = traverseResult.substr(0, pos);
            searchSet.insert(singleNodeName);
            traverseResult.erase(0, pos + delimiter.length());
        }

        for (std::string element : searchSet)
        {
            std::string parsed;
            std::string pathString = node->getPath();
            element.erase(0, pathString.length());
            if (element != "")
            {
                element = "." + element;
                searchResult.append(element);
                searchResult.append("\n");
            }
        }
        if (searchResult.size() > 0)
            searchResult.erase(searchResult.size() - 1);
        return searchResult;
    }

    std::string traverseSearch(Node *node, std::string name)
    {
        std::string traverseResult;
        // if the folder path is the result itself
        if (node->name() == name)
        {
            traverseResult.append(node->getPath());
            traverseResult.append("\n");
        }
        Iterator *it = node->createIterator();
        it->first();
        for (int childNum = 0; childNum < it->size(); childNum++)
        {
            Node *currentNode = it->currentItem();
            // file name match the search string
            if (currentNode->nodeType == "file" && currentNode->name() == name)
            {
                traverseResult.append(currentNode->getPath());
                traverseResult.append("\n");
            }
            // search for nodes under folder
            if (currentNode->nodeType == "folder")
            {
                std::string subtraverseResult;
                subtraverseResult = traverseSearch(currentNode, name);
                traverseResult.append(subtraverseResult);
            }
            it->next();
        }
        return traverseResult;
    }
};
#endif
