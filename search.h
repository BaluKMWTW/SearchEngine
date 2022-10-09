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
#pragma once
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
bool no_alph(string);
void banWebsite(set<string>&, string);
//delete non-alphabetical chars from the beggining and the end of the string
//delete all punc from the beggining and the end by reversing strings orded
//copy everything in between (if uppercase -> switch to lowercase using ASCII)
string cleanToken(string s) {
    if(no_alph(s))
        return "";
    string x;
    bool start_flag = true;
    for(u_int i = 0; i < s.size(); i++) {
        if( start_flag && !isalpha(s[i]) && !isdigit(s[i])) {
            continue;
        }else{
            start_flag = false;
        }
        if( i == s.size() - 1 && !isalpha(s[i]) && !isdigit(s[i])) {
            continue;
        }
        if(isupper(s[i])) {
            char c = s[i] + 32;
            x += c;
        }else if(isalpha(s[i]) || ispunct(s[i]) || isdigit(s[i]) ||isspace(s[i])){
            x += s[i];
        }
    } 
    string y;
    bool end_flag = true;
    for(int i = x.size() -1; i >= 0; i--) {
        if( end_flag && !isalpha(x[i]) && !isdigit(s[i])) {
            continue;
        }else{
            end_flag = false;
        }
        y += x[i];
    }
    string z;
    for(int i = y.size() -1; i >= 0; i--) {
        z += y[i];
    }

    return z;  
}
// create a set of unique tokens from the given string
// I used stringstream object that gets inserted when the conditions are met
set<string> gatherTokens(string text) {
    set<string> tokens;
    stringstream ss(text);
    string tmp;
    while(ss >> tmp) {
        
        if(tmp == "")
            continue;
        string x;
        x = cleanToken(tmp);
       
        if(tokens.find(x) == tokens.end()) {
            
            if(x != ""){
                tokens.insert(x);
                
            }
           
        }
    }
    return tokens;
}

// count the nummber of processed urls
// map each word with set of urls that contain this word
int buildIndex(string filename, map<string, set<string>>& index) {
    int count = 0;
    fstream fs(filename);
    string tmp;
    int i = 0;
    string url_tmp;
    while(getline(fs, tmp)) {
        i++;
        if(i % 2 != 0) {
            url_tmp = tmp;
            count ++;
        }
        if(i % 2 == 0) {
            set<string> tokens = gatherTokens(tmp);
            for(auto& e: tokens) {
                
                if(tokens.size() != 0){
                    index[e].insert(url_tmp);
                }
                
               
            }
        }   
        
    }
    return count;
}
// get set of url for each word of sentence and perform adequate operation:
// 1st char is + => AND
// 1st char is - => SUBTRACT
// else  => OR
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    set<string> keys;
    stringstream ss(sentence);
    string tmp;
    set<string> plus;
    set<string> minus; 
    //perform AND operation when + in front, OR when nothing in front, subtract when - in front,  
    while(ss >> tmp) {
        if(tmp[0] == '+') {
            for(auto& e : result) {
                if(index[tmp.substr(1)].find(e) == index[tmp.substr(1)].end()) {
                    result.erase(e);
                }
            } 
        } else if(tmp[0] == '-') {
            for(auto& e : result) {
                if(index[tmp.substr(1)].find(e) != index[tmp.substr(1)].end()) {
                    result.erase(e);
                }
            } 
        } else {
            for(auto& e : index) {
                if(tmp == e.first){
                    for(auto& f : e.second) {
                        result.insert(f);
                    }
                }
            }
        }
    }
    return result;
}
// search the filed named filename for matches made by findQueryMatches function and print them out
// also, print out the number of pages in the file and the number unique terms in the file
// od so as long as the query sentece doesn't become an empty string
void searchEngine(string filename) {
    cout << "Stand by while building index..." << endl;
    map<string,set<string>> index;
    int index_count = 0;
    index_count = buildIndex(filename, index);
    cout << "Indexed " << index_count <<" pages containing " << index.size() << " unique terms" << endl;
    string input;
    cout << "Enter query sentence (press enter to quit):" << endl;
    set<string> store_result; //used for creative component to store result from previous search
    getline(cin, input);

    while(input != "") {
    if(input == "") {
        return;
    }else {
        set<string> result;
        result = findQueryMatches(index, input);
        if(input.substr(0,3) == "ban") { //creative component
            result.clear();
            string name = input.substr(4);
            for(auto& e : store_result) {
                if(e.find(name) != std::string::npos) {
                    store_result.erase(e);
                }
            }
            result = store_result;
        }
        cout << "Found " << result.size() << " matching pages" << endl;
        for(auto& e : result) {
            cout << e << endl;  
        }
        store_result.clear( );
        store_result = result;
    }
        cout << "Enter query sentence (press enter to quit):" << endl;
        getline(cin, input);
    }   
}
// check if string contains any letters
bool no_alph(string s) {
    for(auto& e: s){
        if(isalpha(e)){
            return false;
        }
            
    }
    return true;
}