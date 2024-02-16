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
    istringstream stream(content);

    istringstream iss(content);//treat the string 'content' as a stream (to be able to use it in the "getline" method.)
    string sentenceToTrie="";
    string word,removeString="",firstWord="";
    int counterToThree = 0;
    int place = 0,i,lengthOfFirstWord=0;
    //save start of words.

    for (i = 0; i < 3; i++)
    {
        getline(iss, word, ' ');
        sentenceToTrie += word;
        sentenceToTrie += " ";
        if (i == 0)
        {
            firstWord = word;  //"one"
        }
    }
    cout << sentenceToTrie << 0 << endl;
    trie.Insert(sentenceToTrie, 0);
    int newLocation = firstWord.length() + 1;//length+space.
    while (getline(iss, word, ' '))
    {
        sentenceToTrie = sentenceToTrie.substr(firstWord.length()+1, sentenceToTrie.length());//remove the first word from sentenceToTrie. DesignString.substr(startPos,lengthToStay)
        lengthOfFirstWord = sentenceToTrie.find(' ');//find length of current first word 
        firstWord = sentenceToTrie.substr(0,lengthOfFirstWord);//saves the firstWord for next rotation.
        sentenceToTrie += word;
        sentenceToTrie += " ";
        cout << sentenceToTrie << newLocation << endl;
        trie.Insert(sentenceToTrie, newLocation);
        newLocation += firstWord.length() + 1;
    }
    return;
}


void Book::searchAndPrint(const string& query) {
    // TODO: Use the trie to find the locations of the string (At most 3 sentences)
    // TODO: For each location, use the extractSentence function to extract the sentence in that location
    // TODO: Print each sentence
    list<int> locations; // TODO: fix
    if (locations.empty()) {
        cout << "No results" << endl;
        return;
    }
    cout << "Sentences matching the prefix:" << endl;

}

string Book::extractSentence(int location) {
    // TODO: Go over the characters of the content from the location backwards until finding a '.' or until accumulating 5 words.
    // TODO: Go over the characters of the content from the location forwards until finding a '.' or until accumulating a total of 10 words.
    // TODO: Assemble the sentence by adding the two parts with a '*' marker for the location and '...' if the sentence was cut.
    return nullptr;
}

void Book::censorQuery(const string& query) {
    //TODO: remove the query from the trie (mark it as a non end-of-word)
}