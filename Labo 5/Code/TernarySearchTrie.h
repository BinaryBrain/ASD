// Léonard Berney, Sacha Bron

#ifndef TernarySearchTrie_h
#define TernarySearchTrie_h

class TernarySearchTrie
{
private:
	struct Node {
	public:
		char key;
		Node* right;
		Node* left;
		Node* middle;
		int index; // pas implémenté
		Node(char key) : key(key), right(nullptr), left(nullptr), middle(nullptr), index(-1) { }
	};

	Node* root;
	std::vector<int> matchesIndexes; // pas implémenté

	// ajoute un mot dans l'arbre en commençant au noeud donné
	Node* insert(Node* x, const char* key)
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

	// implémentation pas terminée
	void partialMatches(Node* x, const char* key)
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
			matchesIndexes.push_back(x->index); //TODO: trouver comment attribuer les index aux nodes.
		}
		if (*key == '.' || *key > x->key)
		{
			partialMatches(x->right, key);
		}
	}

public:
	TernarySearchTrie() : root(nullptr){}

	// ajoute un mot dans l'arbre
	void insert(const char* key)
	{
		root = insert(root, key);
	}

	// vérifie si un mot est contenu dans l'arbre
	bool contains(const char* key)
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

	// pas implémenté
	std::vector<char*> wildCardMatch(const char* key)
	{
		std::vector<char*> matches;
		//TODO: remplir matches
		partialMatches(root, key);
		return matches;
	}
};

#endif