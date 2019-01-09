#include <string>

using namespace std;

class TrieNodeList;

// Represents a simple trie which stores words.
//
// Uses "\1" as a way to mark the end of strings within the trie. DO NOT use
// this character within the string stored in this trie; The behaviour is
// undefined.
class Trie {
public:
  Trie();
  bool find(string word);
  void push(string word);

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
  int getLength();
  void push(TrieNode node);
  TrieNode get(int i);
  void debug();

private:
  int capacity;
  TrieNode *nodes;

  void grow();
};