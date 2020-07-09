#include <cstring>
#include <stdexcept>
#include <memory>

#include "String.h"

String::String() : _buffer(nullptr), _length(0) {}

String::String(char c) : _length(1)
{
	char* buffer = new char[1];
	buffer[0] = c;

	_buffer = buffer;
}

String::String(char* chars, unsigned length) : _buffer(chars), _length(length) {}

String::String(const char* string)
{
	if (!string)
	{
		_length = 0;
		_buffer = nullptr;
		return;
	}

	_length = std::strlen(string);

	char* buffer = new char[_length];
	std::memcpy(buffer, string, _length);

	_buffer = buffer;
}

String::String(const String& string) : _length(string._length)
{
	char* buffer = new char[_length];
	std::memcpy(buffer, string._buffer, _length);

	_buffer = buffer;
}

String::~String()
{
	delete[] _buffer;
}

int String::Count(char c) const noexcept
{
	int count = 0;
	for (int i = 0; i < _length; i++)
		if (_buffer[i] == c) count++;

	return count;
}

int String::FirstIndexOf(char c) const noexcept
{
	for (int i = 0; i < _length; i++)
		if (_buffer[i] == c) return i;

	return -1;
}

int String::LastIndexOf(char c) const noexcept
{
	for (int i = _length - 1; i; i--)
		if (_buffer[i] == c) return i;

	return -1;
}

unsigned String::Length() const noexcept { return _length; }

bool String::Contains(char c) const noexcept
{
	for (int i = 0; i < _length; i++)
		if (_buffer[i] == c) return true;

	return false;
}

bool String::Contains(const String& string) const noexcept
{
	if (string._length > _length) return false;

	int gap = _length - string._length;
	for (int i = 0; i <= gap; i++)
	{
		if (_buffer[i] != string[0]) continue;

		int j;
		for (j = 1; j < string._length; j++)
			if (_buffer[i + j] != string[j]) break;

		if (j == string._length) return true;
	}

	return false;
}

bool String::IsAlphabet() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool upperRange = 'A' <= _buffer[i] && _buffer[i] <= 'Z';
		bool lowerRange = 'a' <= _buffer[i] && _buffer[i] <= 'z';
		if (!upperRange && !lowerRange) return false;
	}

	return true;
}

bool String::IsAlphanum() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool upperRange = 'A' <= _buffer[i] && _buffer[i] <= 'Z';
		bool lowerRange = 'a' <= _buffer[i] && _buffer[i] <= 'z';
		bool numberRange = '0' <= _buffer[i] && _buffer[i] <= '9';
		if (!upperRange && !lowerRange && !numberRange) return false;
	}

	return true;
}

bool String::IsEmpty() const noexcept { return _length; }

bool String::IsLower() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool upperRange = 'A' <= _buffer[i] && _buffer[i] <= 'Z';
		if (upperRange) return false;
	}

	return true;
}

bool String::IsNumber() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool numberRange = '0' <= _buffer[i] && _buffer[i] <= '9';
		if (!numberRange) return false;
	}

	return true;
}

bool String::IsUpper() const noexcept
{
	for (int i = 0; i < _length; i++)
	{
		bool lowerRange = 'a' <= _buffer[i] && _buffer[i] <= 'z';
		if (lowerRange) return false;
	}

	return true;
}

const char* String::ToRawString() const noexcept
{
	char* buffer = new char[_length + 1];
	std::memcpy(buffer, _buffer, _length);
	buffer[_length] = '\0';

	return buffer;
}

String String::Substring(int start, int length) const
{
	if ((start + length) > _length)
		throw std::out_of_range("Selection outside original string.");

	char* buffer = new char[length];
	std::memcpy(buffer, _buffer + start, length);

	return String(buffer, length);
}

String String::Strip() const noexcept
{
	unsigned start = 0;
	for (start; start < _length; start++)
		if (_buffer[start] != ' ' && _buffer[start] != '\n') break;

	unsigned end = _length - 1;
	for (end; end; end--)
		if (_buffer[end] != ' ' && _buffer[end] != '\n') break;

	int count = end - start + 1;
	return Substring(start, count);
}

String String::Strip(char c) const noexcept
{
	unsigned start = 0;
	for (start; start < _length; start++)
		if (_buffer[start] != c) break;

	unsigned end = _length - 1;
	for (end; end; end--)
		if (_buffer[end] != c) break;

	int count = end - start + 1;
	return Substring(start, count);
}

String String::Lstrip() const noexcept
{
	unsigned i = 0;
	for (i; i < _length; i++)
		if (_buffer[i] != ' ' && _buffer[i] != '\n') break;

	return Substring(i, _length - i);
}

String String::Lstrip(char c) const noexcept
{
	unsigned i = 0;
	for (i; i < _length; i++)
		if (_buffer[i] != c) break;

	return Substring(i, _length - i);
}

String String::Rstrip() const noexcept
{
	unsigned i = _length - 1;
	for (i; i; i--)
		if (_buffer[i] != ' ' && _buffer[i] != '\n') break;

	return Substring(0, i + 1);
}

String String::Rstrip(char c) const noexcept
{
	unsigned i = _length - 1;
	for (i; i; i--)
		if (_buffer[i] != c) break;

	return Substring(0, i + 1);
}

String String::RemoveAt(int index) const
{
	if (index >= _length) throw std::out_of_range("index out of range");

	unsigned len = _length - 1;
	char* buffer = new char[len];

	std::memcpy(buffer, _buffer, index);
	std::memcpy(buffer + index, _buffer + index + 1, len - index);

	return String(buffer, len);
}

String String::RemoveFirst(char c) const noexcept
{
	int index = FirstIndexOf(c);
	if (index == -1) return *this;

	return RemoveAt(index);
}

String String::RemoveLast(char c) const noexcept
{
	int index = LastIndexOf(c);
	if (index == -1) return *this;

	return RemoveAt(index);
}

String String::RemoveAll(char c) const noexcept
{
	int counter = Count(c);
	if (!counter) return *this;

	unsigned len = _length - counter;
	char* buffer = new char[len];

	int occurence = 0;
	for (int i = 0; i < len; i++)
	{
		if (_buffer[i + occurence] == c) occurence++;
		buffer[i] = _buffer[i + occurence];
	}

	return String(buffer, len);
}

String String::ReplaceAt(int index, char c) const
{
	if (index >= _length) 
		throw std::out_of_range("index out of range");

	String s = *this;
	s[index] = c;

	return s;
}

String String::ReplaceFirst(char before, char after) const noexcept
{
	int index = FirstIndexOf(before);
	if (index == -1) return *this;

	return ReplaceAt(index, after);
}

String String::ReplaceLast(char before, char after) const noexcept
{
	int index = LastIndexOf(before);
	if (index == -1) return *this;

	return ReplaceAt(index, after);
}

String String::ReplaceAll(char before, char after) const noexcept
{
	String s = *this;

	for (int i = 0; i < _length; i++)
		if (s[i] == before) s[i] = after;

	return s;
}

String String::ToLower() const noexcept
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _buffer[i];
		if (charAtIndex >= 'A' && charAtIndex <= 'Z')
			buffer[i] = charAtIndex - ('Z' - 'z');
		else buffer[i] = charAtIndex;
	}

	return String(buffer, _length);
}

String String::ToUpper() const noexcept
{
	char* buffer = new char[_length];
	for (int i = 0; i < _length; i++)
	{
		char charAtIndex = _buffer[i];
		if (charAtIndex >= 'a' && charAtIndex <= 'z')
			buffer[i] = charAtIndex - ('z' - 'Z');
		else buffer[i] = charAtIndex;
	}

	return String(buffer, _length);
}

String String::ToggleCase() const noexcept
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

	return String(buffer, _length);
}

std::vector<String> String::Split(char c) const
{
	std::vector<String> strings;

	String s = Strip(c);

	unsigned count = s.Count(c);
	if (!count) return strings;

	unsigned lastIndexOf = 0;
	strings.resize(count + 1);

	count = 0;
	for (unsigned i = 0; i < _length; i++)
	{
		if (s._buffer[i] != c) continue;

		strings[count] = s.Substring(lastIndexOf, i - lastIndexOf);
		lastIndexOf = i + 1;
		count++;
	}

	strings[count] = s.Substring(lastIndexOf, _length - lastIndexOf);

	return strings;
}

const String& String::Empty() noexcept 
{ 
	static String s;
	static bool init = false;
	if (!init) { s = String(); }
	return s;
}

String& String::operator =(const String& string)
{
	if (this == &string) return *this;

	_length = string._length;

	char* buffer = new char[_length];
	std::memcpy(buffer, string._buffer, _length);
	
	delete[] _buffer;
	_buffer = buffer;
}

String& String::operator +=(const String& string)
{
	unsigned length = _length + string._length;
	char* finalBuffer = new char[length];

	std::memcpy(finalBuffer, _buffer, _length);
	std::memcpy(finalBuffer + _length, string._buffer, string._length);

	_length = length;

	delete[] _buffer;
	_buffer = finalBuffer;

	return *this;
}

String& String::operator *=(int n)
{
	unsigned len = _length * n;
	char* buffer = new char[len];

	for (int i = 0; i < n; i++)
		std::memcpy(buffer + i * _length, _buffer, _length);

	_length = len;

	delete[] _buffer;
	_buffer = buffer;

	return *this;
}

char String::operator [](int index) const
{
	if (index >= _length) throw std::out_of_range("Index out of range.");

	return _buffer[index];
}

char& String::operator [](int index)
{
	if (index >= _length) throw std::out_of_range("Index out of range.");

	return _buffer[index];
}

String operator +(const String& a, const String& b) { return String(a) += b; }
String operator +(const String& a, char b) { return String(a) += String(b); }
String operator +(char a, const String& b) { return String(a) += b; }
String operator +(const String& a, const char* b) { return String(a) += String(b); }
String operator +(const char* a, const String& b) { return String(a) += b; }

String operator *(const String& string, unsigned n)
{
	unsigned len = string._length * n;
	char* buffer = new char[len];

	for (int i = 0; i < n; i++)
		std::memcpy(buffer + i * string._length, string._buffer, string._length);

	return string(buffer, len);
}

String operator *(unsigned n, const String& str) { return str * n; }

bool operator ==(const String& a, const String& b)
{
	if (a._length != b._length) return false;

	for (unsigned i = 0; i < a._length; i++)
		if (a[i] != b[i]) return false;

	return true;
}

bool operator ==(const String& a, const char* b)
{
	if (a._length != std::strlen(b)) return false;

	for (unsigned i = 0; i < a._length; i++)
		if (a[i] != b[i]) return false;

	return true;
}

bool operator ==(const char* a, const String& b)
{
	return b == a;
}

bool operator ==(const String& string, char c)
{
	if (string._length != 1) return false;
	return (string[0] == c) ? true : false;
}

bool operator ==(char c, const String& string) { return string == c; }

bool operator !=(const String& a, const String& b) { return !(a == b); }
bool operator !=(const String& a, const char* b) { return !(a == b); }
bool operator !=(const char* a, const String& b) { return !(a == b); }
bool operator !=(const String& string, char c) { return !(string == c); }
bool operator !=(char c, const String& string) { return !(string == c); }

std::ostream& operator <<(std::ostream& stream, const string& str)
{
	stream.write(str._buffer, str._length);
	return stream;
}

std::istream& operator >>(std::istream& stream, String& string)
{
	char* c = new char[512];
	stream >> c;

	string = String(c);
	delete[] c;

	return stream;
}

String::operator char* () const { return _buffer; }
String::operator const char* () const { return _buffer; }