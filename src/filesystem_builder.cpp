#include <dirent.h>
#include <sys/stat.h>

#include "filesystem_builder.h"
#include "node.h"
#include "folder.h"
#include "file.h"
#include "link.h"
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
    struct stat _st;
    stat(path.c_str(), &_st);
    switch (_st.st_mode & S_IFMT)
    {
    case S_IFREG: // file
        buildFile(path);
        break;
    case S_IFDIR: // folder
        buildFolder(path);
        break;
    case S_IFLNK: // symlink
        buildLink(path);
        break;
    }
}

Node *FileSystemBuilder::getRoot()
{
    return _root;
}

void FileSystemBuilder::buildFolder(std::string path)
{
    Folder *rootFolder = new Folder(path);
    std::vector<std::string> children = _collectChildren(path);
    for (strIterator it = children.begin(); it != children.end(); ++it)
    {
        FileSystemBuilder *fb = FileSystemBuilder::instance();
        fb->build(path + "/" + *it);
        rootFolder->addChild(fb->getRoot());
    }
    _root = rootFolder;
}

void FileSystemBuilder::buildFile(std::string path)
{
    _root = new File(path);
}

void FileSystemBuilder::buildLink(std::string path)
{

    _root = new Link(path);
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