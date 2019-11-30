#include <gtest/gtest.h>

#include <string>
#include "../src/integer.h"
#include "../src/set.h"
#include "../src/iterator.h"
#include "../src/element.h"
#include "../src/null_iterator.h"
#include "../src/visitor.h"
#include "../src/flattened_set_visitor.h"
#include "../src/evaluate_visitor.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class Test : public testing::Test
{
  protected:
    void SetUp() override
    {
        int10 = new Integer(10);
        int20 = new Integer(20);
        int3 = new Integer(3);
        int400 = new Integer(400);
        intSet1 = new Set(); // 10 20
        intSet2 = new Set(); // 3 400
        intSet1->add(int10);
        intSet1->add(int20);
        intSet2->add(int3);
        intSet2->add(int400);
        intSet1->add(intSet2);
    }
    void TearDown() override
    {
        delete int10;
        delete int20;
        delete int3;
        delete int400;
        delete intSet1;
        delete intSet2;
    }
    Integer *int10;
    Integer *int20;
    Integer *int3;
    Integer *int400;
    Set *intSet1;
    Set *intSet2;
};

TEST_F(Test, Integer)
{
    try
    {
        int10->add(int20);
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string s)
    {
        ASSERT_EQ("It's an integer!", s);
    }

    ASSERT_EQ(1, int10->size());
    ASSERT_EQ("10", int10->toString());
    // Test null iterator exceptions.
    Iterator *it = int10->createIterator();
    try
    {
        it->first();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string s)
    {
        ASSERT_EQ("No child member!", s);
    }
    try
    {
        it->currentItem();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string s)
    {
        ASSERT_EQ("No child member!", s);
    }
    try
    {
        it->next();
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string s)
    {
        ASSERT_EQ("No child member!", s);
    }
    // Set Operator exception.
    try
    {
        int10->setOperator('+');
    }
    catch (std::string s)
    {
        ASSERT_EQ("Cannot set operator on it!", s);
    }
}

TEST_F(Test, Set)
{
    ASSERT_EQ("{10,20,{3,400}}", intSet1->toString());
    intSet1->add(new Set());
    ASSERT_EQ("{10,20,{3,400},{}}", intSet1->toString());
    try
    {
        intSet1->setOperator('@');
        FAIL() << "Expected exceptional exception";
    }
    catch (std::string s)
    {
        ASSERT_EQ("Invalid operator!", s);
    }
}

TEST_F(Test, FlattenedSetVisitor)
{
    FlattenedSetVisitor *fsv = new FlattenedSetVisitor();
    intSet1->accept(fsv);
    ASSERT_EQ("{10,20,3,400}", fsv->getResult()->toString());
    int10->accept(fsv);
    ASSERT_EQ("10", fsv->getResult()->toString());
    // intSet1->add(new Set());
    // intSet1->accept(fsv);
    // ASSERT_EQ("{10,20,3,400}", fsv->getResult()->toString());
}

TEST_F(Test, EvaluateVisitor)
{
    EvaluateVisitor *ev = new EvaluateVisitor();
    intSet1->accept(ev);
    ASSERT_EQ(433.0, ev->getResult());

    intSet2->setOperator('-'); // 3-400
    ASSERT_EQ('-', intSet2->getOpe());
    intSet1->accept(ev);
    ASSERT_EQ(-367.0, ev->getResult());

    intSet2->setOperator('*'); // 3*400
    intSet1->accept(ev);
    ASSERT_EQ(1230.0, ev->getResult());  

    intSet2->setOperator('/'); // 3/400
    intSet1->accept(ev);
    ASSERT_EQ(30.0075, ev->getResult());  

    Integer *intTemp1 = new Integer(99);
    Integer *intTemp2 = new Integer(0);
    Set * intSet3 = new Set();
    intSet3->add(intTemp1);
    intSet3->add(intTemp2);
    intSet3->setOperator('/'); // 99/0
    try{
        intSet3->accept(ev);
        FAIL() << "Expected exceptional exception";        
    }
    catch(std::string s)
    { 
        ASSERT_EQ("Divide by zero!", s);
    }
}