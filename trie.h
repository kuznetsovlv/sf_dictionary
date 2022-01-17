#pragma once
#include<map>
#include<vector>
#include<string>

class Trie;
class Node final
{
	private:
	bool _endOfWord;
	std::vector<Node*> _children;
	Node(size_t);
	Node(Node&) = delete;
	Node(Node&&) = delete;
	~Node();

	Node& operator=(Node&) = delete;
	Node&& operator=(Node&&) = delete;

	friend class Trie;
};

class Trie final
{
	private:
	std::map<wchar_t, size_t> _keys;
	Node *_root;

	Node *add(Node*, wchar_t);
	Node *child(const Node*, wchar_t)noexcept;
	void coppyNode(const Node*, Node*);
	void find(const Node*, std::vector<std::wstring>&, std::vector<wchar_t>&, size_t)const;

	public:
	Trie(const std::wstring&);
	Trie(const Trie&);
	Trie(const Trie&&)noexcept;
	~Trie();

	Trie& operator=(const Trie&);
	Trie& operator=(const Trie&&)noexcept;

	void add(const std::wstring&);
	const std::vector<std::wstring> words(const std::wstring&);
	const size_t alphabetSize()const noexcept;
};
