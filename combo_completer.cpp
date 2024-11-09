#include "combo_completer.h"
#include "ui_const.h"

#include <QItemDelegate>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QGraphicsDropShadowEffect>

class ComboxCompDelegate : public QItemDelegate
{
public:
  explicit ComboxCompDelegate(QObject* parent = nullptr) : QItemDelegate(parent) {}
  ~ComboxCompDelegate() = default;

  QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
  {
    QSize size = QItemDelegate::sizeHint(option, index);
    size.setHeight(32);
    return size;
  }
};

ComboCompleter::ComboCompleter(QAbstractItemModel* model, QObject* parent)
  : QCompleter(model, parent)
{
  //this->_init_ui();
}

void ComboCompleter::_init_ui()
{
  QAbstractItemView* view = this->popup();
  view->setItemDelegate(new ComboxCompDelegate(this));

  QWidget* w = view->window();
  w->setWindowFlag(Qt::FramelessWindowHint, true);
  w->setWindowFlag(Qt::NoDropShadowWindowHint, true);
  view->verticalScrollBar()->setStyleSheet(UIConsts::scrollbar_str);

  view->setStyleSheet("QListView{background-color: #FFFFFF;"
    "color: #353637;"
    "font-size: 14px;"
    "font-family: microsoft yahei;}"
    "QListView::item:hover {background-color:#FF00FF}");
}

