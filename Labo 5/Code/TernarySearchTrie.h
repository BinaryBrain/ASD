#ifndef TernarySearchTrie_h
#define TernarySearchTrie_h

template < typename KeyType, typename ValueType >
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
		bool enOfWord;
		Node(KeyType key) : key(key), enOfWord(false), right(nullptr), left(nullptr), middle(nullptr), nodeSize(1) { }
	};

	Node* root;

public:
	TernarySearchTrie() : root(nullptr){}


	bool contains(const KeyType* key)
	{
		Node* x = root;
		KeyType* k = key;

		while (x != nullptr)
		{
			if (*k < x->key)
			{
				x = x->left;
			}
			else if (*k > x->key)
			{
				x = x->right;
			}
			else
			{
				if (*(k + 1) == nullptr)
				{
					return true;
				}

				k++;
				x = x->middle;
			}
		}

		return false;
	}

	void insert(Node* x, const KeyType* key)
	{
		if (x == nullptr)
		{
			*x = new Node(*key);
		}

		if (*(key) < (*x)->key)
		{
			insert(&((*x)->left), key);
		}
		else if (*(key) > (*x)->key)
		{
			insert(&((*x)->right), key);
		}
		else
		{
			if (*(x + 1))
			{
				insert(&((*x)->middle), key + 1);
			}
			else
			{
				(*x)->endOfWord = true;
			}
		}
	}

};

#endif