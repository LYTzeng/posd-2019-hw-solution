#include <set>
#include "find_visitor.h"
#include "folder.h"
#include "file.h"
#include "link.h"

FindVisitor::FindVisitor(std::string name) : _name(name) {}

void FindVisitor::visitFolder(Folder *folder)
{
    std::string searchResult;
    std::set<std::string> searchSet;

    std::string traverseResult = traverseSearch(folder, _name);
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
        std::string pathString = folder->getPath();
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

    _searchResult.assign(searchResult.begin(), searchResult.end());
}

void FindVisitor::visitFile(File *file)
{
    if (file->name() == _name)
        _searchResult.assign(_name.begin(), _name.end());
    else
        _searchResult.assign("\0", 0);
}

void FindVisitor::visitLink(Link *link)
{
    if (link->name() == _name)
        _searchResult.assign(_name.begin(), _name.end());
    else
        _searchResult.assign("\0", 0);
}

std::string FindVisitor::findResult()
{
    return _searchResult;
}

std::string FindVisitor::traverseSearch(Node *node, std::string name) // This function is for FindVisitor::visitFolder() only.
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
        // file or link name match the search string
        if ((currentNode->nodeType == "file" || currentNode->nodeType == "symlink") && currentNode->name() == name)
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
