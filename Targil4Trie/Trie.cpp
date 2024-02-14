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
		(current->mapOfSons).insert(make_pair(word[i], new Node));//create the letter and go through this letter.
		auto x = current->mapOfSons.find(word[i]);
		current = x->second;
		i++;
	}
	current->endOfWord = true;
	current->startsOfWords.push_back(location);//assign another time that this word is being shown in the book  
}

	