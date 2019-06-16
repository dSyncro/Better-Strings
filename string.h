#pragma once

#include <iostream>
#include <vector>
#include <memory>

struct IStringable
{
	virtual void toString() = 0;
};

class string
{
public:

	string();
	string(char c);
	string(char* chars);
	string(const char* string);
	string(const string& str);
	~string();

	int count(char c) const noexcept;
	int firstIndexOf(char c) const noexcept;
	int lastIndexOf(char c) const noexcept;

	unsigned length() const noexcept;

	bool contains(char c) const noexcept;
	bool contains(string str) const noexcept;

	bool isAlphabet() const noexcept;
	bool isAlphanum() const noexcept;
	bool isEmpty() const noexcept;
	bool isLower() const noexcept;
	bool isNumber() const noexcept;
	bool isUpper() const noexcept;

	const char* toRawString() const noexcept;

	string substring(int start, int length) const;

	string strip() const noexcept;
	string strip(char c) const noexcept;

	string lstrip() const noexcept;
	string lstrip(char c) const noexcept;

	string rstrip() const noexcept;
	string rstrip(char c) const noexcept;

	string removeAt(int index) const;
	string removeFirst(char c) const noexcept;
	string removeLast(char c) const noexcept;
	string removeAll(char c) const noexcept;

	string replaceAt(int index, char c) const;
	string replaceFirst(char before, char after) const noexcept;
	string replaceLast(char before, char after) const noexcept;
	string replaceAll(char before, char after) const noexcept;

	string toLower() const noexcept;
	string toUpper() const noexcept;
	string toggleCase() const noexcept;

	std::vector<string> split(char c) const;

	static string empty() noexcept;

	string& operator =(const string& str);
	string& operator +=(const string& str);
	string& operator *=(int n);

	char operator[](int index) const;
	char& operator[](int index);

	explicit operator char* () const;
	explicit operator const char*() const;

	friend string operator +(const string& a, const string& b);
	friend string operator +(const string& a, char b);
	friend string operator +(char a, const string& b);
	friend string operator +(const string& a, const char* b);
	friend string operator +(const char* a, const string& b);

	friend string operator *(const string& str, unsigned n);
	friend string operator *(unsigned n, const string& str);

	friend bool operator ==(const string& a, const string& b);
	friend bool operator ==(const string& a, const char* b);
	friend bool operator ==(const char* a, const string& b);
	friend bool operator ==(const string& str, char c);
	friend bool operator ==(char c, const string& str);

	friend bool operator !=(const string& a, const string& b);
	friend bool operator !=(const string& a, const char* b);
	friend bool operator !=(const char* a, const string& b);
	friend bool operator !=(const string& str, char c);
	friend bool operator !=(char c, const string& str);

	friend std::ostream& operator <<(std::ostream& stream, const string& str);
	friend std::istream& operator >>(std::istream& stream, string& str);

private:

	char* _buffer;
	unsigned _length;

	string(char* chars, unsigned length); // potentially dangerous constructor, meant for internal use
};