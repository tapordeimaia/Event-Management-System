#pragma once
#include "event.h"
#include <vector>
#include <fstream>
#include <memory>
#include "exceptions.h"
#include <windows.h> 
#include <iomanip>

class FileExporter {
public:
	virtual ~FileExporter() = default;
	virtual void exportEvents(const std::vector<Event>& events, const std::string& filename) = 0;
	virtual void display(const std::string& filename) = 0;
};

class CSVExporter : public FileExporter {
public: 
	void exportEvents(const std::vector<Event>& events, const std::string& filename) override {
		
		std::ofstream file(filename);
		if (!file.is_open()) {
			throw FileException("Could not open file for writing" + filename);
		}
		for (const auto& event : events) {
			auto time = std::mktime(const_cast<std::tm*>(&event.getDateTime()));
			tm localTime;
			localtime_s(&localTime, &time); 
			file << "\"" << event.getTitle() << "\";"
				<< "\"" << event.getDescription() << "\";"
				<< "\"" << std::put_time(&localTime, "%Y-%m-%d %H:%M") << "\";"
				<< "\"" << event.getAttendees() << "\";"
				<< "\"" << event.getLink() << "\n";
		}
	}

	void display(const std::string& filename) override {
#ifdef _WIN32
		std::string command = "Excel /e " + filename;
		if (system(command.c_str())) {
			// Fallback to default opening if specific Excel command fails
			ShellExecuteA(nullptr, "open", filename.c_str(), nullptr, nullptr, SW_SHOW);
		}
#else
		std::string command = "xdg-open " + filename;
		system(command.c_str());
#endif
	}
};

class HTMLExporter : public FileExporter {
public:
	void exportEvents(const std::vector<Event>& events, const std::string& filename) override {
		std::ofstream file(filename);
		if (!file.is_open()) {
			throw FileException("Could not open file for writing" + filename);
		}
		file << "<!DOCTYPE html>\n"
			<< "<html>\n"
			<< "<head>\n"
			<< "    <title>Event List</title>\n"
			<< "</head>\n"
			<< "<body>\n"
			<< "<table border=\"1\">\n"
			<< "    <tr>\n"
			<< "        <td>Title</td>\n"
			<< "        <td>Description</td>\n"
			<< "        <td>Date</td>\n"
			<< "        <td>Attendees</td>\n"
			<< "        <td>Link</td>\n"
			<< "      </tr>\n";
		for (const auto& event : events) {
			auto time = std::mktime(const_cast<std::tm*>(&event.getDateTime()));
			tm localTime;
			localtime_s(&localTime, &time);
			file << "    <tr>\n"
				<< "          <td>" << event.getTitle() << "</td>\n"
				<< "          <td>" << event.getDescription() << "</td>\n"
				<< "          <td>" << std::put_time(&localTime, "%Y-%m-%d &H:&M") << "/td>\n"
				<< "          <td>" << event.getAttendees() << "</td>\n"
				<< "          <td><a href=\"" << event.getLink() << "\">Link</a></td>\n"
				<< "      </tr>\n";
		}
		file << "</table>\n"
			<< "</body>\n"
			<< "</html>\n";
	}

	void display(const std::string& filename) override {
#ifdef _WIN32
		ShellExecuteA(nullptr, "open", filename.c_str(), nullptr, nullptr, SW_SHOW);
#else
		std::string command = "xdg-open " + filename;
		system(command.c_str());
#endif
	}
};

class ExporterFactory {
public:
	static std::unique_ptr<FileExporter> createExporter(const std::string& type) {
		if (type == "csv") {
			return std::make_unique<CSVExporter>();
		}
		else if (type == "html") {
			std::cout << "HTML Exporter created\n";
			return std::make_unique<HTMLExporter>();
		}
		throw FileException("Invalid exporter type: " + type);
	}
};

