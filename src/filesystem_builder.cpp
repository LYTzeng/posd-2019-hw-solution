#include "filesystem_builder.h"
#include "node.h"
#include "folder.h"
#include "file.h"

FileSystemBuilder::FileSystemBuilder(){}

FileSystemBuilder *FileSystemBuilder::builder;

FileSystemBuilder *FileSystemBuilder::instance()
{
    if (FileSystemBuilder::builder == nullptr)
        FileSystemBuilder::builder = new FileSystemBuilder();
    return FileSystemBuilder::builder;
}
 
void FileSystemBuilder::build(std::string path)
{
    DIR *root;
    root = opendir(path.c_str());
    if (root == nullptr)
    {
        throw std::string("Not Exist");
    }
    _root = new Folder(path);
    struct dirent *dp;
    while ((dp = readdir(root)) != NULL)
    {
        if (dp->d_type == DT_REG)
        {
            Node *n = new File(std::string(path) + "/" + std::string(dp->d_name));
            _root->addChild(n);
        }
    }
}

Node *FileSystemBuilder::getRoot()
{
    return _root;
}