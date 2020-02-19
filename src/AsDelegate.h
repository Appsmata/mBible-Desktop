#ifndef ASDELEGATE_H
#define ASDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>

class AsDelegate : public QStyledItemDelegate
{
	Q_OBJECT
		signals :

public:
	explicit AsDelegate(QObject* parent = nullptr);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

	~AsDelegate();
};

#endif ASDELEGATE_H
