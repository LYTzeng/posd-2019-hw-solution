#ifndef FILESYSTEM_BUILDER_H
#define FILESYSTEM_BUILDER_H

#include <string>
#include <dirent.h>
class Folder;
class File;
class Node;

class FileSystemBuilder
{
protected:
    FileSystemBuilder();
    static FileSystemBuilder *builder;

public:
    static FileSystemBuilder *instance();
    void build(std::string path);
    Node *getRoot();

private:
    Node *_root;
    
};
#endif
