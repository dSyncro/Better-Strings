#pragma once

#include <iostream>
#include <vector>

struct IStringable
{
	virtual void ToString() = 0;
};

class String
{
public:

	String();
	String(char c);
	String(const char* string);
	String(const String& string);
	~String();

	int Count(char c) const noexcept;
	int FirstIndexOf(char c) const noexcept;
	int LastIndexOf(char c) const noexcept;

	unsigned Length() const noexcept;

	bool Contains(char c) const noexcept;
	bool Contains(const String& string) const noexcept;

	bool IsAlphabet() const noexcept;
	bool IsAlphanum() const noexcept;
	bool IsEmpty() const noexcept;
	bool IsLower() const noexcept;
	bool IsNumber() const noexcept;
	bool IsUpper() const noexcept;

	const char* ToRawString() const noexcept;

	String Substring(int start, int length) const;

	String Strip() const noexcept;
	String Strip(char c) const noexcept;

	String Lstrip() const noexcept;
	String Lstrip(char c) const noexcept;

	String Rstrip() const noexcept;
	String Rstrip(char c) const noexcept;

	String RemoveAt(int index) const;
	String RemoveFirst(char c) const noexcept;
	String RemoveLast(char c) const noexcept;
	String RemoveAll(char c) const noexcept;

	String ReplaceAt(int index, char c) const;
	String ReplaceFirst(char before, char after) const noexcept;
	String ReplaceLast(char before, char after) const noexcept;
	String ReplaceAll(char before, char after) const noexcept;

	String ToLower() const noexcept;
	String ToUpper() const noexcept;
	String ToggleCase() const noexcept;

	std::vector<String> Split(char c) const;

	static const String& Empty() noexcept;

	String& operator =(const String& string);
	String& operator +=(const String& string);
	String& operator *=(int n);

	char operator[](int index) const;
	char& operator[](int index);

	explicit operator char* () const;
	explicit operator const char*() const;

	friend String operator +(const String& a, const String& b);
	friend String operator +(const String& a, char b);
	friend String operator +(char a, const String& b);
	friend String operator +(const String& a, const char* b);
	friend String operator +(const char* a, const String& b);

	friend String operator *(const String& str, unsigned n);
	friend String operator *(unsigned n, const String& string);

	friend bool operator ==(const String& a, const String& b);
	friend bool operator ==(const String& a, const char* b);
	friend bool operator ==(const char* a, const String& b);
	friend bool operator ==(const String& str, char c);
	friend bool operator ==(char c, const String& string);

	friend bool operator !=(const String& a, const String& b);
	friend bool operator !=(const String& a, const char* b);
	friend bool operator !=(const char* a, const String& b);
	friend bool operator !=(const String& str, char c);
	friend bool operator !=(char c, const String& str);

	friend std::ostream& operator <<(std::ostream& stream, const String& string);
	friend std::istream& operator >>(std::istream& stream, String& string);

private:

	char* _buffer;
	unsigned _length;

	String(char* chars, unsigned length); // potentially dangerous constructor, meant for internal use
};