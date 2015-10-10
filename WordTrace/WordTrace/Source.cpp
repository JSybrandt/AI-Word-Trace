#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include "Dictionary.h"
#include "WordNode.h"

using namespace std;

int main(){

	Dictionary englishDict;
	
	do {

		string source, dest;
		cout<<"Enter English initial and destination strings:\n";
		cin>>source>>dest;
		source = Dictionary::sToLower(source);
		dest = Dictionary::sToLower(dest);

		if(!englishDict.contains(source)||!englishDict.contains(dest)){
			cout<<"One or both of those is not present in the dictionary.\nPlease try again.\n";
			continue;
		}

		priority_queue<WordNode<SearchType::DIST_PLUS_HEURISTIC>> pQueue;
		set<string> seenWords;

		WordNode<SearchType::DIST_PLUS_HEURISTIC> sourceNode(source,dest);

		pQueue.push(sourceNode);
		seenWords.insert(source);

		bool found = false;
		unsigned int wordsConsidered=0;
		while(!pQueue.empty()){

			WordNode<SearchType::DIST_PLUS_HEURISTIC> currNode = pQueue.top();
			pQueue.pop();
			wordsConsidered++;
			if(currNode.getString()==dest){
				cout<<"FOUND PATH:"<<endl;
				cout<<"\tDistance:"<<currNode.getDistanceFromSource()<<endl;
				cout<<"\t";
				for(string s : currNode.getChain()){
					cout<<s<<" ";
				}
				cout<<endl;
				found = true;
				break;
			}

			for(string s : englishDict.getRelatedWords(currNode.getString())){
				if(seenWords.count(s)==0){
					seenWords.insert(s);
					WordNode<SearchType::DIST_PLUS_HEURISTIC> newNode(s,dest,&currNode);
					pQueue.push(newNode);
				}
			}

		}
		if(!found) cout<<"There is no path from "<<source<<" to "<<dest<<endl;

		
		
	} while(cin);
	return 0;
	
	
}