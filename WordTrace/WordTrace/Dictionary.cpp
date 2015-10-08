#include "Dictionary.h"


Dictionary::Dictionary(){
	fstream fin(PATH_TO_WORD_LIST,ios::in);

	if(!fin)throw SOURCE_NOT_FOUND();
	string tmp;
	while(fin)
	{
		fin>>tmp;
		wordList.insert(sToLower(tmp));
	}
	fin.close();
}
	
unsigned int Dictionary::size() const{
	return wordList.size();
}

vector<string> Dictionary::getRelatedWords(string const& s) const{

	string query = sToLower(s);

	//number of possible 1 edit strings are #subs + #adds + #subtracts
	unsigned long numGendStrings = pow(25,query.length()) + pow(25,query.length()+1) + query.length();

	//if the dictonary is longer than the gened frontier
	if(size() >= numGendStrings){
		return generateRelatedWords(query);
	}
	else{//if the dictonary is shorter than the number of gened strings
		return scanDictForRelatedWords(query);
	}
}

vector<string> Dictionary::scanDictForRelatedWords(string const& s) const{
	vector<string> res;
	for(string word : wordList){
		if(editDistance(s,word)==1){
			res.push_back(word);
		}
	}
	return res;
}
vector<string> Dictionary::generateRelatedWords(string const& s) const{
	vector<string> res;

	//try all inserts
	for(int i = 0 ; i <= s.length();i++){
		for(char c='a';c<='z';c++){
			string cpy(s);
			cpy.insert(i,1,c);
			if(this->contains(cpy))
				res.push_back(cpy);
		}
	}

	//try all substitutions
	for(int i = 0 ; i < s.length();i++){
		for(char c='a';c<='z';c++){
			if(c!=s[i]){
				string cpy(s);
				cpy[i]=c;
				if(this->contains(cpy))
					res.push_back(cpy);
			}
		}
	}

	//try all deletions
	for(int i = 0; i< s.length(); i++)
	{
		string cpy(s);
		cpy.erase(i,1);
		if(this->contains(cpy))
			res.push_back(cpy);
	}
	return res;
}

bool Dictionary::contains(string const & s) const{
	return (wordList.count(s)>0);
}

unsigned int Dictionary::editDistance(const std::string& s1, const std::string& s2)
{
	//Create a |s1|+1 by |s2|+1 2d array
	unsigned int ** data = new unsigned int*[s1.length()+1];
	for(int i=0; i<=s1.length();i++)
		data[i]=new unsigned int[s2.length()+1];

	//populate with 0's
	for(int i=0; i<=s1.length();i++)
		for(int j=0; j<=s2.length(); j++)
			data[i][j]=0;

	//fill with data
	for(int i=0; i<=s1.length();i++)
		for(int j=0; j<=s2.length();j++)
		{
			//if we are starting from the null string (n insertions)
			if(min(i,j)==0){
				data[i][j]=max(i,j);
			}else{
				//if the two characters are the same
				if(s1[i-1]==s2[j-1]){
					data[i][j]=data[i-1][j-1];
				}else{
					int insertionCost = data[i][j-1]+1;
					int subtractionCost = data[i-1][j]+1;
					int substitutionCost = data[i-1][j-1]+1;
					//new cost is the smallest cost to make this substring
					data[i][j]=min(min(insertionCost,subtractionCost),substitutionCost);
				}
			}
		}

	unsigned int ret = data[s1.length()][s2.length()];
	for(int i = 0 ; i <= s1.length();i++)
	{
		delete [] data[i];
	}
	delete data;
	return ret;
}

string Dictionary::sToLower(string s){
	for(char &c:s)c=tolower(c);
	return s;
}