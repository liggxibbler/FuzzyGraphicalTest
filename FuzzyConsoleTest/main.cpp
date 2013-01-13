#include "FIS_Init.h"
#include <iostream>

using namespace Fuzzy;
using namespace std;

int main()
{
	float input[2];
	FIS_Init* fis = new FIS_Init;
	fis->Initialize();

	cout.precision(3);

	for(int i=0; i<=9; i++)
	{
		for(int j =0; j<= 9;j++)
		{
			input[0] = -1.0 + (2.0/9.0) * i;
			input[1] = -1.0 + (2.0/9.0) * j;
			cout << fis->Evaluate(input)[0] << "\t";
		}
		cout << endl;
	}
	return 0;
}