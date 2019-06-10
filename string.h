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

	string substring(int start, int length) const;

	string strip() const;
	string strip(char c) const;

	string lstrip() const;
	string lstrip(char c) const;

	string rstrip() const;
	string rstrip(char c) const;

	string removeAt(int index) const;
	string removeFirst(char c) const;
	string removeLast(char c) const;
	string removeAll(char c) const;

	string replaceAt(int index, char c) const;
	string replaceFirst(char before, char after) const;
	string replaceLast(char before, char after) const;
	string replaceAll(char before, char after) const;

	string toLower() const;
	string toUpper() const;
	string switchCase() const;

	int firstIndexOf(char c) const;
	int lastIndexOf(char c) const;
	int occurenciesCount(char c) const;

	unsigned length() const;

	bool contains(char c) const;
	bool contains(string str) const;

	bool isEmpty() const;

	std::vector<string> split(char c) const;

	static string empty();

	string& operator +=(const string& str);

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

	friend std::ostream& operator <<(std::ostream& stream, string& str);
	friend std::istream& operator >>(std::istream& stream, string& str);

private:

	std::shared_ptr<char> _shared_buffer;
	unsigned _length;

	string(const char* str, unsigned length); // potentially dangerous constructor
};