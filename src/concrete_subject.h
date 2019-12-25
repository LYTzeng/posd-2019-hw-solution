#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H

#include "node.h"
#include "subject.h"
#include <vector>
#include <iterator>

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject(Node *root) : Subject(), _root(root) {}

    void attach(Observer *observer) override
    {
        observers.push_back(observer);
    }

    void detach(Observer *observer) override
    {
        std::vector<Observer *>::iterator it;
        for (it = observers.begin(); it != observers.end(); it++)
        {
            if (*it == observer)
            {
                observers.erase(it);
                break;
            }
        }
    }

    void notify() override
    {
        std::vector<Observer *>::iterator it;
        for (it = observers.begin(); it != observers.end(); it++)
        {
            (*it)->update();
        }
    }

    Node *getRootState()
    {
        return _root;
    }

private:
    Node *_root; // state
};

#endif
