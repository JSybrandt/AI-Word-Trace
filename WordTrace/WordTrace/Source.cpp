#include <iostream>

#include "Dictionary.h"

using namespace std;

int main(){

	Dictionary englishDict;
	/*
	do {
		string s1, s2;
		cout<<"Enter two strings:";
		cin>>s1>>s2;
		cout<<"Edit Distance:" <<Dictionary::editDistance(s1,s2)<<endl;
	} while(cin);
	return 0;
	*/
	do
	{
		cout<<"Please Enter a Word:";
		string tmp;
		cin>>tmp;

		if(englishDict.contains(tmp)){

			cout<<"All Words within edit distance 1:"<<endl;
			for(string s : englishDict.getRelatedWords(tmp))
			{
				cout<<"\t"<<s<<endl;
			}
		}
		else
		{
			cout<<"Please enter an english word."<<endl;
		}
	}while(cin);
	
}