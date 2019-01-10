#include <iostream>

#include "Trie.h"

using namespace std;

Trie::Trie() { this->roots = new vector<TrieNode>(); }

vector<string> _getWords(vector<TrieNode> *children) {
  vector<string> words;

  for (int i = 0; i < children->size(); i++) {
    TrieNode child = (*children)[i];

    // Skip the endings.
    if (child.value == '\1') {
      continue;
    }

    // If the child has a child that is an ending, add itself to the list.
    for (int j = 0; j < child.children->size(); j++) {
      if ((*child.children)[j].value == '\1') {
        string word = "";
        words.push_back(child.value + word);
      }
    }

    // Also add all of the child words.
    vector<string> childWords = _getWords(child.children);
    for (int j = 0; j < childWords.size(); j++) {
      string childWord = childWords[j];
      words.push_back(child.value + childWord);
    }
  }

  return words;
}

vector<string> Trie::getWords() { return _getWords(this->roots); }

bool _find(vector<TrieNode> *children, string word) {
  if (word.empty()) {
    return true;
  }

  for (int i = 0; i < children->size(); i++) {
    TrieNode child = (*children)[i];
    if (word[0] == child.value) {
      return _find(child.children, word.substr(1));
    }
  }

  return false;
}

bool Trie::find(string word) {
  // Appends "\1" to the string to mark its end within the trie.
  return _find(this->roots, word + "\1");
}

void _push(vector<TrieNode> *children, string word) {
  if (word.empty()) {
    return;
  }

  for (int i = 0; i < children->size(); i++) {
    TrieNode child = (*children)[i];
    if (word[0] == child.value) {
      _push(child.children, word.substr(1));
      return;
    }
  }

  TrieNode child;
  child.value = word[0];
  child.children = new vector<TrieNode>();
  children->push_back(child);
  _push(child.children, word.substr(1));
}

void Trie::push(string word) {
  // Appends "\1" to the string to mark its end within the trie.
  _push(this->roots, word + "\1");
}