#include "TxtHandleCombo.h"
int main()
{
	ReadTxtToVector txt;
	txt.readToVector(L"F:/123.log", 1024);
	//txt.showOneByOneOfVector(1000);
	std::cout << txt.returnTxtLineNumber() << std::endl;
	system("pause");
	return 0;
}