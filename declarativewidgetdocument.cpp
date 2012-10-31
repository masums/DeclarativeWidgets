#include "declarativewidgetdocument.h"

#include "declarativeobjects_p.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>

class DeclarativeWidgetDocument::Private
{
  public:
    Private(DeclarativeWidgetDocument *qq, const QUrl &url)
      : q(qq)
      , m_url(url)
      , m_engine(new QDeclarativeEngine(q))
      , m_component(new QDeclarativeComponent(m_engine, q))
    {
    }

    DeclarativeWidgetDocument* q;
    QUrl m_url;
    QDeclarativeEngine* m_engine;
    QDeclarativeComponent* m_component;
};

DeclarativeWidgetDocument::DeclarativeWidgetDocument(const QUrl &url, QObject *parent)
  : QObject(parent)
  , d(new Private(this, url))
{
  qmlRegisterType<QAbstractItemModel>();
  qmlRegisterType<QItemSelectionModel>();

  // objects
  qmlRegisterType<QAction>();
  qmlRegisterType<DeclarativeAction>("QtGui", 1, 0, "Action");
  qmlRegisterType<DeclarativeActionItem>("QtGui", 1, 0, "ActionItem");
  qmlRegisterType<DeclarativeButtonGroup>("QtGui", 1, 0, "ButtonGroup");
  qmlRegisterType<DeclarativeSeparator>("QtGui", 1, 0, "Separator");

  // layouts
  qmlRegisterType<DeclarativeBoxLayoutAttached>();
  qmlRegisterType<DeclarativeFormLayoutAttached>();
  qmlRegisterType<DeclarativeGridLayoutAttached>();
  qmlRegisterType<DeclarativeFormLayout>("QtGui", 1, 0, "FormLayout");
  qmlRegisterType<DeclarativeGridLayout>("QtGui", 1, 0, "GridLayout");
  qmlRegisterType<DeclarativeHBoxLayout>("QtGui", 1, 0, "HBoxLayout");
  qmlRegisterType<DeclarativeStackedLayout>("QtGui", 1, 0, "StackedLayout");
  qmlRegisterType<DeclarativeVBoxLayout>("QtGui", 1, 0, "VBoxLayout");

  // widgets
  qmlRegisterType<DeclarativeCalendarWidget>("QtGui", 1, 0, "CalendarWidget");
  qmlRegisterType<DeclarativeCheckBox>("QtGui", 1, 0, "CheckBox");
  qmlRegisterType<DeclarativeColorDialogAttached>();
  qmlRegisterType<DeclarativeColorDialog>("QtGui", 1, 0, "ColorDialog");
  qmlRegisterType<DeclarativeColumnView>("QtGui", 1, 0, "ColumnView");
  qmlRegisterType<DeclarativeCommandLinkButton>("QtGui", 1, 0, "CommandLinkButton");
  qmlRegisterType<DeclarativeDateEdit>("QtGui", 1, 0, "DateEdit");
  qmlRegisterType<DeclarativeDateTimeEdit>("QtGui", 1, 0, "DateTimeEdit");
  qmlRegisterType<DeclarativeDial>("QtGui", 1, 0, "Dial");
  qmlRegisterType<DeclarativeDialog>("QtGui", 1, 0, "Dialog");
  qmlRegisterType<DeclarativeDialogButtonBox>("QtGui", 1, 0, "DialogButtonBox");
  qmlRegisterType<DeclarativeDoubleSpinBox>("QtGui", 1, 0, "DoubleSpinBox");
  qmlRegisterType<DeclarativeFileDialogAttached>();
  qmlRegisterType<DeclarativeFileDialog>("QtGui", 1, 0, "FileDialog");
  qmlRegisterType<DeclarativeFontDialog>("QtGui", 1, 0, "FontDialog");
  qmlRegisterType<DeclarativeFrame>("QtGui", 1, 0, "Frame");
  qmlRegisterType<DeclarativeGroupBox>("QtGui", 1, 0, "GroupBox");
  qmlRegisterType<DeclarativeInputDialogAttached>();
  qmlRegisterType<DeclarativeInputDialog>("QtGui", 1, 0, "InputDialog");
  qmlRegisterType<DeclarativeLabel>("QtGui", 1, 0, "Label");
  qmlRegisterType<DeclarativeLCDNumber>("QtGui", 1, 0, "LCDNumber");
  qmlRegisterType<DeclarativeLineEdit>("QtGui", 1, 0, "LineEdit");
  qmlRegisterType<DeclarativeListView>("QtGui", 1, 0, "ListView");
  qmlRegisterType<DeclarativeMainWindow>("QtGui", 1, 0, "MainWindow");
  qmlRegisterType<DeclarativeMenu>("QtGui", 1, 0, "Menu");
  qmlRegisterType<DeclarativeMenuBar>("QtGui", 1, 0, "MenuBar");
  qmlRegisterType<DeclarativeMessageBoxAttached>();
  qmlRegisterType<DeclarativeMessageBox>("QtGui", 1, 0, "MessageBox");
  qmlRegisterType<DeclarativePlainTextEdit>("QtGui", 1, 0, "PlainTextEdit");
  qmlRegisterType<DeclarativeProgressBar>("QtGui", 1, 0, "ProgressBar");
  qmlRegisterType<DeclarativePushButton>("QtGui", 1, 0, "PushButton");
  qmlRegisterType<DeclarativeRadioButton>("QtGui", 1, 0, "RadioButton");
  qmlRegisterType<DeclarativeScrollArea>("QtGui", 1, 0, "ScrollArea");
  qmlRegisterType<DeclarativeScrollBar>("QtGui", 1, 0, "ScrollBar");
  qmlRegisterType<DeclarativeSlider>("QtGui", 1, 0, "Slider");
  qmlRegisterType<DeclarativeSpinBox>("QtGui", 1, 0, "SpinBox");
  qmlRegisterType<DeclarativeStackedWidget>("QtGui", 1, 0, "StackedWidget");
  qmlRegisterType<DeclarativeStatusBarAttached>();
  qmlRegisterType<DeclarativeStatusBar>("QtGui", 1, 0, "StatusBar");
  qmlRegisterType<DeclarativeTableView>("QtGui", 1, 0, "TableView");
  qmlRegisterType<DeclarativeTabWidgetAttached>();
  qmlRegisterType<DeclarativeTabWidget>("QtGui", 1, 0, "TabWidget");
  qmlRegisterType<DeclarativeTextBrowser>("QtGui", 1, 0, "TextBrowser");
  qmlRegisterType<DeclarativeTextEdit>("QtGui", 1, 0, "TextEdit");
  qmlRegisterType<DeclarativeTimeEdit>("QtGui", 1, 0, "TimeEdit");
  qmlRegisterType<DeclarativeToolBar>("QtGui", 1, 0, "ToolBar");
  qmlRegisterType<DeclarativeToolButton>("QtGui", 1, 0, "ToolButton");
  qmlRegisterType<DeclarativeTreeView>("QtGui", 1, 0, "TreeView");
  qmlRegisterType<DeclarativeWebView>("QtGui", 1, 0, "WebView");
  qmlRegisterType<DeclarativeWidget>("QtGui", 1, 0, "Widget");

  d->m_component->loadUrl(d->m_url);
  if (d->m_component->isError()) {
    foreach (const QDeclarativeError &error, d->m_component->errors())
      qDebug() << error.toString();
  }
}

DeclarativeWidgetDocument::~DeclarativeWidgetDocument()
{
  delete d;
}

void DeclarativeWidgetDocument::setContextProperty(const QString &name, const QVariant &value)
{
  d->m_engine->rootContext()->setContextProperty(name, value);
}

void DeclarativeWidgetDocument::setContextProperty(const QString &name, QObject *object)
{
  d->m_engine->rootContext()->setContextProperty(name, object);
}

QDeclarativeEngine* DeclarativeWidgetDocument::engine() const
{
  return d->m_engine;
}

QWidget* DeclarativeWidgetDocument::createWidget()
{
  QObject *object = d->m_component->create();
  if (!object) {
    qWarning("Unable to create component");
    return 0;
  }

  AbstractDeclarativeObject *declarativeObject = dynamic_cast<AbstractDeclarativeObject*>(object);

  if (!declarativeObject) {
    qWarning("Root element is no AbstractDeclarativeObject subclass");
    return 0;
  }

  declarativeObject->setParent(this);

  return qobject_cast<QWidget*>(declarativeObject->object());
}
