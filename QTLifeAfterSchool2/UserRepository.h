#pragma once
#include "Event.h"
#include <vector>
#include <algorithm>
#include <FileExporter.h>

class UserRepository {
private:
	std::vector<Event> interestedEvents;
	std::unique_ptr<FileExporter> exporter;
	std::string exportType;
public:
	UserRepository() = default;
	~UserRepository() = default;

	// Disallow copying
	UserRepository(const UserRepository&) = delete;
	UserRepository& operator=(const UserRepository&) = delete;

	// Allow moving
	UserRepository(UserRepository&&) = default;
	UserRepository& operator=(UserRepository&&) = default;

	std::string getExportType() const {
		return exportType;
	}

	void setExportType(const std::string& type) {
		exportType = type;
		exporter = ExporterFactory::createExporter(type);
	}

	void addEvent(const Event& event);
	void removeEvent(const Event& event);

	const std::vector<Event>& getInterestedEvents() const;
	bool isEventInList(const Event& event) const;

	void exportToFile(const std::string& filename) {
		if (!exporter) {
			exporter = ExporterFactory::createExporter(exportType);
		}
		exporter->exportEvents(interestedEvents, filename);
	}

	void displayExportedFile(const std::string& filename) {
		if (!exporter) {
			exporter = ExporterFactory::createExporter(exportType);
		}
		exporter->display(filename);
	}
};