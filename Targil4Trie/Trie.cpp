#include "Trie.h"

Trie::Trie()
{
	root = new Node();
}

void Trie::Insert(string word, int location)
{
	Node* current = this->root;
	int i = 0;
	for (i = 0; i < word.length(); i++)//this loop is to go through all the already existing letters:
	{
		//if the current map have this letter:
		if (current->mapOfSons.find(word[i]) != current->mapOfSons.end())
		{
			//so go to the existing letter:
			auto x = current->mapOfSons.find(word[i]);
			current = x->second;
		}
		else
		{
			break;//get out from this for bcz its only to make first new letters. 
		}
	}
	while (i < word.length()) //keep go for all the remaining letters 
	{
		//create new letter:
		(current->mapOfSons).insert(make_pair(word[i], new Node()));//create the letter and go through this letter.
		auto x = current->mapOfSons.find(word[i]);
		current = x->second;
		i++;
	}
	current->endOfWord = true;
	current->startsOfWords.push_back(location);//assign another time that this word is being shown in the book  
}

Trie::~Trie()
{
	//go over all the nodes in the tree and delete them
	deleteaAll(root);
}

void Trie::deleteaAll(Node* root)
{
	if (root != nullptr) //if the node isn't leaf
	{
		//for each node ran over its sons and delete it
		map <char, Node*> myMap = root->mapOfSons;
		for (auto it = myMap.begin(); it != myMap.end(); ++it)
		{
			deleteaAll(it->second);
		}
		delete root;
		root = nullptr;
	}
}

list<int> Trie::search(string strToSearch)
{
	list<int> emptyList;
	Node* found = searchNode(strToSearch);

	//if found isn't null - get 3 words from the subtree of the node we found using preOrder.
	// else return empty list (mark we didn't found)
	return found ? preOrder(found) : emptyList;
}

/// <summary>
/// This function go through word in the trie and return the last node of the word (if exist)
/// </summary>
Node* Trie::searchNode(string strToSearch)
{
	Node* current = this->root;
	int i;

	for (i = 0; i < strToSearch.length(); i++)//this loop is to go through all the letters:
	{
		//if the current map have this letter:
		if (current->mapOfSons.find(strToSearch[i]) != current->mapOfSons.end())
		{
			//so go to the existing letter:
			auto x = current->mapOfSons.find(strToSearch[i]);
			current = x->second;
		}
		else
		{
			//if the letter isn't exist - the word doesn't exist
			return nullptr;
		}
	}
	//if we got to here and i isn't 0 (the word isn't empty) return the node we found, else return null
	return i ? nullptr : current;
}

list<int> Trie::preOrder(Node* root)
{
	//go left
	//insert to the list
	// if size == 3. return
	//go right
	return list<int>();
}

	