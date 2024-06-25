#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QVector>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onSetDimensions();
    void onSubmitMatrix();

private:
    QLineEdit *rowsInput;
    QLineEdit *colsInput;
    QTableWidget *tableWidget;
    QVector<QVector<int>> matrix;
};

#endif // MAINWINDOW_H
