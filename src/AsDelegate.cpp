#include "AsDelegate.h"
#include "AsItem.h"

#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyle>
#include <QEvent>
#include <QDebug>

AsDelegate::AsDelegate(QObject* parent) :
	QStyledItemDelegate(parent)
{ }

AsDelegate::~AsDelegate()
{

}

void AsDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.isValid()) {
		painter->save();
		QVariant var = index.data(Qt::UserRole + 1);
		AsItem item = var.value<AsItem>();

		// item Rectangular area
		QRectF rect;
		rect.setX(option.rect.x());
		rect.setY(option.rect.y());
		rect.setWidth(option.rect.width() - 1);
		rect.setHeight(option.rect.height() - 1);

		QPainterPath path;
		path.moveTo(rect.topRight());
		path.lineTo(rect.topLeft());
		path.quadTo(rect.topLeft(), rect.topLeft());
		path.lineTo(rect.bottomLeft());
		path.quadTo(rect.bottomLeft(), rect.bottomLeft());
		path.lineTo(rect.bottomRight());
		path.quadTo(rect.bottomRight(), rect.bottomRight());
		path.lineTo(rect.topRight());
		path.quadTo(rect.topRight(), rect.topRight());

		// Change background color when hovering or selecting
		if (option.state.testFlag(QStyle::State_MouseOver)) {
			painter->setPen(QPen(QColor("#FF4500")));
			painter->setBrush(QColor("#FF4500"));
			painter->drawPath(path);
		}
		else if (option.state.testFlag(QStyle::State_Selected)) {
			painter->setPen(QPen(QColor("#FF7C00")));
			painter->setBrush(QColor("#FF7C00"));
			painter->drawPath(path);
		}
		else {
			painter->setPen(QPen(QColor("#FFFFFF")));
			painter->setBrush(QColor("#FFFFFF"));
			painter->drawPath(path);
		}

		QRectF iconRect, itemText1, itemText2;

		if (item.image.length() > 2)
		{
			iconRect = QRect(rect.left() + 5, rect.top() + 5, 40, 40);
			itemText1 = QRect(iconRect.right() + 5, iconRect.top(), rect.width() - 10 - iconRect.width(), 20);
			itemText2 = QRect(itemText1.left(), itemText1.bottom() + 5, rect.width() - 10 - iconRect.width(), 20);

			painter->drawImage(iconRect, QImage(item.image));
		}
		else
		{
			itemText1 = QRect(5, rect.top(), rect.width() - 10, 20);
			itemText2 = QRect(itemText1.left(), itemText1.bottom() + 5, rect.width() - 10 - iconRect.width(), 20);
		}

		painter->setPen(QPen(QColor(Qt::black)));
		painter->setFont(QFont("Trebuchet MS", 12, QFont::Bold));
		painter->drawText(itemText1, item.title);

		painter->setPen(QPen(Qt::black));
		painter->setFont(QFont("Trebuchet MS", 12, 0));
		painter->drawText(itemText2, item.content);

		painter->restore();
	}
}

QSize AsDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	Q_UNUSED(index)
		return QSize(option.rect.width(), 50);
}
