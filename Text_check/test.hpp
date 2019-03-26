#pragma once
#include<cppjieba/jieba.hpp>
#include<windows.h>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<unordered_set>
#include<string>
#include<vector>
#include<map>
#include<set>
const int MAX_WORD = 10;

const char* const DICT_PATH = "dict/jieba.dict.utf8";
const char* const HMM_PATH = "dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "dict/user.dict.utf8";
const char* const IDF_PATH = "dict/idf.utf8";
const char* const STOP_WORD_PATH = "dict/stop_words.utf8";

class Figures
{
public:
	std::string GBKToUTF8(std::string& str);
	std::string UTF8ToGBK(std::string& str);
	std::vector<std::string> Readword(const std::string file);
	void VecToMap(const std::vector<std::string>& newvec);
	void Sort_N();
	void GetStopWord(const char* file);
	std::set<std::string> Get_set()
	{
		return sset;
	}
	std::map<std::string, int> Get_map()
	{
		return mmap;
	}
	void Word_Set(std::set<std::string>& set1, const std::set<std::string>& set2);
	std::vector<int> Vector_word(const std::set<std::string>& set, const std::map<std::string, int>& map);
	double cosine(const std::vector<int>& vec1, const std::vector<int>& vec2);
private:
	std::unordered_set<std::string> stopword;
	std::map<std::string, int> mmap;
	std::set<std::string> sset;
};
