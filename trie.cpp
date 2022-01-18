#include <map>
#include <vector>
#include <string>
#include "trie.h"

Node::Node(const size_t size):_endOfWord(false)
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
		if(!_keys.contains(key))
		{
			_keys[key] = index++;
		}
	}
}

Trie::Trie(const Trie &that)
{
	_keys = that._keys;

	if(_root)
	{
		delete _root;
	}

	if(that._root)
	{
		_root = new Node(_keys.size());
		coppyNode(that._root, _root);
	}
	else
	{
		_root = nullptr;
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

Node *Trie::add(Node* root, const wchar_t c)
{
	if(!_keys.contains(c))
	{
		return nullptr;
	}

	Node *node = child(root, c);

	if(!node)
	{
		node = new Node(alphabetSize());
		root->_children[_keys[c]] = node;
	}

	return node;
}

Node *Trie::child(const Node* root, const wchar_t c)noexcept
{
	return _keys.contains(c) ? root->_children[_keys[c]] : nullptr;
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

void Trie::find(const Node *root, std::vector<std::wstring> &res, std::vector<wchar_t> &buf, size_t index)const
{
	if(root->_endOfWord)
	{
		std::wstring str;
		for(size_t i = 0; i < index; ++i)
		{
			str.push_back(buf[i]);
		}
		res.push_back(str);
	}

	for(const auto& [c, i]: _keys)
	{
		if(root->_children[i])
		{
			if(index < buf.size())
			{
				buf[index] = c;
			}
			else
			{
				buf.push_back(c);
			}

			find(root->_children[i], res, buf, index + 1);
		}
	}
}

Trie &Trie::operator=(const Trie &that)
{
	if(_root)
	{
		delete _root;
	}

	_keys = that._keys;

	if(that._root)
	{
		_root = new Node(_keys.size());
		coppyNode(that._root, _root);
	}
	else
	{
		_root = nullptr;
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

std::vector<std::wstring> Trie::words(const std::wstring &str)
{
	std::vector<std::wstring> res;

	if(!str.empty() && _root)
	{
		size_t index = 0;
		std::vector<wchar_t> buf;
		Node *node = _root;

		for(wchar_t c: str)
		{
			node = child(node, c);
			if(!node)
			{
				return res;
			}
			buf.push_back(c);
			++index;
		}
		find(node, res, buf, index);
	}

	return res;
}

const size_t Trie::alphabetSize()const noexcept
{
	return _keys.size();
}
