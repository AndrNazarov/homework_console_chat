#pragma once
#include<vector>
#include<memory>
#include<exception>
#include"message.h"

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "User login is busy!"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "User name is busy!"; }
};

class Chat
{
	bool _isChatWork = false;
	std::vector<User> _userList;
	std::vector<Message> _messageList;
	std::shared_ptr<User> _currentUser = nullptr;

	void login();
	void signUp();
	void showChat() const;
	void showAllUsersName() const;
	void addMessage();
	std::vector<User>& getAllUsers() { return _userList; }
	std::vector<Message>& getAllMessages() { return _messageList; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;

public:
	void start();
	bool isChatWork() const { return _isChatWork; }
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; }
	void showLoginMenu();
	void showUserMenu();
};