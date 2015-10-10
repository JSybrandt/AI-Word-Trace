#pragma once
#include <string>
#include <vector>
#include "Dictionary.h"

using std::string;
using std::vector;

enum SearchType{
	HEURISTIC,
	DIST_PLUS_HEURISTIC
};

template <SearchType TYPE>
class WordNode{

public:

	WordNode(string val, string dest, WordNode<TYPE> * parent=nullptr){
		data = val;
		goalWord = dest;
		heuristicValue = Dictionary::editDistance(data,goalWord);
		if(parent!=nullptr){
			distanceFromSource=parent->distanceFromSource+1;
			this->chain = parent->chain;
		}
		else
			distanceFromSource=0;
		this->chain.push_back(data);
	}

	WordNode(const WordNode& copy){
		this->data = copy.data;
		this->goalWord = copy.goalWord;
		this->distanceFromSource = copy.distanceFromSource;
		this->heuristicValue = copy.heuristicValue;
		this->chain = copy.chain;
	}

	string getString(){return data;}

	//get/set the numer of edits from the source word
	unsigned int getDistanceFromSource(){return distanceFromSource;}

	//gets the edit distance to the goal word
	unsigned int getHeuristicValue(){return heuristicValue;}

	unsigned int getSearchValue() const {
		switch (TYPE)
		{
		case HEURISTIC: return heuristicValue;
		case DIST_PLUS_HEURISTIC: return distanceFromSource+heuristicValue;
		}
	}

	//used in priority queue note, a word is "greater" if it has a lower value
	bool operator<(const WordNode& other) const{
		return this->getSearchValue() > other.getSearchValue();
	}

	//returns all of the strings in the word chain
	vector<string> getChain(){return chain;}
	

private:
	string data, goalWord;
	unsigned int distanceFromSource;
	unsigned int heuristicValue;
	vector<string> chain;



};