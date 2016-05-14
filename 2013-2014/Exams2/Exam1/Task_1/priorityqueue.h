#pragma once

template <class T>
/**
 * @brief The PriorityQueue class
 */
class PriorityQueue
{
public:
    /**
     * @brief The EmptyQueueReturnException exception
     */
    class EmptyQueueReturnException{};
    /**
     * @brief PriorityQueue Constructor of PriorityQueue, initialized empty
     */
    PriorityQueue();
    ~PriorityQueue();
    /**
     * @brief enqueue Adds member in queue
     * @param value Value, which we add
     * @param priority Priority in queue
     */
    void enqueue(T value, int priority);
    /**
     * @brief dequeue Returns value with high priority & removes it from queue
     * @return Value with high priority
     * @throw If queue is empty, throws EmptyQueueReturnException
     */
    T dequeue();
private:
    struct Member
    {
        T value;
        int priority;
        Member* prev;
    };
    Member* head;
    unsigned int length;
};

template <class T>
PriorityQueue<T>::PriorityQueue() : head(nullptr), length(0)
{
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    for (int i = 0; i < length; i++)
    {
        dequeue();
    }
}

template <class T>
void PriorityQueue<T>::enqueue(T value, int priority)
{
    if (!length)
    {
        head = new Member{value, priority, nullptr};
    }
    else if (priority > head->priority)
    {
        head = new Member{value, priority, head};
    }
    else
    {
        Member* currentMember = head;
        for (unsigned int i = 0; i < length; i++)
        {
            if ((!currentMember->prev) || (currentMember->prev->priority < priority))
            {
                break;
            }
            currentMember = currentMember->prev;
        }
        currentMember->prev = new Member{value, priority, currentMember->prev};
    }
    length++;
}

template <class T>
T PriorityQueue<T>::dequeue()
{
    if (!length)
    {
        throw EmptyQueueReturnException();
    }
    else
    {
        T value = head->value;
        length--;
        Member* newHead = head->prev;
        delete head;
        head = newHead;
        return value;
    }
}
