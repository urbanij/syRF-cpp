#include "stub_matching.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    StubMatching w;
    w.show();

#if !defined(Q_OS_WIN) && !defined(Q_OS_MAC)
    a.setWindowIcon(QIcon(QStringLiteral(":/icons/stub2.svg")));
#endif

    return a.exec();
}
