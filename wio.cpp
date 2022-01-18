#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include "wio.h"

std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

const size_t CHAR_SIZE = 8 * sizeof(wchar_t);
const unsigned TEST_MASK = 1 << (CHAR_SIZE - 1);

WIO::WIO()
{
	if(!isatty(0))
	{
		throw no_tty_exception();
	}

	fflush(stdout);
	tcgetattr(0, &_tty);

	termios tty = _tty;
	tty.c_lflag &= ~(ISIG | ICANON);
	tty.c_cc[VMIN] = 1;
	tcsetattr(0, TCSAFLUSH, &tty);
}

WIO::~WIO()
{
	tcsetattr(0, TCSANOW, &_tty);
}

const wchar_t WIO::in()const
{
	std::string str;
	std::wstring wstr;
	char c;

	while(wstr.empty())
	{
		try
		{
			read(0, &c, 1);
			str.push_back(c);
			wstr = converter.from_bytes(str);
		}
		catch(...)
		{
		}
	}

	return wstr[0];
}

void WIO::out(const std::wstring &str, const bool withNextLine)const
{
	std::cout << converter.to_bytes(str);
	if(withNextLine)
	{
		std::cout << std::endl;
	}
	else
	{
		fflush(stdout);
	}
}

void WIO::out(const wchar_t c, const bool withNextLine)const
{
	std::cout << converter.to_bytes(c);
	if(withNextLine)
	{
		std::cout << std::endl;
	}
	else
	{
		fflush(stdout);
	}
}

void WIO::test(const wchar_t c)const
{
	std::cout << converter.to_bytes(c) << " - code: " << std::hex << std::showbase << static_cast<int>(c) << std::dec << " bits: ";

	for(size_t i = 0; i < CHAR_SIZE; ++i)
	{
		if(!(i % 8) && i)
		{
			std::cout << " ";
		}
		std::cout << (c & (TEST_MASK >> i) ? 1 : 0);
	}
	std::cout << std::endl;
}

void WIO::test(const std::wstring &str)const
{
	for(wchar_t c: str)
	{
		test(c);
	}
}

const char *no_tty_exception::what()const noexcept
{
	return "No tty";
}

const WIO *getWIO()
{
	static const WIO wio;

	return &wio;
}
