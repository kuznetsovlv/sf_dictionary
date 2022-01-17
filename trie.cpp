#include<map>
#include<vector>
#include<string>
#include "trie.h"

Node::Node(size_t size):_endOfWord(false)
{
	for(size_t i = 0; i < size; ++i)
	{
		_children.push_back(nullptr);
	}
}

Node::~Node()
{
	for(Node *child: _children)
	{
		if(child)
		{
			delete child;
		}
	}
}

Trie::Trie(const std::wstring& letters):_root(nullptr)
{
	size_t index = 0;
	for(wchar_t key: letters)
	{
		auto search = _keys.find(key);
		if(search == _keys.end())
		{
			_keys[key] = index++;
		}
	}
}

Trie::Trie(const Trie &that)
{
	_keys = that._keys;

	if(that._root)
	{
		_root = new Node(_keys.size());
		coppyNode(that._root, _root);
	}
}

Trie::Trie(const Trie &&that)noexcept
{
	if(_root)
	{
		delete _root;
	}

	_keys = std::move(that._keys);
	_root = std::move(that._root);
}

Trie::~Trie()
{
	if(_root)
	{
		delete _root;
	}
}

Node *Trie::add(Node* root, wchar_t c)
{
	Node *node = child(root, c);

	if(!node)
	{
		node = new Node(alphabetSize());
		root->_children[_keys[c]] = node;
	}

	return node;
}

Node *Trie::child(const Node* root, wchar_t c)noexcept
{
	return root->_children[_keys[c]];
}

void Trie::coppyNode(const Node *from, Node *to)
{
	for(size_t i = 0; i < from->_children.size(); ++i)
	{
		if(from->_children[i])
		{
			to->_children[i] = new Node(alphabetSize());
			coppyNode(from->_children[i], to->_children[i]);
		}
	}
}

Trie &Trie::operator=(const Trie &that)
{
	_keys = that._keys;

	if(that._root)
	{
		_root = new Node(_keys.size());
		coppyNode(that._root, _root);
	}

	return *this;
}

Trie &Trie::operator=(const Trie &&that)noexcept
{
	if(_root)
	{
		delete _root;
	}

	_keys = std::move(that._keys);
	_root = std::move(that._root);

	return *this;
}

void Trie::add(const std::wstring &str)
{
	if(!_root)
	{
		_root = new Node(alphabetSize());
	}

	Node *node = _root;
	for(wchar_t c: str)
	{
		node = add(node, c);
	}

	node->_endOfWord = true;
}

const size_t Trie::alphabetSize()const noexcept
{
	return _keys.size();
}
