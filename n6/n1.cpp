//
// Created by Антон Деев
//
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cctype>
using namespace std;
vector<int>::iterator find(vector<int>::iterator first,
                           vector<int>::iterator last,
                           int el) {
    for (auto it = first; it != last; ++it) {
        if (*it == el) return it;
    }
    return last;
}

vector<int>::iterator findInSorted(vector<int>::iterator first,
                                   vector<int>::iterator last,
                                   int el) {
    sort(first, last);
    for (auto it = first; it != last; ++it) {
        if (*it == el) return it;
    }
    return last;
}

bool isLetter(unsigned char c) {
    return isalpha(c) != 0;
}

int wordsCounter(const string& str) {
    if (str.empty()) return 0;

    int count = 0;
    bool in_word = false;

    for (unsigned char c : str) {
        if (isLetter(c)) {
            if (!in_word) {
                in_word = true;
                ++count;
            }
        } else {
            in_word = false;
        }
    }
    return count;
}

map<string, int> wordsMapCounter(const string& text) {
    map<string, int> word_count;
    string word;
    for (unsigned char c : text) {
        if (isLetter(c)) {
            word += c;
        } else if (!word.empty()) {
            ++word_count[word];
            word.clear();
        }
    }
    if (!word.empty()) ++word_count[word];
    return word_count;
}

vector<string> uniqueWords(const string& str) {
    map<string, int> word_map;
    string word;
    for (unsigned char c : str) {
        if (isLetter(c)) {
            word += c;
        } else if (!word.empty()) {
            ++word_map[word];
            word.clear();
        }
    }
    if (!word.empty()) ++word_map[word];

    vector<string> result;
    for (const auto& [w, cnt] : word_map) {
        if (cnt == 1) result.push_back(w);
    }
    return result;
}

int diffWordsCounter(const string& str) {
    set<string> unique_words;
    string word;

    for (unsigned char c : str) {
        if (isLetter(c)) {
            word += c;
        } else if (!word.empty()) {
            unique_words.insert(word);
            word.clear();
        }
    }
    if (!word.empty()) unique_words.insert(word);

    return unique_words.size();
}

void reverseNum(list<int>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        nums.insert(it, -(*it));
    }
}

void plusesDeleter(vector<int>& v) {
    v.erase(remove_if(v.begin(), v.end(),
                      [](int x) { return x > 0; }),
            v.end());
}

void Sort(list<int>& nums) {
    nums.sort(greater<int>());
}

int main() {
    // Zadanie 1
    vector<int> arr_1 = {1, 2, 3, 4, 5};
    auto iter_1 = find(arr_1.begin(), arr_1.end(), 3);
    if (iter_1 != arr_1.end())
        cout << "Find(3) = " << distance(arr_1.begin(), iter_1) << "\n";

    // Zadanie 2
    vector<int> arr_2 = {1, 2, 8, 4, 5};
    auto iter_2 = findInSorted(arr_2.begin(), arr_2.end(), 8);
    if (iter_2 != arr_2.end())
        cout << "Find(8) = " << distance(arr_2.begin(), iter_2) << "\n";

    // Zadanie 3
    string text_1 = "I went home, went to sleep. Woke up and ran";
    cout << "Amount of words - " << wordsCounter(text_1) << "\n";

    // Zadanie 4
    auto count_words = wordsMapCounter(text_1);
    for (const auto& [w, cnt] : count_words) {
        cout << "Words[\"" << w << "\"] == " << cnt << "\n";
    }

    // Zadanie 5
    string text_3 = "Can you can can";
    auto unique = uniqueWords(text_3);
    cout << "Unique words: ";
    for (const auto& w : unique) cout << "\"" << w << "\" ";
    cout << "\n";

    // Zadanie 6
    string text_4 = "can you can a can";
    cout << "Different words count: " << diffWordsCounter(text_4) << "\n";

    // Zadanie 7
    list<int> nums = {1, 5, 4, -3};
    reverseNum(nums);
    for (int n : nums) cout << n << " ";
    cout << "\n";

    // Zadanie 8
    vector<int> v = {1, 0, -8, -9, 0, 10, 23, -7};
    plusesDeleter(v);
    for (int n : v) cout << n << " ";
    cout << "\n";

    // Zadanie 9
    list<int> nums_list = {1, 5, 4, -3};
    Sort(nums_list);
    for (int n : nums_list) cout << n << " ";
    cout << "\n";

    return 0;
}
