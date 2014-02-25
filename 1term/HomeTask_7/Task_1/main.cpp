#include <iostream>

using namespace std;

int getSource(int works[], int student)
{
    if (works[student] < 4)
    {
        return works[student];
    }
    else
    {
        return getSource(works, works[student]);
    }
}

int main()
{
    int amountOfStudents = 0;
    cout << "Write number of students: ";
    cin >> amountOfStudents;
    int iworks[amountOfStudents + 1];
    iworks[0] = 0;
    iworks[1] = 1;
    iworks[2] = 2;
    iworks[3] = 3;
    for (int i = 4; i <= amountOfStudents; i++)
    {
        iworks[i] = iworks[0];
    }
    int student, source;
    cout << "Now write pares [student] [source_student]" << endl;
    cout << "(if you want to stop entering, write 0 or type Ctrl+z {Enter})" << endl;
    while ((cin >> student) && (student != 0) && (cin >> source))
    {
        iworks[student] = source;
    }
    for (int i = 1; i <= amountOfStudents; i++)
    {
        source = getSource(iworks, i);
        cout << "\n" << i << " ";
        if (source)
        {
            cout << source;
        }
        else
        {
            cout << "otchislen";
        }
    }
    return 0;
}

