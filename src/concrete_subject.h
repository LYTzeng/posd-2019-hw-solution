#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H

#include "node.h"
#include "subject.h"
#include "update_path_visitor.h"
#include <vector>
#include <iterator>
#include <wx/treectrl.h>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

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

    void notify(wxTreeItemId savedFileId) override
    {
        std::vector<Observer *>::iterator it;
        for (it = observers.begin(); it != observers.end(); it++)
        {
            (*it)->update(savedFileId);
        }
    }

    Node *getRootState()
    {
        return _root;
    }

    Node *getNodeById(wxTreeItemId id)
    {
        return _map[id];
    }

    void setTreeNodeItemId(wxTreeItemId id, Node *node)
    {
        _map[id] = node;
    }

    std::string getTreeNodeContentById(wxTreeItemId id)
    {
        std::string nodeType = _map[id]->nodeType;
        if (nodeType == "folder")
        {
            return std::string("");
        }
        else if (nodeType != "file")
        {
            return std::string("The file is not displayed in the editor because it uses an unsupported text encoding.");
        }
        std::string content = _readFile(_map[id]->getPath());
        if (_is_valid_utf8(content.c_str()))
        {
            return content;
        }
        return std::string("The file is not displayed in the editor because it uses an unsupported text encoding.");
    }

    void setNodeName(wxTreeItemId id, std::string newName)
    {
        _map[id]->renameNode(newName);
        UpdatePathVisitor *upv = new UpdatePathVisitor();
        _map[id]->accept(upv);
    }

    void setTreeNodeContentById(wxTreeItemId id, std::string newContent)
    {
        _writeFile(_map[id]->getPath(), newContent);
        notify(id);
    }

private:
    Node *_root; // state
    std::map<wxTreeItemId, Node *> _map;

    std::string _readFile(std::string path)
    {
        std::ifstream ifs(path);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        return content;
    }

    void _writeFile(std::string path, std::string newContent)
    {
        std::ofstream file(path);
        std::string singleLine;
        if (file.is_open())
        {
            file << newContent << "\n";
            file.close();
        }
    }

    bool _is_valid_utf8(const char *string)
    {
        if (!string)
            return true;

        const unsigned char *bytes = (const unsigned char *)string;
        unsigned int cp;
        int num;

        while (*bytes != 0x00)
        {
            if ((*bytes & 0x80) == 0x00)
            {
                // U+0000 to U+007F
                cp = (*bytes & 0x7F);
                num = 1;
            }
            else if ((*bytes & 0xE0) == 0xC0)
            {
                // U+0080 to U+07FF
                cp = (*bytes & 0x1F);
                num = 2;
            }
            else if ((*bytes & 0xF0) == 0xE0)
            {
                // U+0800 to U+FFFF
                cp = (*bytes & 0x0F);
                num = 3;
            }
            else if ((*bytes & 0xF8) == 0xF0)
            {
                // U+10000 to U+10FFFF
                cp = (*bytes & 0x07);
                num = 4;
            }
            else
                return false;

            bytes += 1;
            for (int i = 1; i < num; ++i)
            {
                if ((*bytes & 0xC0) != 0x80)
                    return false;
                cp = (cp << 6) | (*bytes & 0x3F);
                bytes += 1;
            }

            if ((cp > 0x10FFFF) ||
                ((cp >= 0xD800) && (cp <= 0xDFFF)) ||
                ((cp <= 0x007F) && (num != 1)) ||
                ((cp >= 0x0080) && (cp <= 0x07FF) && (num != 2)) ||
                ((cp >= 0x0800) && (cp <= 0xFFFF) && (num != 3)) ||
                ((cp >= 0x10000) && (cp <= 0x1FFFFF) && (num != 4)))
                return false;
        }

        return true;
    }
};

#endif
