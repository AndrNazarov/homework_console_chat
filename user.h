#pragma once
#include<string>

class User
{
	const std::string _login;
	std::string _passsword;
	std::string _name;

public:
	User(const std::string& login, const std::string& password, const std::string& name)
		: _login(login), _passsword(password), _name(name) {}

	const std::string& getUserLogin() const { return _login; }

	const std::string& getUserPassword() const { return _passsword; }
	void setUserPassword(const std::string& password) { _passsword = password; }

	const std::string& getUserName() const { return _name; }
	void setUserName(const std::string& name) { _name = name; }
};
