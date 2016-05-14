#pragma once

template<class T>
/**
 * @brief The SharedPointer class
 * @detailed Class of counted smart-pointer
 */
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
    /**
     * @brief isNullPtr Checks if contains nullptr
     * @return true if contains nullptr, false if contains non-null pointer
     */
    bool isNullPtr()
    {
        return !sPtr->ptr;
    }
    /**
     * @brief counter Returns value of counter
     * @return Number of SharedPointers, who contains this pointer at the moment
     */
    unsigned int counter() const
    {
        return sPtr->counter;
    }
    /**
     * @brief operator -> Gives access to containing pointer
     * @return Containing pointer
     */
    T* operator->() const
    {
        return sPtr->ptr;
    }
    /**
     * @brief operator * Gives access to value of containing pointer
     * @return Dereferenced pointer
     */
    T operator*() const
    {
        return *sPtr->ptr;
    }
    /**
     * @brief operator = Operator of assignment
     * @param p Second SharedPointer(which we want assign to this SharedPointer)
     * @return This SharedPointer
     */
    SharedPointer<T>& operator=(SharedPointer<T>& p)
    {
        if (sPtr->ptr != p.sPtr->ptr)
        {
            sPtr->counter--;
            if (!sPtr->counter)
            {
                delete sPtr;
            }
            sPtr = p.sPtr;
            sPtr->counter++;
        }
        return *this;
    }

    /**
     * @brief The Storage class
     * @detailed Class-container for pointer
     */
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
