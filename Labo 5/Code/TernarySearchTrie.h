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
		int index;
		Node(KeyType key) : key(key), right(nullptr), left(nullptr), middle(nullptr), index(-1) { }
	};

	Node* root;
	std::vector<char*> matches;
	std::vector<Node*> nodeVector;

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

	void partialMatches(Node* x, const KeyType* key)
	{
		if (!x) return;

		if (*key == '.' || *key < x->key)
		{
			partialMatches(x->left, key);
		}
		if (*key == '.' || *key == x->key)
		{
			if (x->key && *key)
			{
				partialMatches(x->middle, key + 1);
			}
		}
		if (*key == 0 && x->key == 0)
		{
			//matches.push_back(x->index); TODO: trouver comment récupérer attribuer les index aux nodes.
		}
		if (*key == '.' || *key > x->key)
		{
			partialMatches(x->right, key);
		}
	}

	const KeyType* getKey(int index)
	{
		return index == -1 ? NULL : nodeVector[index]->key.c_str();
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

	std::vector<KeyType*> partialMatches(const KeyType* key)
	{
		partialMatches(root, key);
		return matches;
	}
};

#endif