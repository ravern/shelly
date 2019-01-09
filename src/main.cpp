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
    default:
      return 0;
    }
  }

  return 0;
}