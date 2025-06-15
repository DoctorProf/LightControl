#pragma once

#include <QObject>
#include <QColorDialog>
#include <QColor>

class ColorDialogHelper : public QObject
{
    Q_OBJECT
public:
    explicit ColorDialogHelper(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QString getColor(const QString &initial = "#ffffff") {
        QColor color = QColorDialog::getColor(QColor(initial), nullptr, "Выберите цвет");
        return color.isValid() ? color.name() : initial;
    }
};
