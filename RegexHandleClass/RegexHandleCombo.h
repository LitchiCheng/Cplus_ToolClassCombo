#include <boost/regex.hpp>
#include <string>
#include <iostream>
/*******************************************************************************************
模式							匹配的内容(含意)
字符类
[abc]							a、b 或 c（简单类）
[^abc]							任何字符，除了 a、b 或 c（否定）
[a - zA - Z]					a 到 z 或 A 到 Z，两头的字母包括在内（范围）
[a - d[m - p]]					a 到 d 或 m 到 p：[a - dm - p]（并集）
[a - z && [def]]				d、e 或 f（交集）
[a - z && [^bc]]				a 到 z，除了 b 和 c：[ad - z]（减去）
[a - z && [^m - p]]				a 到 z，而非 m 到 p：[a - lq - z]（减去）

预定义字符类
.								任何字符（与行结束符可能匹配也可能不匹配）
\d								数字：[0 - 9]
\D								非数字： [^ 0 - 9]
\s								空白字符：[\t\n\x0B\f\r]
\S								非空白字符：[^\s]
\w								单词字符：[a - zA - Z_0 - 9]
\W								非单词字符：[^\w]

边界匹配器
^								行的开头
$								行的结尾
\b								单词边界
\B								非单词边界
\A								输入的开头
\G								上一个匹配的结尾
\Z								输入的结尾，仅用于最后的结束符（如果有的话）
\z								输入的结尾

数量词(Greedy策略)
X ?								X，一次或一次也没有
X*								X，零次或多次
X +								X，一次或多次
X{ n }							X，恰好 n 次
X{ n, }							X，至少 n 次
X{ n,m }						X，至少 n 次，但是不超过 m 次

逻辑运算符
XY								X 后跟 Y
X | Y							X 或 Y
(X)								X，作为捕获组
********************************************************************************************/
class RegexHandleClass
{
public:
	RegexHandleClass(const std::string regular_express):m_match_express(regular_express){}
	~RegexHandleClass(){}
	int isPartIn(const char* szStr, const std::string regular_express);
	int isPartIn(const char* szStr);
private:
	std::string m_match_express;
};

int RegexHandleClass::isPartIn(const char* szStr,const std::string regular_express)
{
	boost::regex reg(regular_express);
	boost::cmatch mat;
	if (boost::regex_search(szStr, mat, reg))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int RegexHandleClass::isPartIn(const char* szStr)
{
	boost::regex reg(m_match_express);
	boost::cmatch mat;
	if (boost::regex_search(szStr, mat, reg))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}