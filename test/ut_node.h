#include <string>
#include <iostream>
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/node.h"

TEST(File, TestValidFileName)
{
    Node *file = new File("./test/test_folder/file.txt");
    ASSERT_EQ("file.txt", file->name());
}

TEST(File, TestNotAFileException)
{
    try
    {
        Node *file = new File("./test/test_folder/folder");
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        EXPECT_EQ("It is not File!", e);
    }
}

TEST(Folder, TestValidFolderName)
{
    Node *folder = new Folder("./test/test_folder/folder");
    ASSERT_EQ("folder", folder->name());
}

TEST(Folder, TestNotAFolderException)
{
    try
    {
        Node *folder = new Folder("./test/test_folder/file.txt");
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        EXPECT_EQ("It is not Folder!", e);
    }
}

TEST(Node, TestNodeNotExists)
{
    try
    {
        Node *file = new Node("./test/test_folder/invalid.txt");
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        EXPECT_EQ("Node is not exist!", e);
    }
}

TEST(ListNode, TestListNodeOnFileException)
{
    try
    {
        Node *file = new File("./test/test_folder/file.txt");
        file->listNode();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string e)
    {
        EXPECT_EQ("Not a directory", e);
    }
}

TEST(ListNode, TestListNode)
{
    Node *folder = new Folder("./test/test_folder/folder");
    Node *A = new Folder("./test/test_folder/folder/A");
    Node *searchA = new File("./test/test_folder/folder/searchA.txt");
    Node *searchB = new File("./test/test_folder/folder/searchB.txt");
    folder->addChild(A);
    folder->addChild(searchA);
    folder->addChild(searchB);
    ASSERT_EQ("A searchA.txt searchB.txt", folder->listNode());
}

TEST(FindNode, TestFileFindFileSelf)
{
    Node *file = new File("./test/test_folder/folder/searchA.txt");
    ASSERT_EQ("searchA.txt", file->findNode("searchA.txt"));
}

TEST(FindNode, TestFolderFindFolderSelf)
{
    Node *folder = new Folder("./test/test_folder/folder");
    ASSERT_EQ("", folder->findNode("folder"));
}

TEST(FindNode, TestFolderFindFileMultiple)
{
    Node *folder = new Folder("./test/test_folder/folder");
    Node *A = new Folder("./test/test_folder/folder/A");
    Node *A_searchA = new File("./test/test_folder/folder/A/searchA.txt");
    A->addChild(A_searchA);
    folder->addChild(A);
    Node *searchA = new File("./test/test_folder/folder/searchA.txt");
    folder->addChild(searchA);
    ASSERT_EQ("./A/searchA.txt\n./searchA.txt", folder->findNode("searchA.txt"));
}

TEST(FindNode, TestFolderFindFolderMultiple)
{
    Node *test_folder = new Folder("./test/test_folder");
    Node *A = new Folder("./test/test_folder/A");
    test_folder->addChild(A);
    Node *folder = new Folder("./test/test_folder/folder");
    Node *folder_A = new Folder("./test/test_folder/folder/A");
    folder->addChild(folder_A);
    test_folder->addChild(folder);
    ASSERT_EQ("./A\n./folder/A", test_folder->findNode("A"));
}