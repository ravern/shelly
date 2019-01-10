#include <string>
#include <vector>

using namespace std;

// Represents a node within a trie.
struct TrieNode {
  char value;
  vector<TrieNode> *children;
};

// Represents a simple trie which stores words.
//
// Uses "\1" as a way to mark the end of strings within the trie. DO NOT use
// this character within the string stored in this trie; The behaviour is
// undefined.
class Trie {
public:
  Trie();

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
  vector<TrieNode> *roots;
};