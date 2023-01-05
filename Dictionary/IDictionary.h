#ifndef _IDICTIONARY_H
#define _IDICTIONARY_H

#include <string>
#include <iostream>

template <class Key, class Value>
class IPair
{
    virtual void setKey(Key key) = 0;
    virtual Key getKey() = 0;

    virtual void setValue(Value value) = 0;
    virtual Value getValue() = 0;
};


template <class Key, class Value>
class IDictionary
{
    public:
        virtual bool isEmpty() const = 0;
        virtual int search(const Key& key) = 0;

        virtual bool has(const Key& key) = 0;
        virtual IPair<Key, Value>* get(const Key& key) = 0;

        virtual void insert(const Key& key, const Value& value) = 0;
        virtual void erase(const Key& key) = 0;
        virtual void update(const Key& key, const Value& value) = 0;
};



#endif // _IDICTIONARY_H
