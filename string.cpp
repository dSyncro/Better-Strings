#include <cstring>

#include "string.h"

#pragma region Constructors

string::string()
{
	_length = 0;
	_shared_buffer = std::shared_ptr<char>(new char[0]);
	return;
}

string::string(char c)
{
	_length = 1;
	char* buffer = new char[1];
	buffer[0] = c;
	_shared_buffer = std::shared_ptr<char>(buffer);
}

string::string(char* chars)
{
	_length = std::strlen(chars);
	char* buffer = new char[_length];
	std::memcpy(buffer, chars, _length);
	_shared_buffer = std::shared_ptr<char>(buffer);
}

string::string(const char* str)
{
	if (!str)
	{
		_length = 0;
		_shared_buffer = std::shared_ptr<char>(new char[0]);
		return;
	}

	_length = std::strlen(str);
	char* buffer = new char[_length];
	std::memcpy(buffer, str, _length);

	_shared_buffer = std::shared_ptr<char>(buffer);
}

string::string(const char* str, unsigned length)
{
	_length = length;
	char* buffer = new char[_length];
	std::memcpy(buffer, str, _length);

	_shared_buffer = std::shared_ptr<char>(buffer);
}

string::string(const string& str)
{
	_length = str._length;

	char* buffer = new char[_length];
	std::memcpy(buffer, str._shared_buffer.get(), _length);

	_shared_buffer = std::shared_ptr<char>(buffer);
}

string::~string()
{
	//delete[] _buffer;
}

#pragma endregion

#pragma region Methods

string string::substring(int start, int length) const
{
	if ((start + length) > _length) throw 1;

	char* buffer = new char[length];
	std::memcpy(buffer, _shared_buffer.get() + start, length);

	return string(buffer, length);
}

string string::strip() const
{
	unsigned start = 0;
	for (start; start < _length; start++)
		if (_shared_buffer.get()[start] != ' ' && _shared_buffer.get()[start] != '\n') break;

	unsigned end = _length - 1;
	for (end; end; end--)
		if (_shared_buffer.get()[end] != ' ' && _shared_buffer.get()[end] != '\n') break;

	int count = end - start + 1;
	return substring(start, count);
}

string string::strip(char c) const
{
	unsigned start = 0;
	for (start; start < _length; start++)
		if (_shared_buffer.get()[start] != c) break;

	unsigned end = _length - 1;
	for (end; end; end--)
		if (_shared_buffer.get()[end] != c) break;

	int count = end - start + 1;
	return substring(start, count);
}

string string::lstrip() const
{
	unsigned i = 0;
	for (i; i < _length; i++)
		if (_shared_buffer.get()[i] != ' ' && _shared_buffer.get()[i] != '\n') break;

	return substring(i, _length - i);
}

string string::lstrip(char c) const
{
	unsigned i = 0;
	for (i; i < _length; i++)
		if (_shared_buffer.get()[i] != c) break;

	return substring(i, _length - i);
}

string string::rstrip() const
{
	unsigned i = _length - 1;
	for (i; i; i--)
		if (_shared_buffer.get()[i] != ' ' && _shared_buffer.get()[i] != '\n') break;

	return substring(0, i + 1);
}

string string::rstrip(char c) const
{
	unsigned i = _length - 1;
	for (i; i; i--)
		if (_shared_buffer.get()[i] != c) break;

	return substring(0, i + 1);
}

string string::removeAt(int index) const
{
	unsigned len = _length - 1;
	char* buffer = new char[len];

	std::memcpy(buffer, _shared_buffer.get(), index);
	std::memcpy(buffer + index, _shared_buffer.get() + index + 1, len - index);

	return string(buffer, len);
}

string string::removeFirst(char c) const
{
	int index = firstIndexOf(c);
	if (index == -1) return *this;

	return removeAt(index);
}

string string::removeLast(char c) const
{
	int index = lastIndexOf(c);
	if (index == -1) return *this;

	return removeAt(index);
}

string string::removeAll(char c) const
{
	int count = occurenciesCount(c);
	if (!count) return *this;

	unsigned len = _length - count;
	char* buffer = new char[len];

	int occurence = 0;
	for (int i = 0; i < len; i++)
	{
		if (_shared_buffer.get()[i + occurence] == c) occurence++;
		buffer[i] = _shared_buffer.get()[i + occurence];
	}

	return string(buffer, len);
}

string string::replaceAt(int index, char c) const
{
	if (index >= _length) throw 1;

	string s = *this;
	s[index] = c;

	return s;
}

string string::replaceFirst(char before, char after) const
{
	int index = firstIndexOf(before);
	if (index == -1) return *this;

	return replaceAt(index, after);
}

string string::replaceLast(char before, char after) const
{
	int index = lastIndexOf(before);
	if (index == -1) return *this;

	return replaceAt(index, after);
}

string string::replaceAll(char before, char after) const
{
	if (!contains(before)) return *this;

	string s = *this;
	for (int i = 0; i < _length; i++)
		if (s[i] == before) s[i] = after;

	return s;
}

string string::toLower() const
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _shared_buffer.get()[i];
		if (charAtIndex >= 'A' && charAtIndex <= 'Z')
			buffer[i] = charAtIndex - ('Z' - 'z');
		else buffer[i] = charAtIndex;
	}
	return string(buffer, _length);
}

string string::toUpper() const
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _shared_buffer.get()[i];
		if (charAtIndex >= 'a' && charAtIndex <= 'z')
			buffer[i] = charAtIndex - ('z' - 'Z');
		else buffer[i] = charAtIndex;
	}
	return string(buffer, _length);
}

string string::switchCase() const
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _shared_buffer.get()[i];
		if (charAtIndex >= 'a' && charAtIndex <= 'z')
			buffer[i] = charAtIndex - ('z' - 'Z');
		else if (charAtIndex >= 'A' && charAtIndex <= 'Z')
			buffer[i] = charAtIndex - ('Z' - 'z');
		else buffer[i] = charAtIndex;
	}
	return string(buffer, _length);
}

int string::firstIndexOf(char c) const
{
	for (int i = 0; i < _length; i++)
		if (_shared_buffer.get()[i] == c) return i;

	return -1;
}

int string::lastIndexOf(char c) const
{
	for (int i = _length - 1; i >= 0; i--)
		if (_shared_buffer.get()[i] == c) return i;

	return -1;
}

int string::occurenciesCount(char c) const
{
	int count = 0;
	for (int i = 0; i < _length; i++)
		if (_shared_buffer.get()[i] == c) count++;

	return count;
}

bool string::contains(char c) const
{
	for (int i = 0; i < _length; i++)
		if (_shared_buffer.get()[i] == c) return true;

	return false;
}

bool string::contains(string str) const
{
	if (str._length > _length) return false;

	int gap = _length - str._length;
	for (int i = 0; i <= gap; i++)
	{
		if (_shared_buffer.get()[i] != str[0]) continue;

		int j = 1;
		for (j = 1; j < str._length; j++)
			if (_shared_buffer.get()[i + j] != str[j]) break;

		if (j == str._length) return true;
	}

	return false;
}

bool string::isEmpty() const { return _length; }

std::vector<string> string::split(char c) const
{
	std::vector<string> strings;

	string s = strip();

	unsigned count = s.occurenciesCount(c);
	if (!count) return strings;

	unsigned lastIndexOf = 0;
	strings.resize(count + 1);
	count = 0;

	for (unsigned i = 0; i < _length; i++)
	{
		if (s._shared_buffer.get()[i] != c) continue;

		strings[count] = s.substring(lastIndexOf, i - lastIndexOf);
		lastIndexOf = i + 1;
		count++;
	}

	strings[count] = s.substring(lastIndexOf, _length - lastIndexOf);

	return strings;
}

unsigned string::length() const { return _length; }

#pragma endregion

#pragma region Static Methods

string string::empty() { return ""; }

#pragma endregion

#pragma region Operators

string& string::operator +=(const string& str)
{
	unsigned length = _length + str._length;
	char* final_buffer = new char[length];

	std::memcpy(final_buffer, _shared_buffer.get(), _length);
	std::memcpy(final_buffer + _length, str._shared_buffer.get(), str._length);

	_length = length;
	_shared_buffer = std::shared_ptr<char>(final_buffer);

	return *this;
}

char string::operator [](int index) const
{
	if (index >= _length) throw 1;

	return _shared_buffer.get()[index];
}

char& string::operator [](int index)
{
	if (index >= _length) throw 1;

	return _shared_buffer.get()[index];
}

string operator +(const string& a, const string& b) { return string(a) += b; }

string operator +(const string& a, char b) { return string(a) += string(b); }

string operator +(char a, const string& b) { return string(a) += b; }

string operator +(const string& a, const char* b) { return string(a) += string(b); }

string operator +(const char* a, const string& b) { return string(a) += b; }

string operator *(const string& str, unsigned n)
{
	unsigned len = str._length * n;
	char* buffer = new char[len];

	for (int i = 0; i < n; i++)
		std::memcpy(buffer + i * str._length, str._shared_buffer.get(), str._length);

	string s = string();
	s._length = len;
	s._shared_buffer = std::shared_ptr<char>(buffer);

	return s;
}

string operator *(unsigned n, const string& str) { return str * n; }

bool operator ==(const string& a, const string& b)
{
	if (a.length() != b.length()) return false;

	for (unsigned i = 0; i < a.length(); i++)
		if (a[i] != b[i]) return false;

	return true;
}

bool operator ==(const string& a, const char* b)
{
	if (a.length() != std::strlen(b)) return false;

	for (unsigned i = 0; i < a._length; i++)
		if (a[i] != b[i]) return false;

	return true;
}

bool operator ==(const char* a, const string& b)
{
	if (b.length() != std::strlen(a)) return false;

	for (unsigned i = 0; i < b._length; i++)
		if (a[i] != b[i]) return false;
	return true;
}

bool operator ==(const string& str, char c)
{
	if (str._length != 1) return false;
	return (str[0] == c) ? true : false;
}

bool operator ==(char c, const string& str) { return str == c; }

bool operator !=(const string& a, const string& b) { return !(a == b); }

bool operator !=(const string& a, const char* b) { return !(a == b); }

bool operator !=(const char* a, const string& b) { return !(a == b); }

bool operator !=(const string& str, char c) { return !(str == c); }

bool operator !=(char c, const string& str) { return !(str == c); }

std::ostream& operator <<(std::ostream& stream, string& str)
{
	stream.write(str._shared_buffer.get(), str._length);
	return stream;
}

std::istream& operator >>(std::istream& stream, string& str)
{
	char* c = new char[512];
	stream >> c;

	str = string(c);
	delete[] c;

	return stream;
}

#pragma endregion

#pragma region Cast Operators

string::operator char* () const { return _shared_buffer.get(); }
string::operator const char* () const { return _shared_buffer.get(); }

#pragma endregion
