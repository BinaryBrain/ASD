#ifndef TernarySearchTrie_h
#define TernarySearchTrie_h

template <typename KeyType>
class TernarySearchTrie
{
private:
	struct Node {
	public:
		KeyType key;
		Node* right;
		Node* left;
		Node* middle;
		Node(KeyType key) : key(key), right(nullptr), left(nullptr), middle(nullptr) { }
	};

	Node* root;

	Node* insert(Node* x, const KeyType* key)
	{
		if (x == nullptr)
		{
			x = new Node(*key);
		}

		if (*key < x->key)
		{
			x->left = insert(x->left, key);
		}
		else if (*(key) > x->key)
		{
			x->right = insert(x->right, key);
		}
		else
		{
			if (*key != 0)
			{
				x->middle = insert(x->middle, ++key);
			}
		}

		return x;
	}

public:
	TernarySearchTrie() : root(nullptr){}

	void insert(const KeyType* key)
	{
		root = insert(root, key);
	}

	bool contains(const KeyType* key)
	{
		Node* x = root;

		while (x != nullptr)
		{
			if (*key < x->key)
			{
				x = x->left;
			}
			else if (*key > x->key)
			{
				x = x->right;
			}
			else
			{
				if (*key++ == 0)
				{
					return true;
				}

				x = x->middle;
			}
		}

		return false;
	}

};

#endif