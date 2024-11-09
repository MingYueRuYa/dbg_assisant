#include "combobox.h"
#include "ui_const.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QLineEdit>
#include <QScrollBar>
#include <QStyledItemDelegate>

class ComboBoxItemDelegate : public QStyledItemDelegate {
public:
  ComboBoxItemDelegate(QObject* parent = nullptr)
    : QStyledItemDelegate(parent) {}

  void initStyleOption(QStyleOptionViewItem* option,
    const QModelIndex& index) const {
    QStyledItemDelegate::initStyleOption(option, index);
    option->displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
  }
};

ComboBox::ComboBox(QWidget* parent) : QComboBox(parent) {
  this->_init_ui();
  this->_init_signal();
  qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);
  this->setItemDelegate(new ComboBoxItemDelegate());
  this->update_theme();
}

void ComboBox::update_theme() {

  std::string parent_str = R"(QWidget{
background-color:transparent;
border:none;
margin:0;
})";

  this->setStyleSheet(UIConsts::combobox_style);
  this->view()->setStyleSheet(UIConsts::view_str);

  QWidget* w = this->view()->window();
  w->setWindowFlag(Qt::FramelessWindowHint, true);
  w->setWindowFlag(Qt::NoDropShadowWindowHint, true);
  w->setAttribute(Qt::WA_NoSystemBackground);
  w->setAttribute(Qt::WA_TranslucentBackground);
  QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(w);
  shadow->setOffset(0, 0);
  shadow->setColor(QColor("#19000000"));
  shadow->setBlurRadius(10);
  this->view()->setGraphicsEffect(shadow);

  this->view()->verticalScrollBar()->setStyleSheet(UIConsts::scrollbar_str);
  this->view()->parentWidget()->setStyleSheet(
    QString::fromStdString(parent_str));
}

bool ComboBox::set_line_edit_enable(bool enable) {
  QLineEdit* line_edit = this->lineEdit();
  if (nullptr == line_edit) {
    return false;
  }

  line_edit->setFocusPolicy(enable ? Qt::FocusPolicy::ClickFocus
    : Qt::FocusPolicy::NoFocus);
  line_edit->setEnabled(enable);
  return true;
}

void ComboBox::on_text_changed(const QString& text) {
  QLineEdit* line_edit = this->lineEdit();
  if (nullptr == line_edit) {
    return;
  }
  QFontMetrics metrics(line_edit->font());
  int width = line_edit->width() - 5;
  QString elided_str = metrics.elidedText(text, Qt::ElideMiddle, width);
  line_edit->setText(elided_str);
}

void ComboBox::_init_signal() {
  connect(this, SIGNAL(currentTextChanged(QString)), this,
    SLOT(on_text_changed(QString)));
}

void ComboBox::_init_ui() {}
