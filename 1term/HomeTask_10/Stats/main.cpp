#include <iostream>
#include <fstream>

using namespace std;

const unsigned int maxCode = 256;
struct Letter
{
    unsigned int quantity;
    unsigned int length;
};

bool openOutFile(fstream &outfile)
{
    outfile.open("stats.txt", ios_base::trunc);
    if (!outfile.is_open())//if don't exists
    {
        outfile.open("stats.txt", ios_base::in | ios_base::out | ios_base::trunc);//create
        return false;
    }
    else
    {
        return true;
    }
}
bool getInFileInformation(ifstream &infile);

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    Letter stats[maxCode];
    for (int i = 0; i < maxCode; i++)
    {
        stats[i].quantity = 0;
        stats[i].length = 0;
    }
    bool fl = false;
    while (true)
    {
        char current = infile.get();
        if (current == '\n' && fl)
        {
            infile.unget();
            break;
        }
        fl = true;
        infile.get();
        unsigned int t = 0;
        infile >> t;
        infile.get();
        stats[current].quantity = t;
    }
    while (!infile.eof())
    {
        infile.get();
        char current = infile.get();
        infile.get();
        infile.get();
        infile.get();
        unsigned int t = 0;
        while (infile.get() != '\'')
        {
            t++;
        }
        stats[current].length = t;
        infile.get();
    }

    fstream out;
    cout << (openOutFile(out) ? "Result in file 'stats.txt'" : "Was created file 'stats.txt'");
    for (int i = 0; i < maxCode; i++)
    {
        if (stats[i].length)
        {
            cout << (char) i << ": " << stats[i].quantity << " | " << stats[i].length << endl;
            out << (char) i << ": " << stats[i].quantity << " | " << stats[i].length << endl;
        }
    }

    unsigned long int incomeSize = 0;
    unsigned long int compressedSize = 0;
    unsigned long int quantity = 0;
    unsigned long int sumOfLenDiffChars = 0;

    for (int i = 0; i < maxCode; i++)
    {
        if (stats[i].length)
        {
            quantity ++;
            sumOfLenDiffChars += stats[i].length;
            incomeSize += (stats[i].quantity * 8);
            compressedSize += (stats[i].quantity * stats[i].length);
        }
    }
    cout << "in bits:\n";
    cout << "income size: " << incomeSize << "\ncompressed size: "
         << compressedSize << "+size of tree\naverage length: " << (double) sumOfLenDiffChars / (double) quantity;
    out << "in bits:\n";
    out << "income size: " << incomeSize << "\ncompressed size: "
         << compressedSize << "+size of tree\naverage length: " << (double) sumOfLenDiffChars / (double) quantity;
    infile.close();
    out.close();
    return 0;
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
