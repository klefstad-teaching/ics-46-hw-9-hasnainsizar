#include "ladder.h"
#include <queue>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
{
    cout << "Error: " << msg << " for words " << word1 << " and " << word2 << endl;
}

vector<string> get_adjacent_words(const string& word, const unordered_set<string>& word_set)
{
    vector<string> adjacent_words;
    for (size_t i = 0; i < word.length(); ++i)
    {
        string mutated_word = word;
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (c == word[i]) continue; // Skip the original character
            mutated_word[i] = c;
            if (word_set.find(mutated_word) != word_set.end())
            {
                adjacent_words.push_back(mutated_word);
            }
        }
    }
    return adjacent_words;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word)
    {
        error(begin_word, end_word, "Start and end words are SAME!");
        return {};
    }

    if (word_list.find(end_word) == word_list.end())
    {
        error(begin_word, end_word, "End word not in file!");
        return {};
    }

    // Convert word_list to unordered_set for O(1) lookups
    unordered_set<string> word_set(word_list.begin(), word_list.end());

    queue<vector<string>> ladder_q;
    ladder_q.push({ begin_word });

    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_q.empty())
    {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string last_word = ladder.back();

        // Get adjacent words by mutating the last word
        vector<string> adjacent_words = get_adjacent_words(last_word, word_set);

        for (const string& word : adjacent_words)
        {
            if (word == end_word)
            {
                ladder.push_back(word);
                return ladder;
            }

            if (visited.find(word) == visited.end())
            {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                ladder_q.push(new_ladder);
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
    while (file >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty())
    {
        cout << "No word ladder found.\n";
    }
    else
    {
        cout << "Word ladder found: ";
        for (const string& word : ladder)
        {
            cout << word << " ";
        }
        cout << "\n";
    }
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).empty()); // No ladder exists
}
