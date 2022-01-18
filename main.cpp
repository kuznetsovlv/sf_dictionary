#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "fill.h"
#include "trie.h"
#include "wio.h"

const std::wstring ALPHABET = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

int main()
{
	try
	{
		const WIO *wio = getWIO();
		Trie dict(ALPHABET);

		fill(dict, L"grandmother grand gramm go mother mummy cat car мама книга кирка");

		wchar_t wc;
		std::wstring text, word;
		std::vector<std::wstring> words;

		do
		{
			wc = wio->in();
			//wio->test(wc);

			switch(wc)
			{
				case 0x20:	//SPACE
					word.clear();
					words.clear();
					text.push_back(wc);
					break;
				case 0x9:	//TAB
					if(words.size())
					{
						wio->out(0xa);
						for(std::wstring str: words)
						{
							wio->out(str, true);
						}
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
							}
							words.clear();
						}
					}
					wio->out(0xa);
					wio->out(text);
					break;
				case 0xa:	//ENTER
					break;
				default:
						if(ALPHABET.find(wc) != std::string::npos)
						{
							if(!words.empty())
							{
								words.clear();
							}
							word.push_back(wc);
							text.push_back(wc);
						}
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
