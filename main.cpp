/*
 Bu proje qInfo, qDebug,QWarning,QFatal loglama fonksiyonlarının alternatif kullanımını içerir.
 @author MimCim
*/
#include <QCoreApplication>
#include <QDebug>
#include <QMessageLogger>
#include <QDateTime>

void debug(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s :: %d   %s (%s:%u, %s)\n", type, type, localMsg.constData(), file, context.line, function);
        break;
    }
}
void warning(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s %s (%s:%u, %s)\n", QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str(), localMsg.constData(), file, context.line, function);
        break;
    }

}
void critical(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtCriticalMsg:
        fprintf(stderr, "QtCriticalMsg:  %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}
void fatal(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtFatalMsg:
        fprintf(stderr, "Debug: %s :: %d   %s (%s:%u, %s)\n", type, type, localMsg.constData(), file, context.line, function);
        break;
    }
}
void all(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
//# Eğer stderr dosyasının default dosya path'ini değiştirmek istiyorsak baştan aşağıdaki işlemi yapmalıyız.
//# İstenirse yazılacak dosya dizini stderr yerine istenilen başka bir dosya ismi verilerek de değiştirilebilir
//    QByteArray localMsg = msg.toLocal8Bit();
//    FILE *logfile = fopen("/root/Desktop/test.txt","a+");
//    fprintf(logfile, "%s \n", localMsg.constData());
//    fclose(logfile);
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
    {
        fprintf(stderr, "Debug: %s %s (%s:%u, %s)\n",QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str(), localMsg.constData(), file, context.line, function);
    }
        break;
    case QtWarningMsg:
    {
        fprintf(stderr, "Warning: %s %s (%s:%u, %s)\n", QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str(), localMsg.constData(), file, context.line, function);
    }
        break;
    case QtCriticalMsg:
    {
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
    }
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}

//Bir değişkeni makefile dosyasında tanımlayıp uygulamada tanımlanıp tanımlanmadığını kotrol etmek için;
// CFLAGS  = -DtestFlag
// CXXFLAGS = -DtestFlag
// Makefile içerisine yukarıdaki tanımlamalar eklendikten sonra aşağıdaki gibi kullanılır
//#ifdef testFlag
//    fprintf(stderr, "TANIMLI TEST_FLAG %d\n",testff);
//#else
//    fprintf(stderr, "TANIMsız \n");
//#endif

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
// # Aşağıda verilen sorgu ile executable dosyanın QTCreator üzerinden mi yoksa
// #çift tıklanarak(veya terminal üzerinden) mı çalıştırıldığı kontrol edilebilir
//    if (qgetenv("QTDIR").isEmpty())
//        logToFile = true;

// int type = QCoreApplication::arguments().at(1);  #eğer type değerini terminalden çekecek isek burayı açmamız gerek
    int type=2;
    if(type==0)
        qInstallMessageHandler(debug);
    else if(type==1)
        qInstallMessageHandler(warning);
    else if(type==2)
        qInstallMessageHandler(critical);
    else if(type==3)
        qInstallMessageHandler(fatal);
    else
        qInstallMessageHandler(all);

//# Test fonsiyonlarım
    qDebug()<<"DEbugdebugdebug";
    qCritical() << "Cirticacritical";
    qWarning() << "warnıgWarning";
    //qFatal()<<"fatalfatal";

    return a.exec();
}
