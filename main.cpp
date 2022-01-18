#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "trie.h"
#include "wio.h"

int main()
{
	try
	{
		const WIO *wio = getWIO();
		Trie dict(L"");

		wchar_t wc;
		std::wstring text, word;
		std::vector<std::wstring> words;

		do
		{
			wc = wio->in();

			switch(wc)
			{
				case 0x20:
					word.clear();
					words.clear();
					text.push_back(wc);
					break;
				case 0x9:
					if(words.size())
					{
						for(std::wstring str: words)
						{
							wio->out(0xa);
							wio->out(str, true);
						}
						wio->out(text);
						words.clear();
					}
					else if(!word.empty())
					{
						words = dict.words(word);
						if(words.size() == 1)
						{
							for(size_t i = word.size(); i < words[0].size(); ++i)
							{
								word.push_back(words[0][i]);
								text.push_back(words[0][i]);
								wio->out(words[0][i]);
							}
							words.clear();
						}
					}
					wio->out(0xd);
					break;
				default:
					word.push_back(wc);
					words.clear();
					text.push_back(wc);
			}
		} while(wc != 0xa);
	}
	catch(std::exception error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
