#include "indexmainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QMessageBox>
#include <QTranslator>
#include <QVariant>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "citation_indexing_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    IndexMainWindow w;
    w.show();
#if 0
    MyTextEditor test;
    test.installEventFilter(&w);
    test.setWindowTitle("test");
    test.show();
    MyEditor test2;
    test2.setWindowTitle("test2");
    test2.show();
    MyDataTable test3;
    test3.setWindowTitle("test3");
    test3.show();
#endif
#if 0
    MyTaskModule task;
    int key = -1;
    QMap<QString, QString> temp;
    QMap<QString, QMap<QString, QString>> temp2;
    QString err;
    //    task.finish_task(5, 2, err, u8"无话可说", u8"完美");
    //    task.load_single_task(key, temp, err);
    //    task.load_all_task(temp2, err);
    task.load_new_task();
    qDebug() << task.get_emergency();
    qDebug() << task.get_article_code();
    qDebug() << task.is_error();
    qDebug() << task.get_error_string();
#endif
#if 0
    MyDataBaseModule db;
    auto ret = db.create_out_db("./test_out.db");
    if (ret) {
        qDebug() << "creat out db successfully!";
    } else {
        qDebug() << db.error();
    }

#endif
    MyDataBaseModule db;
#if 0
    if (db.system_info_db_open("./system_info.db")) {
        QMap<QString, QMap<QString, QVariant>> temp_map;
        db.system_info_db_job_table_read(temp_map);
        temp_map.clear();
        db.system_info_db_literature_table_read(temp_map);
        temp_map.clear();
        db.system_info_db_location_table_read(temp_map);
        temp_map.clear();
        db.system_info_db_publish_table_read(temp_map);
        //        qDebug() << temp_map;
        temp_map.clear();
        db.system_info_db_close();
    }
    if (db.input_db_open("D:/work/613304/20210812/132732200025725789/13/3370/20232/20232.db")) {
        QMap<QString, QMap<QString, QVariant>> temp_map;
        db.input_db_table_article_read(temp_map);
        qDebug() << temp_map;
        temp_map.clear();
        db.input_db_table_ciation_read(temp_map);
        qDebug() << temp_map;
        temp_map.clear();
        db.input_db_table_detail_read(temp_map);
        qDebug() << temp_map;
        temp_map.clear();
        db.input_db_table_view_cn_read(temp_map);
        qDebug() << temp_map;
        temp_map.clear();
        db.input_db_close();
    } else {
        qDebug() << db.error();
    }
#endif
#if 0
    if (db.out_db_open("D:/work/613304/20210812/132732200025725789/13/3370/20232/upload/20232.db")) {
        QMap<QString, QMap<QString, QVariant>> temp_map;
        if (!db.out_db_table_result_read(temp_map)) {
            qDebug() << db.error();
        }
        //        qDebug() << temp_map;
        db.out_db_close();
        if (!db.out_db_open("./test_out.db")) {
            qDebug() << db.error();
        }
        if (!db.out_db_table_result_write(temp_map)) {
            qDebug() << db.error();
        }
        db.out_db_close();
    } else {
        QMessageBox::critical(&w, "error", db.error());
    }
#endif

    return a.exec();
}
