//
// Created by Adrian Hwang on 2024-10-11.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

template<typename value_type>
class UnionFindSet{
public:
	std::unordered_map<value_type,std::pair<value_type,size_t>> parent_size;
	std::vector<std::vector<value_type>> similarPairs;
	UnionFindSet(std::vector<std::vector<value_type>> similarPairs_input):similarPairs(similarPairs_input){
		__construct_parent_size();
	}
	void __construct_parent_size(){
		for(auto i=similarPairs.begin();i!=similarPairs.end();i++){
			value_type previous_word="";
			for(auto j=i->begin();j!=i->end();j++){
				//the first word
				if(previous_word==""){
					//if no existing in the parent_size, set it as root, size as 1
					if(parent_size.find(*j)==parent_size.end()){
						parent_size[*j].first=*j;
						parent_size[*j].second=1;
					}
					//update previous_word
					previous_word=*j;
				}else{ //not the first word
					//if no existing in the parent_size, set parent and size
					if(parent_size.find(*j)==parent_size.end()){
						value_type root=find(previous_word);
						parent_size[*j].first=root; //directly attach to root
						parent_size[*j].second=parent_size[root].second;
					}
					//update previous_word
					previous_word=*j;
				}
			}
		}
	}
	//find the root of word_x and folding all paths(attach all children to the root)
	value_type find(value_type x){
		return x==parent_size[x].first? x: parent_size[x].first=find(parent_size[x].first);
	}

	//attach root of smaller size to root of larger size
	void heuristic_combine(value_type x, value_type y){
		//get both roots
		x=find(x);
		y=find(y);
		if(x==y) return;
		//get size
		size_t size_x=parent_size[x].second;
		size_t size_y=parent_size[y].second;

		//make sure y's size must less than x
		if(size_y>size_x) std::swap(x,y);

		//attach y to be x's child
		parent_size[y].first=x;
		parent_size[x].second=size_x+size_y;
	}
};

class SimilarSentence{
public:
	UnionFindSet<std::string> ufs;
	SimilarSentence(std::vector<std::vector<std::string>>similarPairs_input):ufs(similarPairs_input){}
	bool operator()(std::string str1, std::string str2){
		//equal strings
		if(str1==str2) return true;

		//split str into words in vectors
		std::vector<std::string> str1_words=split_str(str1);
		std::vector<std::string> str2_words=split_str(str2);

		//if different length, false
		if(str1_words.size()!=str2_words.size()) return false;

		//compare words-wise
		size_t size=str1_words.size();
		for(int i=0;i<size;i++){
			//find not similar corresponding words
			if(ufs.find(str1_words[i])!=ufs.find(str2_words[i]))return false;
		}
		//no return false, so words-wise match
		return true;
	}
	std::vector<std::string> split_str(std::string str){
		std::vector<std::string> words;
		std::string word;
		std::istringstream iss(str);
		char delimiter=' ';
		while (std::getline(iss, word, delimiter)) {
        words.push_back(word);
		}
		return words;
	}
};
#endif //UNIONFIND_H
