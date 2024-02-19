#include "Book.h"
#include <algorithm>
#include <string>
#include <regex>
#include <list>

using namespace std;

Book::Book(const string& filepath) {
    // Open the file at the specified filepath
    ifstream file(filepath);

    // Check if the file is successfully opened
    if (file.is_open()) {
        // Read the entire content of the file into a stringstream
        stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        file.close();

        // Transform the content to lowercase
        transform(content.begin(), content.end(), content.begin(), ::tolower);

        // Replace consecutive whitespaces with a single space using regular expressions
        regex pattern("\\s+"); // Matches one or more whitespace characters
        content = regex_replace(content, pattern, " ");

        // Insert content into the trie
        processContent();
    }
    else {
        // If the file fails to open, throw an exception
        throw invalid_argument("Unable to open file");
    }
}

void Book::processContent() {

    istringstream iss(content);//treat the string 'content' as a stream (to be able to use it in the "getline" method.)
    string sentenceToTrie="";
    string word,removeString="",firstWord="";
    int counterToThree = 0;
    int place = 0,i,lengthOfFirstWord=0;
    //save start of words.

    for (i = 0; i < 3; i++)
    {
        getline(iss, word, ' ');
        if (i == 0)
        {
            firstWord = word;  //"one"
        }
        else
            sentenceToTrie += " "; //add spaces start from the second word

        sentenceToTrie += word;

    }
    trie.Insert(sentenceToTrie, 0);
    int newLocation = firstWord.length() + 1;//length+space.
    while (getline(iss, word, ' '))
    {
        sentenceToTrie = sentenceToTrie.substr(firstWord.length()+1, sentenceToTrie.length());//remove the first word from sentenceToTrie. DesignString.substr(startPos,lengthToStay)
        lengthOfFirstWord = sentenceToTrie.find(' ');//find length of current first word 
        firstWord = sentenceToTrie.substr(0,lengthOfFirstWord);//saves the firstWord for next rotation.
        sentenceToTrie += " ";
        sentenceToTrie += word;
        trie.Insert(sentenceToTrie, newLocation);
        newLocation += firstWord.length() + 1;
    }
    return;
}


void Book::searchAndPrint(const string& query) {
    // TODO: Use the trie to find the locations of the string (At most 3 sentences)
    // TODO: For each location, use the extractSentence function to extract the sentence in that location
    // TODO: Print each sentence

    list<int> locations = trie.search(query);
    if (locations.empty()) {
        cout << "No results" << endl;
        return;
    }
    cout << "Sentences matching the prefix:" << endl;
    int i = 0;
    for (int locate : locations)
    {
        cout << extractSentence(locate) << endl;
        i++;
        if (i == 3)
            break;
    };
}

/*
This function gets location in book and print the sentence that contain it.

*/
string Book::extractSentence(int location) {

    //treat the string 'content' as a stream (to be able to use it in the "getline" method.)
    istringstream iss(content);

    int numOfWords = 0;
    string bWwords[5], sentence = "", word;

    //run backward over the characters in the string until we take 5 words or got to point.
    for (int i = location-1; i>=0 && numOfWords != 5; i--)
    {
        if (content[i] == '.')//we reached to end of sentence
            break;
        if ((i && content[i-1] == ' ')||(i==0)) //we reached to end of word
        {
            iss.seekg(i);// skipping the first 'i' characters. needed because we moving backwards
            
            //try get the word 
            getline(iss, word, ' ');

            if(word != "")//if we extract something - insert it to our array
                bWwords[numOfWords++] = word;
        }
    }

    //if we didnt got to point its mean we in middle of sentence 
    if (numOfWords == 5)
        sentence += "...";

    //insert the words we collected to the full sentence 
    for (int i = numOfWords; i > 0; i--)
        sentence += bWwords[i-1] + " ";

    //mark we got to our location
    sentence += "*";

    // Set the internal string buffer of iss starting from our specific position
    iss.seekg(location);

    //run forward over the characters in the string until we take 5 words or got to point.
    while (getline(iss, word, ' '))
    {
        sentence += word + " "; //add the word to the complete sentence

        if (word.find('.') != string::npos || ++numOfWords == 10) //if the word include the char '.' or we reached 10 words - stop extracting words
            break;
    }

    //sentence.pop_back();//delete the last space

    //if we got to 10 words its mean we in middle of sentence (didn't find point)
    if (numOfWords == 10)
        sentence += "...";

    return sentence;
}

void Book::censorQuery(const string& query) {
    trie.deleteWord(query);
}