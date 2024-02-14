#pragma once
#include "Node.h"
class Trie
{
public:
	Node* root;

	Trie();
	void Insert(string word, int location);
	~Trie();
};

