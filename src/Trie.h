#include <string>
#include <vector>

using namespace std;

class TrieNodeList;

// Represents a simple trie which stores words.
//
// Uses "\1" as a way to mark the end of strings within the trie. DO NOT use
// this character within the string stored in this trie; The behaviour is
// undefined.
class Trie {
public:
  // Creates an empty trie.
  Trie();

  // Returns the number of words in the trie.
  int getLength();

  // Returns the list of words in the trie.
  vector<string> getWords();

  // Finds the word within the trie, only returning true if the exact word
  // had been added into the trie.
  bool find(string word);

  // Adds a new word into the trie.
  void push(string word);

  // Outputs debug information about the trie.
  void debug();

private:
  int length;
  vector<string> words;
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
  // Creates the list with the default initial capacity.
  TrieNodeList();

  // Creates the list with a non-default initial capacity.
  TrieNodeList(int capacity);

  // Returns whether the list is empty.
  bool isEmpty();

  // Returns the length of the list.
  int getLength();

  // Pushes a new node into the list.
  void push(TrieNode node);

  // Returns the node at the given index of the list.
  TrieNode get(int i);

  // Outputs debug information about the list.
  void debug();

private:
  int length;
  int capacity;
  TrieNode *nodes;

  // Grows the list to twice the original capacity.
  void grow();
};