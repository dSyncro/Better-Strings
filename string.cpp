#include <cstring>
#include <stdexcept>

#include "string.h"

#pragma region Constructors

string::string() : _buffer(new char[0]), _length(0) {}

string::string(char c) : _length(1)
{
	char* buffer = new char[1];
	buffer[0] = c;

	_buffer = buffer;
}

string::string(char* chars)
{
	_length = std::strlen(chars);

	char* buffer = new char[_length];
	std::memcpy(buffer, chars, _length);

	_buffer = buffer;
}

string::string(char* chars, unsigned length) : _buffer(chars), _length(length) {}

string::string(const char* str)
{
	if (!str)
	{
		_length = 0;
		_buffer = new char[0];
		return;
	}

	_length = std::strlen(str);

	char* buffer = new char[_length];
	std::memcpy(buffer, str, _length);

	_buffer = buffer;
}

string::string(const string& str) : _length(str._length)
{
	char* buffer = new char[_length];
	std::memcpy(buffer, str._buffer, _length);

	_buffer = buffer;
}

string::~string()
{
	delete[] _buffer;
}

#pragma endregion

#pragma region Methods

int string::count(char c) const noexcept
{
	int count = 0;
	for (int i = 0; i < _length; i++)
		if (_buffer[i] == c) count++;

	return count;
}

int string::firstIndexOf(char c) const noexcept
{
	for (int i = 0; i < _length; i++)
		if (_buffer[i] == c) return i;

	return -1;
}

int string::lastIndexOf(char c) const noexcept
{
	for (int i = _length - 1; i >= 0; i--)
		if (_buffer[i] == c) return i;

	return -1;
}

unsigned string::length() const noexcept { return _length; }

bool string::contains(char c) const noexcept
{
	for (int i = 0; i < _length; i++)
		if (_buffer[i] == c) return true;

	return false;
}

bool string::contains(string str) const noexcept
{
	if (str._length > _length) return false;

	int gap = _length - str._length;
	for (int i = 0; i <= gap; i++)
	{
		if (_buffer[i] != str[0]) continue;

		int j = 1;
		for (j = 1; j < str._length; j++)
			if (_buffer[i + j] != str[j]) break;

		if (j == str._length) return true;
	}

	return false;
}

bool string::isAlphabet() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool upperRange = _buffer[i] >= 'A' && _buffer[i] <= 'Z';
		bool lowerRange = _buffer[i] >= 'a' && _buffer[i] <= 'z';
		if (!upperRange && !lowerRange) return false;
	}

	return true;
}

bool string::isAlphanum() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool upperRange = _buffer[i] >= 'A' && _buffer[i] <= 'Z';
		bool lowerRange = _buffer[i] >= 'a' && _buffer[i] <= 'z';
		bool numberRange = _buffer[i] >= '0' && _buffer[i] <= '9';
		if (!upperRange && !lowerRange && !numberRange) return false;
	}

	return true;
}

bool string::isEmpty() const noexcept { return _length; }

bool string::isLower() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool upperRange = _buffer[i] >= 'A' && _buffer[i] <= 'Z';
		if (upperRange) return false;
	}

	return true;
}

bool string::isNumber() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool numberRange = _buffer[i] >= '0' && _buffer[i] <= '9';
		if (!numberRange) return false;
	}

	return true;
}

bool string::isUpper() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool lowerRange = _buffer[i] >= 'a' && _buffer[i] <= 'z';
		if (lowerRange) return false;
	}

	return true;
}

const char* string::toRawString() const noexcept
{
	char* buffer = new char[_length + 1];
	std::memcpy(buffer, _buffer, _length);
	buffer[_length] = NULL;

	return buffer;
}

string string::substring(int start, int length) const
{
	if ((start + length) > _length)
		throw std::out_of_range("selection outside original string");

	char* buffer = new char[length];
	std::memcpy(buffer, _buffer + start, length);

	return string(buffer, length);
}

string string::strip() const noexcept
{
	unsigned start = 0;
	for (start; start < _length; start++)
		if (_buffer[start] != ' ' && _buffer[start] != '\n') break;

	unsigned end = _length - 1;
	for (end; end; end--)
		if (_buffer[end] != ' ' && _buffer[end] != '\n') break;

	int count = end - start + 1;
	return substring(start, count);
}

string string::strip(char c) const noexcept
{
	unsigned start = 0;
	for (start; start < _length; start++)
		if (_buffer[start] != c) break;

	unsigned end = _length - 1;
	for (end; end; end--)
		if (_buffer[end] != c) break;

	int count = end - start + 1;
	return substring(start, count);
}

string string::lstrip() const noexcept
{
	unsigned i = 0;
	for (i; i < _length; i++)
		if (_buffer[i] != ' ' && _buffer[i] != '\n') break;

	return substring(i, _length - i);
}

string string::lstrip(char c) const noexcept
{
	unsigned i = 0;
	for (i; i < _length; i++)
		if (_buffer[i] != c) break;

	return substring(i, _length - i);
}

string string::rstrip() const noexcept
{
	unsigned i = _length - 1;
	for (i; i; i--)
		if (_buffer[i] != ' ' && _buffer[i] != '\n') break;

	return substring(0, i + 1);
}

string string::rstrip(char c) const noexcept
{
	unsigned i = _length - 1;
	for (i; i; i--)
		if (_buffer[i] != c) break;

	return substring(0, i + 1);
}

string string::removeAt(int index) const
{
	if (index >= _length) throw std::out_of_range("index out of range");

	unsigned len = _length - 1;
	char* buffer = new char[len];

	std::memcpy(buffer, _buffer, index);
	std::memcpy(buffer + index, _buffer + index + 1, len - index);

	return string(buffer, len);
}

string string::removeFirst(char c) const noexcept
{
	int index = firstIndexOf(c);
	if (index == -1) return *this;

	return removeAt(index);
}

string string::removeLast(char c) const noexcept
{
	int index = lastIndexOf(c);
	if (index == -1) return *this;

	return removeAt(index);
}

string string::removeAll(char c) const noexcept
{
	int counter = count(c);
	if (!counter) return *this;

	unsigned len = _length - counter;
	char* buffer = new char[len];

	int occurence = 0;
	for (int i = 0; i < len; i++)
	{
		if (_buffer[i + occurence] == c) occurence++;
		buffer[i] = _buffer[i + occurence];
	}

	return string(buffer, len);
}

string string::replaceAt(int index, char c) const
{
	if (index >= _length) 
		throw std::out_of_range("index out of range");

	string s = *this;
	s[index] = c;

	return s;
}

string string::replaceFirst(char before, char after) const noexcept
{
	int index = firstIndexOf(before);
	if (index == -1) return *this;

	return replaceAt(index, after);
}

string string::replaceLast(char before, char after) const noexcept
{
	int index = lastIndexOf(before);
	if (index == -1) return *this;

	return replaceAt(index, after);
}

string string::replaceAll(char before, char after) const noexcept
{
	if (!contains(before)) return *this;

	string s = *this;
	for (int i = 0; i < _length; i++)
		if (s[i] == before) s[i] = after;

	return s;
}

string string::toLower() const noexcept
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _buffer[i];
		if (charAtIndex >= 'A' && charAtIndex <= 'Z')
			buffer[i] = charAtIndex - ('Z' - 'z');
		else buffer[i] = charAtIndex;
	}

	return string(buffer, _length);
}

string string::toUpper() const noexcept
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _buffer[i];
		if (charAtIndex >= 'a' && charAtIndex <= 'z')
			buffer[i] = charAtIndex - ('z' - 'Z');
		else buffer[i] = charAtIndex;
	}

	return string(buffer, _length);
}

string string::toggleCase() const noexcept
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _buffer[i];
		if (charAtIndex >= 'a' && charAtIndex <= 'z')
			buffer[i] = charAtIndex - ('z' - 'Z');
		else if (charAtIndex >= 'A' && charAtIndex <= 'Z')
			buffer[i] = charAtIndex - ('Z' - 'z');
		else buffer[i] = charAtIndex;
	}

	return string(buffer, _length);
}

std::vector<string> string::split(char c) const
{
	std::vector<string> strings;

	string s = strip(c);

	unsigned count = s.count(c);
	if (!count) return strings;

	unsigned lastIndexOf = 0;
	strings.resize(count + 1);
	count = 0;

	for (unsigned i = 0; i < _length; i++)
	{
		if (s._buffer[i] != c) continue;

		strings[count] = s.substring(lastIndexOf, i - lastIndexOf);
		lastIndexOf = i + 1;
		count++;
	}

	strings[count] = s.substring(lastIndexOf, _length - lastIndexOf);

	return strings;
}

#pragma endregion

#pragma region Static Methods

string string::empty() noexcept { return string(); }

#pragma endregion

#pragma region Operators

string& string::operator =(const string& str)
{
	if (this == &str) return *this;

	_length = str._length;

	char* buffer = new char[_length];
	std::memcpy(buffer, str._buffer, _length);
	
	_buffer = buffer;
}

string& string::operator +=(const string& str)
{
	unsigned length = _length + str._length;
	char* final_buffer = new char[length];

	std::memcpy(final_buffer, _buffer, _length);
	std::memcpy(final_buffer + _length, str._buffer, str._length);

	_length = length;
	_buffer = final_buffer;

	return *this;
}

string& string::operator *=(int n)
{
	unsigned len = _length * n;
	char* buffer = new char[len];

	for (int i = 0; i < n; i++)
		std::memcpy(buffer + i * _length, _buffer, _length);

	_length = len;
	_buffer = buffer;

	return *this;
}

char string::operator [](int index) const
{
	if (index >= _length) throw std::out_of_range("index out of range");

	return _buffer[index];
}

char& string::operator [](int index)
{
	if (index >= _length) throw std::out_of_range("index out of range");

	return _buffer[index];
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
		std::memcpy(buffer + i * str._length, str._buffer, str._length);

	return string(buffer, len);
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

std::ostream& operator <<(std::ostream& stream, const string& str)
{
	stream.write(str._buffer, str._length);
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

string::operator char* () const { return _buffer; }
string::operator const char* () const { return _buffer; }

#pragma endregion
