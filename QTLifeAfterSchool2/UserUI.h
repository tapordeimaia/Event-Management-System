#pragma once
#include "UserService.h"
#include <string>

class UserUI {
private:
	UserService& service;

	void displayMenu();
	void handleBrowseEvents();
	void handleShowInterested();
	void handleRemoveInterested();
	
	std::tm getDateTimeInput();

public:
	UserUI(UserService& service);
	void run();
};