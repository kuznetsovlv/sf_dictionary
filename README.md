# SkillFactory HW Module 13

## Finding words by it's prefixes using prefix tree

## Classes:

- `WIO` - input/output class, nead to get unbuffered input of wchar_ts. And output of std::wstrings and wchar_ts.To create has bean used code from https://www.linux.org.ru/forum/development/5392862
- `Trie` - prefix tree. Created with alphabet of wchar_ts and used to find words by prefixes of type std::wstring.
- method `fill` usedto fill `Trie` dictionary with words.

## Usig:
```
$make
$./dictionary
```
Print text, `TAB` to find autofil if it is single, double `TAB` shows all available variants, `SPACE` to start entering new word, `ENTER` - to exit.

## IT IS IMPORTANT:
Because of WIO the programm may not work at Windows. Tested at Linux Mint 20.2, compiled with gcc 9.3.0