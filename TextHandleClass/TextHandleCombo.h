#include "stdafx.h"
#include <fstream>// std::ifstream
#include <iostream>// std::wcout
#include <vector>
#include <string>
using std::vector;
using std::wstring;

class ReadTextToVector
{
public:
	ReadTextToVector() {}
	~ReadTextToVector();
	int readToVector(vector<wstring> &data, wstring szFile, int line_size);
	int readToVector(wstring szFile, int line_size);
	int showOneByOneOfVector(int end_line_number);
	int returnTextLineNumber(vector<wstring> &data);
	int returnTextLineNumber();
private:
	vector<wstring> m_result;
	wchar_t *strbuf;
};

ReadTextToVector::~ReadTextToVector()
{
	delete[]strbuf;
}

int ReadTextToVector:: readToVector(vector<wstring> &data, wstring szFile,int line_size)
{
	data.clear();
	std::wifstream file_(szFile.c_str(), std::ios::in);
	strbuf = new wchar_t[line_size];
	while (!file_.eof())
	{
		file_.getline(strbuf, line_size);
		wstring sentence = strbuf;
		if (sentence.empty())
		{
			continue;
		}
		data.push_back(sentence);
	}
	file_.close();
	if (data.size() < 1)
	{
		return -1;
	}
	return 0;
}

int ReadTextToVector::readToVector(wstring szFile, int line_size)
{
	m_result.clear();
	std::wifstream file_(szFile.c_str(), std::ios::in);
	strbuf = new wchar_t[line_size];
	while (!file_.eof())
	{
		file_.getline(strbuf, line_size);
		wstring sentence = strbuf;
		if (sentence.empty())
		{
			continue;
		}
		m_result.push_back(sentence);
	}
	file_.close();
	if (m_result.size() < 1)
	{
		return -1;
	}
	return 0;
}

int ReadTextToVector::showOneByOneOfVector(int end_line_number)
{
	if (m_result.size() > 0 && m_result.size() >= end_line_number)
	{
		for (int i = 0; i < end_line_number; ++i)
		{
			std::wcout << m_result[i] << std::endl;
		}
	}
	else 
	{
		std::cout << "Now vector has't got excepted number of data." << std::endl;
		return -1;
	}
	return 0;
}

int ReadTextToVector::returnTextLineNumber(vector<wstring> &data)
{
	return data.size();
}

int ReadTextToVector::returnTextLineNumber()
{
	return m_result.size();
}
class TextHandleTool
{
public:
	TextHandleTool() {}
	~TextHandleTool() {}
	bool isPartIn(const char* string_raw, const char* string_match, int size);
private:

};

bool TextHandleTool::isPartIn(const char* string_raw, const char* string_match, int size)
{
	std::string string_convert;
	string_convert.assign(string_raw, size);
	if (string_convert.find(string_match) != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}