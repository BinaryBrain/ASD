#ifndef TernarySearchTrie_h
#define TernarySearchTrie_h

template < typename KeyType>
class TernarySearchTrie
{
private:
	struct Node {
	public:
		KeyType key;
		Node* right;
		Node* left;
		Node* middle;
		int nodeSize;
		bool endOfWord;
		Node(KeyType key) : key(key), endOfWord(false), right(nullptr), left(nullptr), middle(nullptr), nodeSize(1) { }
	};

	Node* root;

	void insert(Node* x, const KeyType* key)
	{
		if (x == nullptr)
		{
			x = new Node(*key);
		}

		if (*(key) < x->key)
		{
			insert(x->left, key);
		}
		else if (*(key) > x->key)
		{
			insert(x->right, key);
		}
		else
		{
			if (*(key + 1))
			{
				insert(x->middle, key + 1);
			}
			else
			{
				x->endOfWord = true;
			}
		}
	}

public:
	TernarySearchTrie() : root(nullptr){}

	void insert(const KeyType* key)
	{
		insert(root, key);
	}

	bool contains(const KeyType* key)
	{
		Node* x = root;
		KeyType k = *key;

		while (x != nullptr)
		{
			if (k < x->key)
			{
				x = x->left;
			}
			else if (k > x->key)
			{
				x = x->right;
			}
			else
			{
				if ((k + 1) == '\0')
				{
					return true;
				}

				k = *++key;
				x = x->middle;
			}
		}

		return false;
	}

};

#endif