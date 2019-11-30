#ifndef SET_H
#define SET_H

#include <string>
#include <vector>
#include <map>
#include "element.h"

class Set : public Element
{
  public:
    class SetIterator : public Iterator
    {
      public:
        SetIterator(Set *s) : _s(s) {}
        void first()
        {
            _current = _s->_map.begin();
        }
        Element *currentItem()
        {
            if (_s->_map.size() == 0 || _current == _s->_map.end())
                throw std::string("No current item!");
            // return _current->second;
            return *_current;
        }
        void next()
        {
            if ((_current++) == _s->_map.end())
                throw std::string("Moving past the end!");
        }
        bool isDone()
        {
            return _current == _s->_map.end();
        }
        int size()
        {
            return _s->_map.size();
        }

      private:
        Set *_s;
        // std::map<std::string, Element *>::iterator _current;
        std::vector<Element *>::iterator  _current;
    };

  public:
    Set()
    {
        _operator = '+';
    }
    void add(Element *element)
    {
        // _map[element->toString()] = element;
        _map.push_back(element);
    }
    int size()
    {
        return _map.size();
    }
    std::string toString()
    {
        std::string result = "{";
        if (size() != 0)
        {
            Iterator *it = createIterator();
            it->first();
            for (int childNum = 0; childNum < it->size(); childNum++)
            {
                result.append(it->currentItem()->toString());
                result.append(",");
                it->next();
            }
            result.erase(result.end() - 1, result.end());
        }
        result.append("}");
        return result;
    }
    Iterator *createIterator()
    {
        return new SetIterator(this);
    }
    void setOperator(char ope)
    {
        if (ope != '+' && ope != '-' && ope != '*' && ope != '/')
            throw(std::string("Invalid operator!"));
        
        _operator = ope;
    }
    void accept(Visitor *fsv)
    {
        fsv->visitSet(this);
    }

    char getOpe() // getter
    {
        return _operator;
    }

  private:
    char _operator;
    // std::map<std::string, Element *> _map;
    std::vector<Element*> _map;
};

#endif