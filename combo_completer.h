#pragma once

#include <QCompleter>
#include <QAbstractItemModel>

class ComboCompleter : public QCompleter
{
public:
  ComboCompleter(QAbstractItemModel* model, QObject* parent = nullptr);
  ~ComboCompleter() = default;

public:
  void _init_ui();

private:
  Q_DISABLE_COPY(ComboCompleter)

};

