#include "stdio.h"
#include "calculator.h"

using namespace std;

int main()
{
    printf("Write expression: ");
    char* incomeStr = new char[1000];
    scanf("%s", incomeStr);
    Calculator<ArrayStack<char>, PointerStack<double>> calc(incomeStr);
    //You can change PointerStack & ArrayStack( Calculator<...<char>, ...<double>> )
    printf("Result: %g", calc.compute());
    delete [] incomeStr;
    return 0;
}
