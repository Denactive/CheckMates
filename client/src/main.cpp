#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QLabel>
#include <QMdiArea>
#include <QQuickWidget>

#include "../include/graphics.h"
#include "../tests/tests.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

//    QGuiApplication app(argc, argv);
    qmlRegisterType<ChessBoard> ("Chess", 1, 0, "ChessBoardModel");
//    QCoreApplication::setAttribute((Qt::AA_EnableHighDpiScaling));
    QApplication app(argc, argv);

    std::cout << "Begin programm\n";
    MainWindow w;
//    QMdiArea *mdiarea = new QMdiArea;
//    w.setCentralWidget(mdiarea);
//    QQuickWidget *toolbar = new QQuickWidget(QUrl(":/main.qml"));
//    toolbar->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    mdiarea->addSubWindow(toolbar);
//    w.show();

//    w.pushBoard();

    w.show();

    if (tests()) std::cout << "TESTS COMPLETE\n";
    else std::cout << "TESTS FAIL\n";


//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

        return app.exec();
}

