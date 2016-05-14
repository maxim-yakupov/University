#include "stdio.h"
#include "calculator.h"
#include "testStack.h"
#include "testCalculator.h"

using namespace std;

int main()
{
//    tests
    TestStack testStack;
    QTest::qExec(&testStack);
    TestCalculator testCalculator;
    QTest::qExec(&testCalculator);
//    end tests
    printf("************************* Begin program *************************\nWrite expression: ");
    char* incomeStr = new char[1000];
    scanf("%s", incomeStr);
    Calculator<ArrayStack<TokenStruct>, ArrayStack<double>> calc(incomeStr);
    //You can change PointerStack & ArrayStack( Calculator<...<char>, ...<double>> )
    printf("Result: %g\n\n", calc.compute());
    //
    while (true)
    {
        printf("Write expression(type 'q' to finish): ");
        scanf("%s", incomeStr);
        if (incomeStr[0] == 'q') break;
        calc(incomeStr);
        printf("Result: %g\n\n", calc.compute());
    }
    //
    delete [] incomeStr;
    return 0;
}
