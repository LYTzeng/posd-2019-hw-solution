#include <string>
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
    ASSERT_EQ("A B searchA.txt searchB.txt", folder->listNode());
}

TEST(ListNode, TestListNodeEmptyDir)
{
    Node *folder = new Folder("./test/test_folder/folder/B");
    ASSERT_EQ("", folder->listNode());
}

// TEST(FindNode, TestFolderFindNodeMultiple)
// {
//     Node *file = new Folder("./test/test_folder/folder");
//     ASSERT_EQ("./searchA.txt\n./A/searchA.txt", file->findNode("searchA.txt"));
// }
