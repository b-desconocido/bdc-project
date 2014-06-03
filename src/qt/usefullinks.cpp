#include "usefullinks.h"
#include "ui_usefullinks.h"
#include <QDesktopServices>
#include <QUrl>

UsefulLinks::UsefulLinks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsefulLinks)
{
    ui->setupUi(this);

	/* Don't want to create custom class/signal mapper for 3 signals */
	connect(ui->btnFacebook, SIGNAL(clicked()), SLOT(openFacebook()));
	connect(ui->btnReddit, SIGNAL(clicked()), SLOT(openReddit()));
	connect(ui->btnTwitter, SIGNAL(clicked()), SLOT(openTwitter()));
}

UsefulLinks::~UsefulLinks()
{
    delete ui;
}

void UsefulLinks::openFacebook()
{
	 QDesktopServices::openUrl(QUrl("https://www.facebook.com/pages/Black-Dragon-Coin/1471669706384394", QUrl::TolerantMode));
}

void UsefulLinks::openReddit()
{
	 QDesktopServices::openUrl(QUrl("http://www.reddit.com/r/BlackDragonCoin/", QUrl::TolerantMode));
}

void UsefulLinks::openTwitter()
{
	 QDesktopServices::openUrl(QUrl("https://twitter.com/BlackDragonCoin", QUrl::TolerantMode));
}
