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
      break;
    default:
      return 0;
    }
  }

  return 0;
}