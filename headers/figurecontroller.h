#pragma once

#include <QObject>

#include "pimpl.h"

class FigureController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> objects READ objects NOTIFY objectsChanged FINAL)
public:
    static FigureController* instance();

    Q_INVOKABLE void addItem(int t, float x, float y);

    QList<QObject*> objects() const;

    static void registerType();

signals:
    void objectsChanged();

private:
    FigureController();
    ~FigureController() override;
    FigureController(const FigureController&) = delete;
    FigureController(FigureController&&) = delete;
    FigureController& operator=(const FigureController&) = delete;
    FigureController& operator=(FigureController&&) = delete;

    DECLARE_PIMPL
};

