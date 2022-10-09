// Jan Komorowski CS251 UIC Fall 2022
// Project 2: Search Engine
// program opens one of the given files (cplusplus.txt, stackoverflow.txt, tiny.txt, uiccs-news.txt, wiki-uni.txt)
// then takes a Query Sentence from the user that searches for given terms
// + in front of the word means that only the results that contain this word will be shown
// - in front of the word means that all previous results that don't contain this word will be shown
// no special character in front of the word means that all previous results will be show along with the ones for this word (no duplicates)
// CREATIVE COMPONENT : ban a website
// after inputing command "ban x" the results will be modified, so there will be no urls matching the name of the given website (x)
// simple test: for tiny.txt input "fish", then input "ban shoppinglist"
#include <iostream>
#include "search.h"
using namespace std;
int main() {
    string filename = "tiny.txt";
    searchEngine(filename);
    return 0;
    //TESTS:    
    // cleanTokens()
    // string s = "_.123h.e.l.l.o.&3";
    // cout << cleanTokens() << endl;

    // gatherTokens()
    // fstream fs(filename)
    // string url;
    // string words;
    // getline(fs, url);
    // getline(fs, words);
    // set<string> tokens;
    // tokens = gatherTokens(words);
    // // for(auto& e : tokens) {
    //     cout << e << endl;
    // }

    // buildIndex()
    // map<string, set<string>> index;
    // int index_count = 0;
    // index_count = buildIndex(filename, index);
    // cout << index_count << endl;
    // for(auto& e : index) {
    //     cout << e.first << ":" << endl;
    //     for(auto& f : e.second) {
    //         cout << f << endl;
    //     }
    // }

    // findQueryMatches() for cplusplus.txt
    // string setntence = "vector";
    // string sentence = "vector +container";
    // string sewntence = "vector +container -pointer";
    // findQueryMatches(index, sentence);
}

