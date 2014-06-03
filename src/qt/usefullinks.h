#ifndef USEFULLINKS_H
#define USEFULLINKS_H

#include <QWidget>
#include <string>

namespace Ui {
class UsefulLinks;
}

class UsefulLinks : public QWidget
{
    Q_OBJECT

public:
    explicit UsefulLinks(QWidget *parent = 0);
    ~UsefulLinks();

private slots:
	void openFacebook();
	void openReddit();
	void openTwitter();

private:
    Ui::UsefulLinks *ui;
};

#endif // USEFULLLINKS_H
