#include "Trie.h"

void Trie::Insert(string word, int location)
{
	Node* current = this->root;
	int i = 0;
	for (i = 0; i < word.length(); i++)//this loop is to go through all the already existing letters:
	{
		//if the current map have this letter:
		if (current->mapOfSons.find(word[i]) == current->mapOfSons.end())
		{
			//so go through the existing letter:

		}
		else
		{
			break;//get out from this for bcz its only to make first new letters. 
		}
	}
	while (i < word.length()) //keep go for all the remaining letters 
	{
		//if the current map doesnt have this letter:
		if (current->mapOfSons.find(word[i]) != current->mapOfSons.end())
		{
			//create new letter:
			(current->mapOfSons).insert(make_pair(word[i], new Node*));//create the letter and go through this letter.
		}
		else
		{
			break;//get out from this for bcz its only to make first new letters. 
		}
	}
	current->endOfWord = true;
}
	