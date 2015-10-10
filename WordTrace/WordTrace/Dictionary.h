#pragma once
#include<fstream>
#include<string>
#include<unordered_set>
#include<vector>
#include<exception>

using std::string;
using std::fstream;
using std::ios;
using std::unordered_set;
using std::vector;
using std::exception;
using std::min;
using std::max;
using std::pow;

class SOURCE_NOT_FOUND : public exception{};

const string PATH_TO_WORD_LIST = "english.txt";

class Dictionary{
public:

	Dictionary();	
	
	unsigned int size() const;

	vector<string> getRelatedWords(string const& s) const;

	bool contains(string const & s) const;
		
	static unsigned int editDistance(const string& s1, const string& s2);
	static string sToLower(string s);

private:
	unordered_set<string> wordList;
	
	vector<string> scanDictForRelatedWords(string const& s) const;
	vector<string> generateRelatedWords(string const& s) const;
	
	

};