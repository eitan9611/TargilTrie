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
	list<int> locationslist;
	int counter = 0, numOfVisit = 1;
	Node* found = searchNode(strToSearch);

	//if found isn't null - get 3 words from the subtree of the node we found using preOrder.
	if (found)
	{
		locationslist = preOrder(found, locationslist, counter, numOfVisit);
		cout << "The search required visiting " << numOfVisit << " nodes." << endl;
		return locationslist;
	}
	else// else return empty list (mark we didn't found)
		return locationslist;// empty list
	
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
	return i ? current : nullptr;
}

list<int> Trie::preOrder(Node* root, list<int>& locationsList, int& numOfWords, int& numOfNodesVisit)
{
	if (root == nullptr) return locationsList;

	//if we got to Node that is end of word
	if (root->endOfWord)
	{
		//add all the locations of this node to our locations list
		locationsList.insert(locationsList.end(), root->startsOfWords.begin(), root->startsOfWords.end());
		numOfWords++;
	}
	
	//ran over his sons in pre order
	map <char, Node*> myMap = root->mapOfSons;
	for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
		if (numOfWords == 3) break;

		preOrder(it->second, locationsList, numOfWords, ++numOfNodesVisit);
	}
	return locationsList;
}

	