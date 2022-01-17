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

	friend class Trie;
};

class Trie final
{
	private:
	std::map<wchar_t, size_t> _keys;
	Node *_root;

	Node *child(Node*, wchar_t);

	public:
	Trie(const std::wstring&);
	Trie(const Trie&)noexcept;
	Trie(const Trie&&)noexcept;
	~Trie();

	Trie& operator=(Trie&)noexcept;
	Trie&& operator=(Trie&&)noexcept;

	void add(const std::wstring&);
	const std::vector<std::wstring> words(const std::wstring&)const noexcept;
};
