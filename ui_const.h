#pragma once

#include <QString>

namespace UIConsts {

  const QString combobox_style = R"(QComboBox{
          border:1px solid #CCCCCC;
          background:#FFF;
				  color:
				  #4C4C4C;
				  font-size:12px;
				  padding:0 0 0 8px;
				  border-radius:2px;
				  margin:0 3px;
				  text-align: Middle;
					font-family: "Microsoft YaHei";
				  }
				  QComboBox[error=true]{
				  border: 1px solid rgba(255, 61, 61, 0.2);
				  color: #FF3D3D;
				  }
				  QComboBox::hover{
				  /*padding-left:7px;*/
				  background:#F2F2F2;
				  border:
				  1px solid #CCCCCC;
				  }

				  QComboBox::on{
				  /*padding-left:7px;*/
          background:#FFF;
				  border:
				  1px solid #0b57d0;
				  }

				  QComboBox::down-arrow{
				  border:none;
				  background:transparent;
				  }
				  QComboBox::drop-down{
				  width:12px;
				  height:7px;
				  subcontrol-position:right center;
				  image:url(:/WindbgConfig/images/arrow_down.png);
				  padding-right: 11px;
				  }
				  QComboBox::drop-down:on{
				  image:url(:/WindbgConfig/images/arrow_up.png);
				  }
				  QComboBox:editable{
				  background:
				  #FFF;
				  }
				  QComboBox:focus{
				  background:
				  #FFF;
					border:1px solid #0b57d0;
				  }
				  QComboBox:disabled{
				  padding-left:7px;
				  background:transparent;
				  border:
				  1px solid #CCCCCC;
				  })";

  const QString scrollbar_str = R"(QScrollBar:vertical{
border:1px solid transparent;
width:4px;
background-color:
transparent;
						 padding-top:16px;
						 padding-bottom:16px;
						 }
						 QScrollBar:vertical:hover{
						 border:none;
						 border-radius:2px;
						 }
						 QScrollBar::handle:vertical{
						 background:
						 #ededed;
						 width:4px;
						 border-radius:2px;
						 }
						 QScrollBar::handle:vertical:hover{
						 background:
						 #e6e6e6;
						 }
						 QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{background:none;}
						 QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical{
						 height:0px;width:0px;
						 background-color:rgba(0,0,0,0);
						 })";


  const QString view_str = "QAbstractItemView { \
outline: none; \
show-decoration-selected:0;\
border:\
1px solid #CCCCCC;\
background:\
#ffffff;\
				   padding: 6px;\
				   margin:4 6px;\
				   border-radius:2px;\
				   min-width: 0px;\
				   }\
				   QAbstractItemView::item {\
				   color:\
				   #4c4c4c;\
				   font-size:12px; \
				   height:28px; \
				   padding:0 0 0 8px; \
				   } \
				   QAbstractItemView::item:hover, QAbstractItemView::item:selected{ \
				   padding:0 0 0 0; \
				   border-radius:2px; \
				   background-color: \
				   #1967d2; \
				   color: \
				   #FFFFFF; \
				   }";


  const QString list_view_style = R"(QListView{
border:none;
font-size:12px;
background:
/*UiThemeStart[WidgetBGColor]*/
#ededed;
/*UiThemeEnd*/;
outline:none;

}

QListView::item{
padding-left:10px;
font-size:12px;
height:28px;
color:
/*UiThemeStart[BodyText]*/
#323232;
/*UiThemeEnd*/;
border-bottom:1px solid
/*UiThemeStart[TitleBarBg]*/
#bfbfbf;
/*UiThemeEnd*/;
}

QListView::item:selected{
padding-left:10px;
font-size:12px;
color:
/*UiThemeStart[ConfigTitle]*/
#000000;
/*UiThemeEnd*/;
background:
/*UiThemeStart[BtnHover]*/
#fafafa;
/*UiThemeEnd*/;
}

QListView::item:hover{
padding-left:10px;
font-size:12px;
color:
/*UiThemeStart[ConfigTitle]*/
#000000;
/*UiThemeEnd*/;
background:
/*UiThemeStart[BtnHover]*/
#fafafa;
/*UiThemeEnd*/;
})";


  const QString list_widget_style = R"(QListWidget{
border:none;
font-size:12px;
background:
/*UiThemeStart[WidgetBGColor]*/
#ededed;
/*UiThemeEnd*/;
outline:none;

}

QListWidget::item{
padding-left:10px;
font-size:12px;
height:28px;
color:
/*UiThemeStart[BodyText]*/
#323232;
/*UiThemeEnd*/;
border-bottom:1px solid
/*UiThemeStart[TitleBarBg]*/
#bfbfbf;
/*UiThemeEnd*/;
}

QListWidget::item:selected{
padding-left:10px;
font-size:12px;
color:
/*UiThemeStart[ConfigTitle]*/
#000000;
/*UiThemeEnd*/;
background:
/*UiThemeStart[BtnHover]*/
#fafafa;
/*UiThemeEnd*/;
}

QListWidget::item:hover{
padding-left:10px;
font-size:12px;
color:
/*UiThemeStart[ConfigTitle]*/
#000000;
/*UiThemeEnd*/;
background:
/*UiThemeStart[BtnHover]*/
#fafafa;
/*UiThemeEnd*/;
})";
}
