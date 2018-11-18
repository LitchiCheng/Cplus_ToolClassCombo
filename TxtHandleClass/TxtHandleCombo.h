#include "stdafx.h"
#include <fstream>// std::ifstream
#include <iostream>// std::wcout
#include <vector>
#include <string>
using std::vector;
using std::wstring;

class ReadTxtToVector
{
public:
	ReadTxtToVector() {}
	~ReadTxtToVector();
	int readToVector(vector<wstring> &data, wstring szFile, int line_size);
	int readToVector(wstring szFile, int line_size);
	int showOneByOneOfVector(int end_line_number);
	int returnTxtLineNumber(vector<wstring> &data);
	int returnTxtLineNumber();
private:
	vector<wstring> m_result;
	wchar_t *strbuf;
};

ReadTxtToVector::~ReadTxtToVector()
{
	delete[]strbuf;
}

int ReadTxtToVector:: readToVector(vector<wstring> &data, wstring szFile,int line_size)
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

int ReadTxtToVector::readToVector(wstring szFile, int line_size)
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

int ReadTxtToVector::showOneByOneOfVector(int end_line_number)
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

int ReadTxtToVector::returnTxtLineNumber(vector<wstring> &data)
{
	return data.size();
}

int ReadTxtToVector::returnTxtLineNumber()
{
	return m_result.size();
}