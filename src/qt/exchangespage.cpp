#include "exchangespage.h"
#include "ui_exchangespage.h"
#include "sync.h"
#include "bitcoinrpc.h"
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace boost;
using namespace json_spirit;

tickers_map_t mapTickers;
CCriticalSection cs_tickers;

ExchangesPage::ExchangesPage(QWidget *parent)
	: QWidget(parent), ui(new Ui::ExchangesPage)
{
	ui->setupUi(this);
	connect(ui->cbCurrentExchange, SIGNAL(currentIndexChanged(const QString & )), SLOT(changeTicker(const QString &)));
	connect(ui->btnRefresh, SIGNAL(pressed()), SLOT(refreshClicked()));
	QFuture<void> future = QtConcurrent::run(this, &ExchangesPage::Refresh);
}

void ExchangesPage::refreshClicked()
{
	QFuture<void> future = QtConcurrent::run(this, &ExchangesPage::Refresh);
}

void ExchangesPage::changeTicker(const QString & text)
{
	{
		LOCK(cs_tickers);
		tickers_map_t::iterator it = !text.isEmpty() ? mapTickers.find(text.toStdString()) : mapTickers.begin();
		if (it != mapTickers.end())
		{
			TickerEntry item = (*it).second;
			ui->lblUrl->setText(QString(("<a href=\"" + item.Url + "\">" + item.Name.c_str() + "</a>").c_str()));
			ui->lblSellPrice->setText(QString(item.SellPrice.c_str()));
			ui->lblBuyPrice->setText(QString(item.BuyPrice.c_str()));
		}
	}
}

void ExchangesPage::Refresh()
{
	try
	{
		// Download summary exchange statistics
		Object result = CallRPC("tools.blackdragoncoin.com", "81", "simpleTicker", Array());

		QString selectedItem = ui->cbCurrentExchange->currentText();
		{
			LOCK(cs_tickers);
			BOOST_FOREACH (const Config_vector<std::string>::Pair_type &obj, result)
			{
				// Parse and map the response
				map<string, Config_vector<string>::Value_type> mapParsedTickers;
				map<string, Config_vector<string>::Value_type> mapParsedResults;
				obj_to_map(obj.value_.get_obj(), mapParsedTickers);
				obj_to_map(mapParsedTickers["Result"].get_obj(), mapParsedResults);

				// Assign
				string Name = mapParsedResults["Name"].get_str();
				string Url = mapParsedResults["Url"].get_str();
				string SellPrice = str(format("%.8f") % mapParsedResults["SellPrice"].get_real());
				string BuyPrice = str(format("%.8f") % mapParsedResults["BuyPrice"].get_real());
				mapTickers[Name] = TickerEntry(Name, Url, SellPrice, BuyPrice);
			}
			if (selectedItem.isEmpty() && !mapTickers.empty())
				selectedItem = QString((*mapTickers.begin()).first.c_str());
		}

		// Update combo box
		ui->cbCurrentExchange->clear();
		BOOST_FOREACH (tickers_map_t::value_type &i, mapTickers)
		{
			ui->cbCurrentExchange->addItem(QString(i.first.c_str()));
		}
		if (!selectedItem.isEmpty() && mapTickers.find(selectedItem.toStdString()) != mapTickers.end())
		{
			ui->cbCurrentExchange->setCurrentIndex(ui->cbCurrentExchange->findText(selectedItem));
		}

		QMetaObject::invokeMethod(this, "changeTicker", Q_ARG(QString, selectedItem));
	}
	catch(...) { }
}

ExchangesPage::~ExchangesPage()
{
	delete ui;
}
