#include <string>
#include "trie.h"
#include "fill.h"

void fill(Trie& trie, const std::wstring &wordList)
{
	std::wstring current;

	for(wchar_t c: wordList)
	{
		if(c == 0x20)
		{
			if(!current.empty())
			{
				trie.add(current);
				current.clear();
			}
		}
		else
		{
			current.push_back(c);
		}
	}

	if(!current.empty())
	{
		trie.add(current);
	}
}
