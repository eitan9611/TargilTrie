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

	void deleteWord(string word);
	bool deleteWordRecursive(string word, Node* root);
		
	list<int> search(string strToSearch);

	//2 help function to search
	Node* searchNode(string strToSearch, int& numOfNodesVisit);
	list<int> preOrder(Node* root, list<int>& locationsList, int& numOfNodes, int& numOfNodesVisit);


};

