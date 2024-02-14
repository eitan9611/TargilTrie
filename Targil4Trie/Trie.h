#pragma once
#include "Node.h"
class Trie
{
public:
	Node* root;

	Trie(Node* _root);
	void Insert(string word, int location);
	~Trie();
};

