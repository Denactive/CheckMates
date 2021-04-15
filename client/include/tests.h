//#ifndef TESTS_H
//#define TESTS_H

//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QApplication>
//#include <QLabel>
//#include <QMdiArea>
//#include <QQuickWidget>
//#include <gtest/gtest.h>
//#include <gmock/gmock-matchers.h>

//#include "include/graphics.h"

//using namespace testing;

//TEST(window_show, ok)
//{
////    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
////        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
////    #endif

////    //    QGuiApplication app(argc, argv);
////        qmlRegisterType<ChessBoard> ("Chess", 1, 0, "ChessBoardModel");
////    //    QCoreApplication::setAttribute((Qt::AA_EnableHighDpiScaling));
////        QApplication app(argc, argv);

////        std::cout << "Begin programm\n";
////        MainWindow w;
////    //    QMdiArea *mdiarea = new QMdiArea;
////    //    w.setCentralWidget(mdiarea);
////    //    QQuickWidget *toolbar = new QQuickWidget(QUrl(":/main.qml"));
////    //    toolbar->setResizeMode(QQuickWidget::SizeRootObjectToView);
////    //    mdiarea->addSubWindow(toolbar);
////    //    w.show();

////    //    w.pushBoard();

////        w.show();


//    //    QQmlApplicationEngine engine;
//    //    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    //    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//    //                     &app, [url](QObject *obj, const QUrl &objUrl) {
//    //        if (!obj && url == objUrl)
//    //            QCoreApplication::exit(-1);
//    //    }, Qt::QueuedConnection);
//    //    engine.load(url);

////        return app.exec();
////    EXPECT_EQ(1, 1);
////    ASSERT_THAT(0, Eq(0));
//}

//#endif // TESTS_H
