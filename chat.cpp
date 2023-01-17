#include<iostream>
#include"chat.h"

void Chat::start()
{
	_isChatWork = true;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : _userList)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
	}

	return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
	for (auto& user : _userList)
	{
		if (name == user.getUserName())
			return std::make_shared<User>(user);
	}

	return nullptr;
}

void Chat::login()
{
	std::string login, password;
	char operation;

	do
	{
		std::cout << "login: ";
		std::cin >> login;
		std::cout << "password: ";
		std::cin >> password;

		_currentUser = getUserByLogin(login);

		if (_currentUser == nullptr || (password != _currentUser->getUserPassword()))
		{
			_currentUser = nullptr;

			std::cout << "login failed!" << std::endl;
			std::cout << "(0)for exit or any key repeat: ";
			std::cin >> operation;

			if (operation == '0')
				break;
		}

	} while (!_currentUser);
}

void Chat::signUp()
{
	std::string login;
	std::string password;
	std::string name;

	std::cout << "login: ";
	std::cin >> login;
	std::cout << "password: ";
	std::cin >> password;
	std::cout << "name: ";
	std::cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	_userList.push_back(user);
	_currentUser = std::make_shared<User>(user);
}

void Chat::showChat() const
{
	std::string from;
	std::string to;

	std::cout << "=*=*=CHAT=*=*=" << std::endl;

	for (auto& mess : _messageList)
	{
		//показываем сообщения: от текущего пользователя, для него и для всех
		if (_currentUser->getUserLogin() == mess.getFrom() || _currentUser->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			//подменяем для себя имя на me
			from = (_currentUser->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (_currentUser->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();
			}

			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "text: " << mess.getText() << std::endl;
		}
	}

	std::cout << "-------------" << std::endl;
}

void Chat::showLoginMenu()
{
	_currentUser = nullptr;

	char operation;

	do
	{
		std::cout << "(1)Login" << std::endl;
		std::cout << "(2)SignUp" << std::endl;
		std::cout << "(0)ShutDown" << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '0':
			_isChatWork = false;
			break;
		default:
			std::cout << "1 or 2..." << std::endl;
			break;
		}

	} while (!_currentUser && _isChatWork);
}

void Chat::showUserMenu()
{
	char operation;

	std::cout << "Hi, " << _currentUser->getUserName() << std::endl;

	while (_currentUser)
	{
		std::cout << "Menu: (1)Show Chat | (2)Add message | (3)Users | (0)Logout " << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "Unknown choice!" << std::endl;
			break;
		}
	}
}

void Chat::showAllUsersName() const
{
	std::cout << "=*=*= Users =*=*=" << std::endl;

	for (auto& user : _userList)
	{
		std::cout << user.getUserName();

		if (_currentUser->getUserLogin() == user.getUserLogin())
			std::cout << "me" << std::endl;
	}
	std::cout << "=================" << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;

	std::cout << "To (name or all): ";
	std::cin >> to;
	std::cout << "Text: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || getUserByName(to)))  //если не удалось найти получателя по имени
	{
		std::cout << "error send message: can't find " << std::endl;
		return;
	}

	if (to == "all")
		_messageList.push_back(Message{ _currentUser->getUserLogin(), "all", text });
	else
		_messageList.push_back(Message{ _currentUser->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}