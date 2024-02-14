#include <iostream>
#include "Book.h"
#include "Node.h"
#include "Trie.h"
#include <list>
using namespace std;

int main() {
    //string prefix, command, path;
    //cout << "Enter the book's path: ";
    //getline(cin, path); // Read entire line as input
    //Book book(path);

    //while (true) {
    //    cout << "Enter 's' to search, 'c' to censor or 'e' to quit: ";
    //    getline(cin, command); // Read entire line as input

    //    if (command == "e") {
    //        break;
    //    }
    //    if (command == "s") {
    //        cout << "Enter prefix:" << endl;
    //        getline(cin, prefix); // Read entire line as input
    //        book.searchAndPrint(prefix);
    //    }
    //    if (command == "c") {
    //        cout << "Enter search term to censor:" << endl;
    //        getline(cin, prefix); // Read entire line as input
    //        book.censorQuery(prefix);
    //    }
    //}
    map<char, Node*> myMap;
    list <int> a;
    Node b(false,a,myMap);
    Node* c = &b;
    Trie k;
 
    k.Insert("stom", 7);
    k.Insert("stom", 12);
    k.Insert("satum", 8);
    k.Insert("stok", 5);

    list<int> loc = k.search("st");

    for (list<int>::iterator it = loc.begin(); it != loc.end(); it++)
        cout << *it << " ";

    return 0;
}