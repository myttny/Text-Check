#include "test.hpp"
#include "cppjieba/Jieba.hpp"
using namespace std;

void Word_vector(string file, Figures& figs, cppjieba::Jieba& jieba)
{
	figs.GetStopWord(STOP_WORD_PATH);
	vector<string> vec, newvec;
	vec = figs.Readword(file);
	for (int i = 0; i < vec.size(); ++i)
	{
		jieba.Cut(figs.GBKToUTF8(vec[i]), newvec, true);
		figs.VecToMap(newvec);
	}
	figs.Sort_N();
}

double Test(string file1, string file2)
{
	cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
	Figures figs1, figs2;
	Word_vector(file1, figs1, jieba);
	Word_vector(file2, figs2, jieba);
	figs1.Word_Set(figs1.Get_set(), figs2.Get_set());
	vector<int> vec1 = figs1.Vector_word(figs1.Get_set(), figs1.Get_map());
	vector<int> vec2 = figs2.Vector_word(figs1.Get_set(), figs2.Get_map());
	return figs1.cosine(vec1, vec2);
}

int main() {
	string file1, file2;
	cin >> file1 >> file2;
	cout << Test(file1, file2) * 100 << '%' << endl;
	system("pause");
	return 0;
}
