#pragma once
#include "Node.h"
class Trie
{
public:
	Node* root;

	Trie();
	~Trie();

	void Insert(string word, int location);
	void deleteaAll(Node*);// help recursive function to Dtor

	list<int> search(string strToSearch);

	//2 help function to search
	Node* searchNode(string strToSearch);
	list<int> preOrder(Node* root);


};

