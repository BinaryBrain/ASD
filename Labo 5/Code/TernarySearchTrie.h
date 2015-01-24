#ifndef TernarySearchTrie_h
#define TernarySearchTrie_h

template < typename KeyType, typename ValueType >
class TernarySearchTrie
{
private:
	struct Node {
	public:
		KeyType key;
		ValueType value;
		Node* right;
		Node* left;
		Node* middle;
		int nodeSize;
		Node(KeyType key, ValueType value) : key(key), value(value), right(nullptr), left(nullptr), middle(nullptr), nodeSize(1) { }
	};


};

#endif