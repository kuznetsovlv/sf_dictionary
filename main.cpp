#include <iostream>
#include <string>
#include <exception>
#include "trie.h"
#include "wio.h"

int main()
{
	try
	{
		const WIO *wio = getWIO();

		wchar_t wc;
		std::wstring str;

		do
		{
			wc = wio->in();
			std::cout << std::endl;
			wio->test(wc);
			str.push_back(wc);
		} while(wc != 0xa);

		wio->out(str);
	}
	catch(std::exception error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
