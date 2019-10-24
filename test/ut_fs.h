#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/utilities.h"

class NodeTest : public ::testing::Test{
protected:
  void SetUp() {
    hw = new Folder("test/test_folder/hw");
    a_out = new File("test/test_folder/hw/a.out");
    hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
    hello_txt= new File("test/test_folder/hello.txt");
    test_folder= new Folder("test/test_folder");
    hw->addChild(a_out);
    hw->addChild(hw1_cpp);
    test_folder->addChild(hello_txt);
    test_folder->addChild(hw);
  }
  void TearDown() {
    delete hw;
    delete a_out;
    delete hw1_cpp;
    delete hello_txt;
    delete test_folder;
  }
  Folder* hw;
  Node* a_out;
  Node* hw1_cpp;
  File* hello_txt;
  Node* test_folder;
};

TEST(StatApi, GetSize) {
  struct stat st;
  ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
  int size = st.st_size;
  ASSERT_EQ(14, size);
}


TEST_F(NodeTest, First) {
  ASSERT_EQ(14, hello_txt->size());
}

TEST_F(NodeTest, Second) {
  Node::Iterator * it= test_folder->createIterator();
  ASSERT_EQ(4096, test_folder->size());
  it->first();
  ASSERT_EQ(14, it->currentItem()->size());
  it->next();
  ASSERT_EQ(4096, it->currentItem()->size());
}

TEST_F(NodeTest, AddException){
  ASSERT_ANY_THROW(hello_txt->addChild(test_folder));
}

TEST_F(NodeTest, CatchException){
  try{
    hello_txt->addChild(test_folder);
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Invalid add!", s);
  }
}

TEST_F(NodeTest, InfoByteFunctionOnFile){
  ASSERT_EQ(14, infoByte(hello_txt));
}

TEST_F(NodeTest, InfoByteFunctionOnFolder){
  ASSERT_EQ(19027, infoByte(hw));
}

TEST_F(NodeTest, IteratorFromFolder) {
  Node::Iterator * it = hw->createIterator();
  it->first(); // Initialize
  ASSERT_EQ(a_out, it->currentItem());
  it->next();
  ASSERT_EQ(hw1_cpp, it->currentItem());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, IteratorFromFile){
  Node::Iterator* it= hello_txt->createIterator();
  ASSERT_TRUE(it->isDone());
}

#endif
