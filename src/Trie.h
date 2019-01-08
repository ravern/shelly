#include <string>

class TrieNodeList;

// Represents a simple trie which stores words.
class Trie {
public:
  Trie();

private:
  TrieNodeList *roots;
};

// Represents a node within a trie.
struct TrieNode {
  char value;
  TrieNodeList *children;
};

// Represents a list of nodes within a trie.
class TrieNodeList {
public:
  int length;

  TrieNodeList();
  TrieNodeList(int capacity);
  bool isEmpty();
  void push(TrieNode node);
  void debug();

private:
  int capacity;
  TrieNode *nodes;

  void grow();
};