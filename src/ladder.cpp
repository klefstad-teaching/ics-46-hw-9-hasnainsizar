#include "ladder.h"
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
{ cout << "Error: " << msg << " for words " << word1 << " and " << word2 << endl;}

bool edit_distance_within(const string& str1, const string& str2, int d)
{
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1-len2) > d) {return false;}

    vector<vector<int>> dp(len1 + 1, vector<int>(len2+1, 0));

    for (int i = 0; i <= len1; ++i)
    {
        for (int j = 0; j <= len2; ++j)
        {
            if (i==0){dp[i][j] = j;}
            else if (j==0) {dp[i][j] = i;}
            else if (str1[i-1] == str2[j-1]) {dp[i][j] = dp[i-1][j-1];}
            else dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string&  begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word)
    {
        error(begin_word, end_word, "Start and end words are SAME!");
        return {};}

    if (begin_word.length() != end_word.length())
    {   
        error(begin_word, end_word, "Start and end words must be same length!");
        return {};}

    if (word_list.find(end_word) == word_list.end())
    {   
        error(begin_word, end_word, "End word not in file!");
        return {};} 

    queue<vector<string>> ladder_q;
    ladder_q.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_q.empty())
    {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string last_word = ladder.back();
        // cout << "Exploring ladder: ";
        for (const string& word : word_list)
        {
            if (is_adjacent(last_word, word)){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word==end_word){return new_ladder;}
                    ladder_q.push(new_ladder);
                }
            }
        }
    }
    error(begin_word, end_word, "No ladder found!");
    return {};
}

void load_words(set<string>& word_list, const string& file_name)
{
    ifstream file(file_name);
    string word;
    while (file >> word){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty()) {cout << "No word ladder found.\n";}
    else{cout << "Word ladder found: ";
        for (const string& word : ladder){cout << word << " ";}
        cout << "\n";
    }
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "small.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
