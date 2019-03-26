#include "test.hpp"
#include<cstdlib>
#include<functional>
using namespace std;

string Figures::GBKToUTF8(string& str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* utf8char = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8char, len, NULL, NULL);
	string out(utf8char);
	if (wstr)
	{
		delete[] wstr;
		wstr = NULL;
	}
	if (utf8char)
	{
		delete[] utf8char;
		wstr = NULL;
	}
	return out;
}

string Figures::UTF8ToGBK(string& str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* utf8char = new char[len];
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, utf8char, len, NULL, NULL);
	string out(utf8char);
	if (wstr)
	{
		delete[] wstr;
		wstr = NULL;
	}
	if (utf8char)
	{
		delete[] utf8char;
		wstr = NULL;
	}
	return out;
}

vector<string> Figures::Readword(const string file)
{
	vector<string> vec;
	string line;
	ifstream fin(file);
	if (!fin.is_open())
	{
		cout << "open file: " << file << "failed" << endl;
		exit(-1);
	}
	while (!fin.eof())
	{
		getline(fin, line);
		vec.push_back(line);
	}
	return vec;
}

void Figures::VecToMap(const vector<string>& newvec)
{
	for (int i = 0; i < newvec.size(); ++i)
	{
		if (stopword.count(newvec[i]) > 0)
			continue;
		if (mmap.count(newvec[i]))
			mmap[newvec[i]]++;
		else
			mmap[newvec[i]] = 1;
	}
}

void Figures::GetStopWord(const char* file)
{
	ifstream fin(file);
	if (!fin.is_open())
	{
		cout << "open files" << file << "file" << endl;
		exit(-1);
	}
	string line;
	while (!fin.eof())
	{
		getline(fin, line);
		stopword.insert(line);
	}
	fin.close();
}

void Figures::Sort_N()
{
	int count = 0;
	vector<pair<int, string>> vec;
	for (auto it = mmap.begin(); it != mmap.end(); ++it)
	{
		vec.push_back(make_pair(it->second, it->first));
	}
	sort(vec.begin(), vec.end());

	for (int i = vec.size() - 1; i >= 0 && count < MAX_WORD; --i)
	{
		sset.insert(vec[i].second);
		count++;
	}
}

vector<int> Figures::Vector_word(const std::set<std::string>& set, const std::map<std::string, int>& map)
{
	vector<int> vec;
	for (auto it = set.begin(); it != set.end(); ++it)
	{
		auto pos = map.find(*it);
		if (pos != map.end())
			vec.push_back(pos->second);
		else
			vec.push_back(0);
	}
	return vec;
}

void Figures::Word_Set(set<string>& set1, const set<string>& set2)
{
	for (auto it = set2.begin(); it != set2.end(); ++it)
	{
		set1.insert(*it);
	}
}

double Figures::cosine(const vector<int>& vec1, const vector<int>& vec2)
{
	volatile int products = 0;
	volatile int trnum1 = 0;
	volatile int trnum2 = 0;
	for (int i = 0; i < vec1.size(); ++i)
	{
		products += vec1[i] * vec2[i];
	}
	for (int i = 0; i < vec1.size(); ++i)
	{
		trnum1 += pow(vec1[i], 2);
	}
	for (int i = 0; i < vec2.size(); ++i)
	{
		trnum2 += pow(vec2[i], 2);
	}
	return products / sqrt(trnum1 * trnum2);
}
