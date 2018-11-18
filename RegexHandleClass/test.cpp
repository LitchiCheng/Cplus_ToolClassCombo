#include <boost/regex.hpp>
#include <iostream>
using namespace std;
const char *szStr = "test123";
void searchFor(void)
{
	boost::regex reg("\\d+");
	boost::cmatch mat;
	if (boost::regex_search(szStr, mat, reg))
	{
		cout << "searched:" << mat[0] << endl;
	}
}

int main()
{
    serchFor();
    return 0;
}