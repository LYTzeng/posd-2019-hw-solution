#include <dirent.h>
#include <sys/stat.h>

#include "filesystem_builder.h"
#include "node.h"
#include "folder.h"
#include "file.h"
#include "iterator.h"

using strIterator = std::vector<std::string>::iterator;

FileSystemBuilder::FileSystemBuilder() {}

FileSystemBuilder *FileSystemBuilder::_builder;

FileSystemBuilder *FileSystemBuilder::instance()
{
    if (FileSystemBuilder::_builder == nullptr)
        FileSystemBuilder::_builder = new FileSystemBuilder();
    return FileSystemBuilder::_builder;
}

void FileSystemBuilder::build(std::string path)
{
    Folder *rootFolder = new Folder(path);
    std::vector<std::string> children = _collectChildren(path);
    for (strIterator it = children.begin(); it != children.end(); ++it)
    {
        try
        {
            Node *childFolder = new Folder(path + "/" + *it);
            rootFolder->addChild(childFolder);
        }
        catch (std::string err)
        {
            Node *childFile = new File(path + "/" + *it);
            rootFolder->addChild(childFile);
        }
    }
    _root = rootFolder;
}

Node *FileSystemBuilder::getRoot()
{
    return _root;
}

std::vector<std::string> FileSystemBuilder::_collectChildren(std::string path)
{
    DIR *opendir(const char *name);
    struct dirent *readdir(DIR * dirp);
    int closedir(DIR * dirp);
    DIR *directory;
    directory = opendir(path.c_str());
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