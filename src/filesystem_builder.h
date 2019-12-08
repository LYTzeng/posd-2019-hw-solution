#ifndef FILESYSTEM_BUILDER_H
#define FILESYSTEM_BUILDER_H

#include <string>
#include <vector>

class Folder;
class File;
class Node;

class FileSystemBuilder
{
protected:
    FileSystemBuilder();

public:
    static FileSystemBuilder *instance();
    void build(std::string path);
    Node *getRoot();

private:
    static FileSystemBuilder *_builder;
    Node *_root;
    std::vector<std::string> _collectChildren(std::string path);
};
#endif
