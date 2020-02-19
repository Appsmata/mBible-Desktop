#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <QMetaType>

typedef enum {
    S_RED,
    S_BLUE,
    S_YELLOW,
} ItemStatus;

struct AsItem {
    QString image;
    QString title;
    QString content;
};

Q_DECLARE_METATYPE(AsItem)

#endif //ITEMDATA_H
