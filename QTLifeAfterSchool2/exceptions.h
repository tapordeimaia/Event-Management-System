#pragma once
#include <stdexcept>
#include <string>

class EventException : public std::runtime_error {
public:
	explicit EventException(const std::string& msg) : std::runtime_error(msg) {}
};

class RepositoryException : public std::runtime_error {
public:
	explicit RepositoryException(const std::string& msg) : std::runtime_error(msg) {}
};

class ValidationException : public std::runtime_error {
public:
	explicit ValidationException(const std::string& msg) : std::runtime_error(msg) {}
};

class FileException : public std::runtime_error {
public:
	explicit FileException(const std::string& msg) : std::runtime_error(msg) {}
};
