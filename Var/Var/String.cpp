#include"String.h"


String::String(const char* text, unsigned size) :
	m_Text(text ? new char[size + 1] : nullptr),
	m_Size{size}
{
	if (m_Text)
	{
		std::strncpy(m_Text, text, size);
		m_Text[size] = '\0';
	}
}

String::String() : m_Text{ nullptr }, m_Size {0} {}



String::~String()
{
	if (m_Text) {
		delete[] m_Text;
	}
}

String::String(const String& other) : m_Size{other.m_Size}
{
	if (other.m_Text)
	{
		m_Text = new char[m_Size + 1];
		std::strncpy(m_Text, other.m_Text, m_Size);
		m_Text[m_Size] = '\0';
	}

}

String::String(String&& other) : m_Text{other.m_Text}, m_Size{other.m_Size}
{
	other.m_Text = nullptr;
	other.m_Size = 0;
}

String& String::operator=(const String& other)
{
	if (this != &other) 
	{
		delete[] m_Text;
		m_Size = other.m_Size;
		m_Text = new char[m_Size + 1];
		std::strncpy(m_Text, other.m_Text, m_Size);
		m_Text[m_Size] = '\0';
	}
	return *this;
}

String& String::operator=(String&& other)
{
	if (this != &other)
	{
		delete[] m_Text;
		m_Size = other.m_Size;
		m_Text = other.m_Text;
		other.m_Text = nullptr;
		other.m_Size = 0;
	}
	return *this;
}

char* String::GetText() const
{
	return m_Text;
}

unsigned String::GetSize() const
{
	return m_Size;
}

void String::SetText(char* text)
{
	m_Text = text;
}

void String::SetSize(unsigned size)
{
	m_Size = size;
}
