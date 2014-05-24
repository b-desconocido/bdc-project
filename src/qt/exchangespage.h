#ifndef EXCHANGESPAGE_H
#define EXCHANGESPAGE_H

#include <QWidget>
#include <QObject>
#include <QAction>
#include <string>
#include <map>

#undef foreach

namespace Ui {
class ExchangesPage;
}
class ExchangesPage :
	public QWidget
{
	Q_OBJECT

public:
	explicit ExchangesPage(QWidget *parent = 0);
    ~ExchangesPage();

	void Refresh();
public slots:
	void changeTicker(const QString & text);
	void refreshClicked();
private:
    Ui::ExchangesPage *ui;
};

class TickerEntry
{
	static const QUrl updateUrl;
public:
	std::string Name;
	std::string Url;
	std::string SellPrice;
	std::string BuyPrice;
	TickerEntry(std::string name, std::string url, std::string sellPrice, std::string buyPrice)
		: Name(name), Url(url), SellPrice(sellPrice), BuyPrice(buyPrice)
	{
	}
	TickerEntry()
		: Name(""), Url(""), SellPrice(""), BuyPrice("")
	{
	}
	~TickerEntry(){}
	TickerEntry& operator=(const TickerEntry& other)
	{
		Name = other.Name;
		Url = other.Url;
		SellPrice = other.SellPrice;
		BuyPrice = other.BuyPrice;
		return *this;
	}
};

typedef std::map<std::string, TickerEntry> tickers_map_t;

extern tickers_map_t mapTickers;
#endif

