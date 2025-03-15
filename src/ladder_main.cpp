#include "ladder.h"
#include <algorithm>

int main()
{
    // verify_word_ladder();
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    if (!ladder.empty()){print_word_ladder(ladder);}
    return 0;
}
