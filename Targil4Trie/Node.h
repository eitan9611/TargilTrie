#pragma once
#include <iostream>
#include <list>
#include <map>
using namespace std;
class Node
{
public:
	bool endOfWord;
	list<int> startsOfWords;
	map <char, Node*> mapOfSons; //the char will contain the letter and the node will conation pointer to this letter.
	Node(bool a, list <int> b, map<char, Node*> c) :endOfWord(a), startsOfWords(b), mapOfSons(c) {}
	Node() { };
};