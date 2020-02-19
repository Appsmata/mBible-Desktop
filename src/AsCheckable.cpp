#include "AsCheckable.h"

AsCheckable::AsCheckable(QObject* parent) :
    QStringListModel(parent) {
}

AsCheckable::AsCheckable(const QStringList& strings, QObject* parent) :
    QStringListModel(strings, parent) {

}

Qt::ItemFlags AsCheckable::flags(const QModelIndex& index) const {
    Qt::ItemFlags defaultFlags = QStringListModel::flags(index);
    if (index.isValid()) {
        return defaultFlags | Qt::ItemIsUserCheckable;
    }
    return defaultFlags;
}

QVariant AsCheckable::data(const QModelIndex& index,
    int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::CheckStateRole)
        return checkedItems.contains(index) ?
        Qt::Checked : Qt::Unchecked;

    else if (role == Qt::BackgroundColorRole)
        return checkedItems.contains(index) ?
        QColor("#ffffb2") : QColor("#ffffff");

    return QStringListModel::data(index, role);
}

bool AsCheckable::setData(const QModelIndex& index,
    const QVariant& value, int role) {

    if (!index.isValid() || role != Qt::CheckStateRole)
        return false;

    if (value == Qt::Checked)
        checkedItems.insert(index);
    else
        checkedItems.remove(index);

    emit dataChanged(index, index);
    return true;
}

void AsCheckable::save() {
    /*QFile file("required_components.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << "Required components:" << "\n";
    foreach(QPersistentModelIndex index, checkedItems)
        out << index.data().toString() << "\n";*/
}