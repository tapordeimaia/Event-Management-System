#include <QApplication>
#include "EventService.h"
#include "EventRepository.h"
#include "GUI.h"
#include "Event.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	EventRepository repo;
	EventService service(repo);

	GUI gui(service, repo);
	gui.setWindowTitle("Event Management System");
	gui.resize(800, 600);
	gui.show();

	return app.exec();
}
