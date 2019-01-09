#include <iostream>

#include "Trie.h"

using namespace std;

int main() {
  Trie *dict = new Trie();

  dict->push("john");
  dict->push("mary");

  cout << dict->find("john") << endl;
  cout << dict->find("mary") << endl;
  cout << dict->find("jane") << endl;

  return 0;
}