#include <iostream>

#include "Trie.h"

using namespace std;

#define DEFAULT_CAPACITY 2

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

void TrieNodeList::push(TrieNode node) {
  if (this->length == this->capacity) {
    this->grow();
  }

  this->nodes[this->length] = node;
  this->length++;
}

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