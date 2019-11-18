#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/utilities.h"
#include "../src/iterator.h"
#include "../src/find_visitor.h"
#include "../src/update_path_visitor.h"

class NodeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        hw = new Folder("test/test_folder/hw");
        a_out = new File("test/test_folder/hw/a.out");
        hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
        hello_txt = new File("test/test_folder/hello.txt");
        hf_txt = new File("test/test_folder/hf.txt");
        test_folder = new Folder("test/test_folder");
        hw_hello_txt = new File("test/test_folder/hw/hello.txt");
        empty = new Folder("test/test_folder/empty");
        hw->addChild(a_out);
        hw->addChild(hw1_cpp);
        hw->addChild(hw_hello_txt);
        test_folder->addChild(hello_txt);
        test_folder->addChild(hf_txt);
        test_folder->addChild(hw);
    }
    void TearDown() override
    {
        delete hw;
        delete a_out;
        delete hw1_cpp;
        delete hello_txt;
        delete test_folder;
        delete utilities;
        delete hw_hello_txt;
    }
    Folder *hw;
    Node *a_out;
    Node *hw1_cpp;
    File *hello_txt;
    File *hf_txt;
    Node *test_folder;
    Utilities *utilities;
    File *hw_hello_txt;
    Folder *empty;
};

TEST(StatApi, GetSize)
{
    struct stat st;
    ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
    int size = st.st_size;
    ASSERT_EQ(14, size);
}

TEST_F(NodeTest, First)
{
    ASSERT_EQ(14, hello_txt->size());
}

TEST_F(NodeTest, Second)
{
    Iterator *it = test_folder->createIterator();
    ASSERT_EQ(4096, test_folder->size());
    it->first();
    ASSERT_EQ(14, it->currentItem()->size());
    it->next();
    ASSERT_EQ(13, it->currentItem()->size());
}

TEST_F(NodeTest, AddException)
{
    ASSERT_ANY_THROW(hello_txt->addChild(test_folder));
}

TEST_F(NodeTest, CatchException)
{
    try
    {
        hello_txt->addChild(test_folder);
        ASSERT_EQ(true, false);
    }
    catch (std::string s)
    {
        ASSERT_EQ("Invalid add!", s);
    }
}

TEST_F(NodeTest, InfoByteFunctionOnFile)
{
    ASSERT_EQ(14, infoByte(hello_txt));
}

TEST_F(NodeTest, InfoByteFunctionOnFolder)
{
    ASSERT_EQ(19027, infoByte(hw));
}

TEST_F(NodeTest, IteratorFromFolder)
{
    Iterator *it = hw->createIterator();
    it->first(); // Initialize
    ASSERT_EQ(a_out, it->currentItem());
    it->next();
    ASSERT_EQ(hw_hello_txt, it->currentItem());
    it->next();
    ASSERT_EQ(hw1_cpp, it->currentItem());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, IteratorFromFile)
{
    Iterator *it = hello_txt->createIterator();
    ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, FolderIteratorException)
{
    Iterator *it = test_folder->createIterator();
    it->first();
    it->next();
    it->next();
    it->next();
    try
    {
        it->next();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        ASSERT_EQ("Moving past the end!", e);
    }

    try
    {
        it = empty->createIterator();
        it->first();
        it->currentItem();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        ASSERT_EQ("No current item!", e);
    }
}

TEST_F(NodeTest, FileCallIteratorMethodException)
{
    Iterator *it;
    it = hello_txt->createIterator();

    try
    {
        it->first();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        ASSERT_EQ("no child member", e);
    }

    try
    {
        it->next();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        ASSERT_EQ("no child member", e);
    }

    ASSERT_TRUE(it->isDone());

    try
    {
        it->currentItem();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        ASSERT_EQ("no child member", e);
    }
}

TEST_F(NodeTest, ListNode)
{
    ASSERT_EQ("hello.txt hf.txt hw", utilities->listNode(test_folder));
}

TEST_F(NodeTest, ListNodeOnFileException)
{
    try
    {
        utilities->listNode(a_out);
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        ASSERT_EQ("Not a directory", e);
    }
}

TEST_F(NodeTest, FileFindFileSelf)
{
    ASSERT_EQ("hello.txt", utilities->findNode(hello_txt, "hello.txt"));
}

TEST_F(NodeTest, FolderFindFolderSelf)
{
    ASSERT_EQ("", utilities->findNode(test_folder, "test_folder"));
}

TEST_F(NodeTest, FolderFindFileMultiple)
{
    ASSERT_EQ("./hello.txt\n./hw/hello.txt", utilities->findNode(test_folder, "hello.txt"));
}

TEST_F(NodeTest, FolderFindFolder)
{
    ASSERT_EQ("./hw", utilities->findNode(test_folder, "hw"));
}

/*
██╗  ██╗██╗    ██╗     ██████╗ 
██║  ██║██║    ██║    ██╔════╝ 
███████║██║ █╗ ██║    ███████╗ 
██╔══██║██║███╗██║    ██╔═══██╗
██║  ██║╚███╔███╔╝    ╚██████╔╝
╚═╝  ╚═╝ ╚══╝╚══╝      ╚═════╝ 
*/

TEST_F(NodeTest, NodeTypeError)
{
    ASSERT_ANY_THROW(new File("./123"));                       //If the node doesn't exist, you should throw string "Node is not exist!"
    ASSERT_ANY_THROW(new File("./test/test_folder"));          //If the File doesn't exist, you should throw string "It is not File!"
    ASSERT_ANY_THROW(new Folder("./test/test_folder/hf.txt")); //If the Folder doesn't exist, you should throw string "It is not Folder!"
    ASSERT_ANY_THROW(new Link("./test/test_folder", a_out));   //If the Link doesn't exist, you should throw string "It is not Link!"
}

TEST_F(NodeTest, Link)
{
    Link *ln = new Link("./test/test_folder/symlink_a", a_out);
    Node *sym_a_out = ln->getSource();
    ASSERT_EQ(a_out, sym_a_out);
}

TEST_F(NodeTest, Node_getPath)
{
    ASSERT_EQ("test/test_folder/hw", hw->getPath());
    ASSERT_EQ("test/test_folder/hw/a.out", a_out->getPath());
}

TEST_F(NodeTest, FindVisitor_findResult)
{
    FindVisitor *fv = new FindVisitor("hello.txt");
    hello_txt->accept(fv);
    ASSERT_EQ("hello.txt", fv->findResult());
    test_folder->accept(fv);
    ASSERT_EQ("./hello.txt\n./hw/hello.txt", fv->findResult());
    hw->accept(fv);
    ASSERT_EQ("./hello.txt", fv->findResult());
}

TEST_F(NodeTest, Node_RenameNode)
{
    hw->renameNode("homework6");
    UpdatePathVisitor *upv = new UpdatePathVisitor();
    hw->accept(upv);
    ASSERT_EQ("homework6", hw->name());
    ASSERT_EQ("test/test_folder/homework6", hw->getPath());
    ASSERT_EQ("a.out", a_out->name());
    ASSERT_EQ("test/test_folder/homework6/a.out", a_out->getPath());
    ASSERT_EQ("test/test_folder/homework6/hello.txt", hw_hello_txt->getPath());
    ASSERT_EQ("test/test_folder/homework6/hw1.cpp", hw1_cpp->getPath());
    struct stat _st;
    if (lstat("test/test_folder/homework6", &_st) != 0)
        FAIL(); // Check the physical node name!
}

#endif
