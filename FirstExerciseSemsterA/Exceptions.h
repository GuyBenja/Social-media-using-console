#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>

class UnrecognizeCharException : public std::exception
{//this class is a class exception for char validation
private:

	std::string m_str;

public:
	UnrecognizeCharException(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};

class DateException : public std::exception
{//this class is a class exception for date  validation
private:

	std::string m_str;

public:
	DateException(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};

class StatusException : public std::exception
{//this class is a class exception for status  validation
private:

	std::string m_str;

public:
	StatusException(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};
class PathException : public std::exception
{//this class is a class exception for path validation
private:

	std::string m_str;

public:
	PathException(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};

class NameException : public std::exception
{//this class is a class exception for name validation
private:

	std::string m_str;

public:
	NameException(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};

class FriendshipExceptions : public std::exception
{//this class is a class exception for friendship validation
private:

	std::string m_str;

public:
	FriendshipExceptions(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};

class UserException : public std::exception
{//this class is a class exception for user validation
private:

	std::string m_str;

public:
	UserException(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};

class FanPageException : public std::exception
{//this class is a class exception for fan page validation
private:

	std::string m_str;

public:
	FanPageException(const std::string& s) :m_str(s) {}
	char const* what()const override { return m_str.c_str(); }
};

#endif // !EXCEPTIONS_H
