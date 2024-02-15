#pragma once
#include "Trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Book {
private:
    string content;
    Trie trie;
    void processContent();

public:
    Book(const string& filepath);
    string extractSentence(int location);
    void searchAndPrint(const string& query);
    void censorQuery(const string& query);

};
