#pragma once

template<class T>
class SharedPointer
{
public:
    SharedPointer() : sPtr(new Storage()){}
    SharedPointer(T* p) : sPtr(new Storage(p)){}
    SharedPointer(SharedPointer& p) : sPtr(p.sPtr)
    {
        sPtr->counter++;
    }
    ~SharedPointer()
    {
        sPtr->counter--;
        if (!sPtr->counter)
        {
            delete sPtr;
        }
    }
    bool isNullPtr()
    {
        return !sPtr->ptr;
    }
    unsigned int counter() const
    {
        return sPtr->counter;
    }
    T* operator->() const
    {
        return sPtr->ptr;
    }
    T operator*() const
    {
        return *sPtr->ptr;
    }
    SharedPointer<T>& operator=(SharedPointer<T>& p)
    {
        if (sPtr->ptr != p.sPtr->ptr)
        {
            if(counter())
            {
                delete sPtr;
            }
            sPtr = p.sPtr;
            sPtr->counter++;
        }
        return *this;
    }

    class Storage
    {
    private:
        Storage() : ptr(nullptr), counter(1){}
        Storage(T* p) : ptr(p), counter(1){}
        ~Storage()
        {
            delete ptr;
        }

        T* ptr;
        unsigned int counter;

        friend class SharedPointer;
    };
private:
    Storage *sPtr;
};
