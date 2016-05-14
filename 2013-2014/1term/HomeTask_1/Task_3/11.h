#include <iostream>

using namespace std;

int main()
{
   const int arrayLength = 10;
   cout << "Enter limiters 'm' and 'n' (m+n <= " << arrayLength << " ): ";
   int m,n;
   cin >> m >> n;
   cout << endl;
   cout << "Do you want to [E]nter elements of array or [g]enerate them for you? ";
   char ch;
   cin >> ch;
   cout << endl;
   //
   int array[arrayLength];
   switch (ch)
   {
       case 'E':
       {
           cout << "Your array: ";
           for (int i = 0; i < m+n; i++)
           {
               cin >> array[i];
           };
           break;
       };
       //
       case 'g':
       {
       cout << "Enter seed(number) for random generation: ";
           int seed;
           cin >> seed;
           cout << endl;
           srand(seed);
           cout << "Your array: ";
           for (int i = 0; i < m+n; i++)
           {
               array[i] = rand() %100;
               cout << array[i] << " ";
               if (i == m-1)
               {
                   cout << "| ";
               };
           };
           break;
       };
       //
       default:
           break;
   };
   cout << endl;
   //
   int t;
   for (int i = 0; i <= (m-1)/2; i++)
   {
       t = array[i];
       array[i] = array[m-1-i];
       array[m-1-i] = t;
   };
   //
   for (int i = m; i <= (m-1+(n/2)); i++)
   {
       t = array[i];
       array[i] = array[m+n-1+(-i+m)];
       array[m+n-1+(-i+m)] = t;
   };
   //
   for (int i = 0; i <= -1+(m+n)/2; i++)
   {
       t = array[i];
       array[i] = array[m+n-1-i];
       array[m+n-1-i] = t;
   };
   //
   cout << "Array after transposition: ";
   for (int i = 0; i < m+n; i++)
   {
       cout << array[i] << " ";
       if (i == n-1)
       {
           cout << "| ";
       };
   };
   return 0;
}
