#include "plist.h"
#include "ulist.h"

int main()
{
    PList plist;
    UList ulist;
    plist.add(1, 10);
    plist.add(2, 10);
    plist.add(3, 10);
    plist.add(4, 10);
    plist.add(5, 10);
    plist.add(5, 2);
    plist.add(5, 3);
    plist.printList();
    printf("\n");
    plist.swap(3, 1);
    plist.printList();
    printf("\n");
    for (int i = 1; i <= 7; i++)
    {
        int v = plist.returnValue(i);
        try
        {
            printf("\n%i\n", v);
            printf("!");
            ulist.add(v, i);
            printf("!");
        }
        catch(const AddingExistingItem &e)
        {
            printf("-");
            printf("%i", v);
            printf("-");
        }
    }
    printf("\n");
    ulist.printList();
    try
    {
        printf("!");
        ulist.delValue(20);
        printf("!");
    }
    catch(const RemovingNotExistingItem &e)
    {
        printf("-");
        printf("%i", 20);
        printf("-");
    }
    ulist.printList();
    return 0;
}

