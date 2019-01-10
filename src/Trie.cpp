#include <iostream>

#include "Trie.h"

using namespace std;

#define SPECIAL_CHAR '\1'

Trie::Trie() { this->roots = new vector<TrieNode>(); }

// TODO: The prefix thing is still a little awkward, figure out a better API.
vector<string> _getWords(vector<TrieNode> *children, char prefix) {
  vector<string> words;

  for (int i = 0; i < children->size(); i++) {
    TrieNode child = (*children)[i];

    // Skip the endings.
    if (prefix == SPECIAL_CHAR) {
      if (child.value == SPECIAL_CHAR) {
        continue;
      }
    } else {
      if (child.value != prefix) {
        continue;
      }
    }

    // If the child has a child that is an ending, add itself to the list.
    for (int j = 0; j < child.children->size(); j++) {
      if ((*child.children)[j].value == SPECIAL_CHAR) {
        string word = "";
        words.push_back(child.value + word);
      }
    }

    // Also add all of the child words.
    vector<string> childWords = _getWords(child.children, SPECIAL_CHAR);
    for (int j = 0; j < childWords.size(); j++) {
      string childWord = childWords[j];
      words.push_back(child.value + childWord);
    }
  }

  return words;
}

vector<string> Trie::getWords() { return this->getWords(SPECIAL_CHAR); }

vector<string> Trie::getWords(char prefix) {
  vector<string> words = _getWords(this->roots, prefix);
  for (int i = 0; i < words.size(); i++) {
    words[i] = words[i].substr(0, words[i].length() - 1);
  }
  return words;
}

TrieResult _findWithError(vector<TrieNode> *children, string word,
                          bool subError) {
  if (word.empty()) {
    TrieResult result;
    result.found = true;
    result.subError = subError;
    result.delError = false;
    return result;
  }

  for (int i = 0; i < children->size(); i++) {
    TrieNode child = (*children)[i];

    if (word[0] == child.value) {
      TrieResult result =
          _findWithError(child.children, word.substr(1), subError);
      if (result.found) {
        return result;
      }
    } else {
      if (!subError) {
        TrieResult result =
            _findWithError(child.children, word.substr(1), true);
        if (result.found) {
          return result;
        }
      }
    }
  }

  TrieResult result;
  result.found = false;
  result.subError = subError;
  result.delError = false;
  return result;
}

TrieResult Trie::findWithError(string word) {
  // Appends the special char to the string to mark its end within the trie.
  TrieResult result = _findWithError(this->roots, word + SPECIAL_CHAR, false);
  if (result.found) {
    return result;
  }

  for (int i = 0; i < word.length(); i++) {
    string wordCopy = string(word);
    wordCopy.erase(i, i + 1);

    TrieResult result =
        _findWithError(this->roots, wordCopy + SPECIAL_CHAR, false);
    if (result.found) {
      result.subError = false;
      result.delError = true;
      return result;
    }
  }

  return result;
}

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
  // Appends the special char to the string to mark its end within the trie.
  return _find(this->roots, word + SPECIAL_CHAR);
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
  // Appends the special char to the string to mark its end within the trie.
  _push(this->roots, word + SPECIAL_CHAR);
}