#include <iostream>

#include "Trie.h"

using namespace std;

#define DEFAULT_CAPACITY 2

Trie::Trie() { this->roots = new TrieNodeList(26); }

int Trie::getLength() { return this->length; }

bool _find(TrieNodeList *children, string word) {
  if (word.empty()) {
    return true;
  }

  for (int i = 0; i < children->getLength(); i++) {
    TrieNode child = children->get(i);
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

void _push(TrieNodeList *children, string word) {
  if (word.empty()) {
    return;
  }

  for (int i = 0; i < children->getLength(); i++) {
    TrieNode child = children->get(i);
    if (word[0] == child.value) {
      _push(child.children, word.substr(1));
      return;
    }
  }

  TrieNode child;
  child.value = word[0];
  child.children = new TrieNodeList();
  children->push(child);
  _push(child.children, word.substr(1));
}

void Trie::push(string word) {
  // Appends "\1" to the string to mark its end within the trie.
  _push(this->roots, word + "\1");
  this->length++;
}

TrieNodeList::TrieNodeList() {
  this->capacity = DEFAULT_CAPACITY;
  this->length = 0;

  this->nodes = (TrieNode *)malloc(this->capacity * sizeof(TrieNode));
}

TrieNodeList::TrieNodeList(int capacity) {
  this->capacity = capacity;
  this->length = 0;

  this->nodes = (TrieNode *)malloc(this->capacity * sizeof(TrieNode));
}

bool TrieNodeList::isEmpty() { return this->length == 0; }

int TrieNodeList::getLength() { return this->length; }

void TrieNodeList::push(TrieNode node) {
  if (this->length == this->capacity) {
    this->grow();
  }

  this->nodes[this->length] = node;
  this->length++;
}

TrieNode TrieNodeList::get(int i) { return this->nodes[i]; }

void TrieNodeList::debug() {
  for (int i = 0; i < this->length; i++) {
    cout << this->nodes[i].value << endl;
  }
}

void TrieNodeList::grow() {
  int capacity = this->capacity * 2;
  TrieNode *nodes = (TrieNode *)malloc(capacity * sizeof(TrieNode));

  for (int i = 0; i < capacity; i++) {
    nodes[i] = this->nodes[i];
  }

  free(this->nodes);
  this->capacity = capacity;
  this->nodes = nodes;
}