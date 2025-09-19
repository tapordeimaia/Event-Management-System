#include "GUI.h"
#include <QString>
#include "AdminMenu.h"
#include "UserMenu.h"
#include <QFont>
#include <QLabel>

GUI::GUI(EventService& service, EventRepository& repo, QWidget* parent) : QWidget(parent), service(service), userService(repo)
{
	setupUI();
}

GUI::~GUI()
{
}

void GUI::setupUI()
{
	this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);");

	auto* mainLayout = new QVBoxLayout(this);
	QLabel* titleLabel = new QLabel("Event Management System");
	QFont titleFont;
	titleFont.setPointSize(24);
	titleFont.setBold(true);
	titleFont.setFamily("Arial");
	titleLabel->setFont(titleFont);
	titleLabel->setStyleSheet("color: white;");
	titleLabel->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(titleLabel);

	auto* buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();

	adminButton = new QPushButton("Admin Menu", this);
	adminButton->setFixedSize(200, 55);
	connect(adminButton, &QPushButton::clicked, this, &GUI::adminMenu);

	QFont buttonFont = adminButton->font();
	buttonFont.setPointSize(16);
	buttonFont.setBold(true);
	adminButton->setFont(buttonFont);
	buttonLayout->addWidget(adminButton);

	buttonLayout->addSpacing(40);

	userButton = new QPushButton("User Menu", this);
	userButton->setFixedSize(200, 55);
	connect(userButton, &QPushButton::clicked, this, &GUI::userMenu);
	userButton->setFont(buttonFont);
	buttonLayout->addWidget(userButton);

	buttonLayout->addStretch();

	mainLayout->addSpacing(150);
	mainLayout->addLayout(buttonLayout);
	mainLayout->addStretch();

	closeButton = new QPushButton("Close", this);
	closeButton->setFixedSize(100, 30);
	connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
	mainLayout->addWidget(closeButton, 0, Qt::AlignHCenter);
	setLayout(mainLayout);

}

void GUI::adminMenu()
{
	AdminMenu* adminWindow = new AdminMenu(service);
	adminWindow->show();
}

void GUI::userMenu()
{
	UserMenu* userWindow = new UserMenu(userService);
	userWindow->show();
}