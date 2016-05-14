#include <iostream>
#include <fstream>

using namespace std;

struct Date
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

bool getInFileInformation(ifstream &infile);
bool isNumber(char ch);
bool isEmptyDate(Date date);
void printDate(Date date);
void changeDate(Date& date, unsigned int day, unsigned int month, unsigned int year);
bool compare(Date first, Date second);

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }

    bool noneMinDate = true;
    Date minDate{0, 0, 0};
    Date currentDate{0, 0, 0};
    char current = '\0';
    unsigned int pos = 1;
    unsigned int count_pos = 0;
    while (!infile.eof())
    {
        current = infile.get();
        if (infile.eof())
        {
            continue;
        }
        if ((currentDate.day < 32) && (currentDate.month < 13))
        {
            if (current == ' ')
            {
                if (!isEmptyDate(currentDate))
                {
                    if ((pos == 3) && ((noneMinDate) || (compare(currentDate, minDate))) && ((currentDate.day > 0) && (currentDate.month > 0) && (currentDate.year > 0)))
                    {
                        changeDate(minDate, currentDate.day, currentDate.month, currentDate.year);
                        noneMinDate = false;
                    }
                }
            }
            else if (isNumber(current))
            {
                count_pos++;
                if (pos == 1)
                {
                    if (count_pos < 3)
                    {
                        currentDate.day = currentDate.day * 10 + (current - '0');
                        continue;
                    }
                }
                if (pos == 2)
                {
                    if (count_pos < 3)
                    {
                        currentDate.month = currentDate.month * 10 + (current - '0');
                        continue;
                    }
                }
                if (pos == 3)
                {
                    if (count_pos < 5)
                    {
                        currentDate.year = currentDate.year * 10 + (current - '0');
                        continue;
                    }
                }
            }
            else if (current == '.')
            {
                pos++;
                if (pos < 4)
                {
                    count_pos = 0;
                    continue;
                }
            }
        }
        pos = 1;
        count_pos = 0;
        changeDate(currentDate, 0, 0, 0);
    }
    if (isEmptyDate(minDate))
    {
        cout << "There is not any dates in file";
    }
    else
    {
        cout << "Mininmal date in file is ";
        printDate(minDate);
    }
    infile.close();
    return 0;
}

bool compare(Date first, Date second)
{
    if (first.year < second.year)
    {
        return true;
    }
    else if (first.year == second.year)
    {
        if (first.month < second.month)
        {
            return true;
        }
        else if (first.month == second.month)
        {
            if (first.day < second.day)
            {
                return true;
            }
        }
    }
    return false;
}

void changeDate(Date& date, unsigned int day, unsigned int month, unsigned int year)
{
    date.day = day;
    date.month = month;
    date.year = year;
}

void printDate(Date date)
{
    cout << date.day << "." << date.month << "." << date.year;
}

bool isEmptyDate(Date date)
{
    return !(date.day || date.month || date.year);
}

bool isNumber(char ch)
{
    return ((ch >= '0') && (ch <= '9'));
}

bool getInFileInformation(ifstream &infile)
{
    cout << "Write file name(for input)[only utf-8 chars!]: ";
    char destination[100] = {'\0'};
    cin.getline(destination, 100);
    cout << "Trying to read file '" << destination << "' . . ." << endl;
    infile.open(destination);
    if (!infile.is_open())
    {
        cout << "Ups, i can't read your file! (maybe it is in wrong place)" << endl;
        return 1;
    }
    else
    {
        cout << "File successfuly loaded" << endl;
    }
    cout << endl;
    return 0;
}
