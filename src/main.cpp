#include <fstream>
#include <iostream>
#include <string>

#include "Trie.h"

using namespace std;

// Loads all the words in the dictionary into the trie.
bool loadDict(Trie *dict) {
  ifstream dictionary;
  dictionary.open("data/dictionary.txt");

  if (!dictionary.is_open()) {
    return false;
  }

  string word;
  while (!dictionary.eof()) {
    getline(dictionary, word);
    dict->push(word);
  }

  dictionary.close();
  return true;
}

// Displays the main menu.
void printMainMenu() {
  cout << "Welcome to Grammarly 2.0!" << endl;
  cout << endl;
  cout << " [1] Spell check a word" << endl;
  cout << " [2] Spell check a file" << endl;
  cout << " [3] Add a new word" << endl;
  cout << " [4] Save dictionary to file" << endl;
  cout << " [5] Words that start with letter" << endl;
  cout << " [6] Spell check a word (allow errors)" << endl;
  cout << " [0] Exit" << endl;
  cout << endl;
}

// Spell checks a single word.
void spellCheckWord(Trie *dict) {
  cout << "Enter your word: ";

  string word;
  cin >> word;

  if (dict->find(word)) {
    cout << "Your word is spelled correctly!" << endl;
  } else {
    cout << "Your word is spelled wrongly!" << endl;
  }

  cout << endl;
}

// Spell checks an entire file.
bool spellCheckFile(Trie *dict) {
  cout << "Enter the path to your file: ";

  string path;
  cin >> path;

  ifstream input;
  input.open(path);

  if (!input.is_open()) {
    return false;
  }

  cout << "Listing wrongly spelled words..." << endl;

  string word;
  while (!input.eof()) {
    getline(input, word);
    if (!dict->find(word)) {
      cout << word << endl;
    }
  }

  cout << endl;

  return true;
}

void addWord(Trie *dict) {
  cout << "Enter your word: ";

  string word;
  cin >> word;

  dict->push(word);

  cout << endl;
}

bool saveDictToFile(Trie *dict) {
  ofstream dictionary;
  dictionary.open("data/dictionary.txt");

  if (!dictionary.is_open()) {
    return false;
  }

  // Output each word to the file.
  vector<string> words = dict->getWords();
  for (int i = 0; i < words.size(); i++) {
    dictionary << words[i];
    if (i != words.size() - 1) {
      dictionary << endl;
    }
  }

  dictionary.close();
  return true;
}

void printWordsWithPrefix(Trie *dict) {
  cout << "Enter the first letter: ";

  char prefix;
  cin >> prefix;

  cout << "Finding words..." << endl;

  // Output each word to the screen.
  vector<string> words = dict->getWords(prefix);
  for (int i = 0; i < words.size(); i++) {
    cout << words[i] << endl;
  }

  cout << endl;
}

// Spell checks a single word.
void spellCheckWordWithError(Trie *dict) {
  cout << "Enter your word: ";

  string word;
  cin >> word;

  TrieResult result = dict->findWithError(word);

  if (result.found) {
    cout << "Your word is spelled correctly!" << endl;
    if (result.subError) {
      cout << "Your word had a substitution error >:(" << endl;
    }
    if (result.delError) {
      cout << "Your word had a deletion error >:(" << endl;
    }
  } else {
    cout << "Your word is spelled wrongly!" << endl;
  }

  cout << endl;
}

int main() {
  Trie *dict = new Trie();

  // Load the dictionary into the trie.
  if (!loadDict(dict)) {
    cout << "Error: Failed to load dictionary!" << endl;
    return 1;
  }

  // Start the main loop.
  while (true) {
    printMainMenu();

    int option;
    cin >> option;
    cout << endl;

    switch (option) {
    case 1:
      spellCheckWord(dict);
      break;
    case 2:
      if (!spellCheckFile(dict)) {
        cout << "Error: Failed to load input!" << endl;
        return 1;
      }
      break;
    case 3:
      addWord(dict);
      break;
    case 4:
      if (!saveDictToFile(dict)) {
        cout << "Error: Failed to save dictionary!" << endl;
        return 1;
      }
      break;
    case 5:
      printWordsWithPrefix(dict);
      break;
    case 6:
      spellCheckWordWithError(dict);
      break;
    default:
      return 0;
    }
  }

  return 0;
}