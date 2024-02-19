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



/// this is wrapping funciton thats send the root to the recursive function.

void Trie::deleteWord(string word)
{
	deleteWordRecursive(word, root);
}

bool Trie::deleteWordRecursive(string word, Node* root)
{
	//if we reached to the end of the word and the trie indeed contain this word - return true. 
	if (word.empty())
	{
		if (root->endOfWord)
		{
			root->endOfWord = false;//mark we delete the word

			if (root->mapOfSons.empty())//if this node is a leaf
			{
				//delete it 
				delete root;
				root = nullptr;
				return true;
			}
		}
		return false;//mark we didn't find the word
	}

	bool deleteSucceed;
	auto next = root->mapOfSons.find(word[0]);
	if (next != root->mapOfSons.end())// if we found the specifc letter in the map 
	{
		deleteSucceed = deleteWordRecursive(word.substr(1, word.length() - 1), next->second); //send again to the recursive function without the first letter of word
		if (deleteSucceed)
		{
			root->mapOfSons.erase(word[0]); //delete the tuple that contain the node we deleted
			
			if (root->mapOfSons.empty())//if there is no other sons
			{
				//delete the current node
				delete root;
				root = nullptr;
				return true;
			}
		}
	}
	return false;// mark we didn't delete the current node
}

list<int> Trie::search(string strToSearch)
{
	list<int> locationslist;
	int counter = 0, numOfVisit = 1;//strToSearch.length();//initalize number of nodes in the amount of characters in the str
	Node* found = searchNode(strToSearch, numOfVisit);

	//if found isn't null - get 3 words from the subtree of the node we found using preOrder.
	if (found)
		locationslist = preOrder(found, locationslist, numOfVisit);

	// else return empty list (mark we didn't found)
	
	cout << "The search required visiting " << numOfVisit << " nodes." << endl;
	return locationslist;
	
}

/// <summary>
/// This function go through word in the trie and return the last node of the word (if exist)
/// </summary>
Node* Trie::searchNode(string strToSearch, int& numOfNodesVisit)
{
	Node* current = this->root;
	int i;

	for (i = 0; i < strToSearch.length(); i++)//this loop is to go through all the letters:
	{
		//if the current map have this letter:
		if (current->mapOfSons.find(strToSearch[i]) != current->mapOfSons.end())
		{
			numOfNodesVisit++;//count in how many nodes we visited
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

list<int> Trie::preOrder(Node* root, list<int>& locationsList, int& numOfNodesVisit)
{
	int locationsToAdd = 3 - locationsList.size(); //calculate how many locations missing to reach to 3
	if (root == nullptr) return locationsList;

	//if we got to Node that is end of word
	if (root->endOfWord)
	{
		//if we still didn't collect 3 locations:
		if(locationsToAdd > 0)
			copy_n(root->startsOfWords.begin(), locationsToAdd, back_inserter(locationsList)); //add as many avaliable locations of this node to our locations list
	}
	
	//ran over his sons in pre order
	map <char, Node*> myMap = root->mapOfSons;
	for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
		if (locationsList.size() == 3) break;
		preOrder(it->second, locationsList, ++numOfNodesVisit);
	}
	return locationsList;
}

	