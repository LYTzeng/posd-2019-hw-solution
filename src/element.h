class Element{
public:
    Element(){
    }

    virtual void add(Element * s) = 0;

    virtual int size()=0;

    virtual std::string toString() = 0;

    virtual Iterator * createIterator() = 0;

    virtual void setOperator(char ope) = 0;

    virtual void accept(Visitor * fsv) = 0;

};