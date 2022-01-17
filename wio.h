#pragma once
#include <exception>
#include <string>
#include <termios.h>

class WIO;

const WIO *getWIO();

//Nead to get unbuffered wchar_t symbols. Used code from https://www.linux.org.ru/forum/development/5392862
class WIO final
{
	private:
	termios _tty;
	WIO();

	public:
	WIO(WIO&) = delete;
	WIO(WIO&&) = delete;
	~WIO();

	const wchar_t in()const;
	void out(const std::wstring&)const;
	void out(const wchar_t)const;
	void test(const wchar_t)const;
	void test(const std::wstring&)const;

	WIO &operator=(WIO&) = delete;
	WIO &&operator=(WIO&&) = delete;

	friend const WIO *getWIO();
};

class no_tty_exception final: public std::exception
{
	virtual const char *what()const noexcept override final;
};
