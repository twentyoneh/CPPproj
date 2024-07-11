#pragma once
#include <cstring>

class String
{
public:
	String(const char*, unsigned);
	String();
	~String();

	String(const String&);
	String(String&&);
	String& operator=(const String&);
	String& operator=(String&&);

	char* GetText() const;
	unsigned GetSize() const;
	void SetText(char*);
	void SetSize(unsigned);

private:
	char* m_Text{nullptr};
	unsigned m_Size{0};
};

