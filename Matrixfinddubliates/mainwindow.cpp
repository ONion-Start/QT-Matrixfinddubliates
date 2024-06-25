#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QIntValidator>
#include <QTableWidgetItem>
#include <QBrush>
#include <QColor>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    QLabel *rowsLabel = new QLabel("Введите количество строк (n):");
    rowsInput = new QLineEdit;
    rowsInput->setValidator(new QIntValidator(1, 100, this));
    QLabel *colsLabel = new QLabel("Введите количество столбцов (m):");
    colsInput = new QLineEdit;
    colsInput->setValidator(new QIntValidator(1, 100, this));
    QPushButton *setDimensionsButton = new QPushButton("Установить размер");

    inputLayout->addWidget(rowsLabel);
    inputLayout->addWidget(rowsInput);
    inputLayout->addWidget(colsLabel);
    inputLayout->addWidget(colsInput);
    inputLayout->addWidget(setDimensionsButton);

    tableWidget = new QTableWidget;

    QPushButton *submitButton = new QPushButton("Отправить матрицу");

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(submitButton);

    connect(setDimensionsButton, &QPushButton::clicked, this, &MainWindow::onSetDimensions);
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::onSubmitMatrix);
}

void MainWindow::onSetDimensions() {
    bool rowsOk, colsOk;
    int rows = rowsInput->text().toInt(&rowsOk);
    int cols = colsInput->text().toInt(&colsOk);

    if (rowsOk && colsOk) {
        tableWidget->setRowCount(rows);
        tableWidget->setColumnCount(cols);
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите допустимые значения для строк и столбцов.");
    }
}

void MainWindow::onSubmitMatrix() {
    int rows = tableWidget->rowCount();
    int cols = tableWidget->columnCount();

    matrix.resize(rows);
    for (int i = 0; i < rows; ++i) {
        matrix[i].resize(cols);
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if (item && !item->text().isEmpty()) {
                matrix[i][j] = item->text().toInt();
            } else {
                QMessageBox::warning(this, "Ошибка", "Заполните все ячейки матрицы.");
                return;
            }
        }
    }

    // Очистка всех ячеек от предыдущей подсветки
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tableWidget->item(i, j)->setBackground(QBrush(Qt::white));
        }
    }

    // Генерация цветов
    vector<QColor> colors = {
        QColor(255, 0, 0), QColor(0, 255, 0), QColor(0, 0, 255),
        QColor(255, 255, 0), QColor(255, 0, 255), QColor(0, 255, 255),
        QColor(192, 192, 192), QColor(128, 0, 0), QColor(128, 128, 0),
        QColor(0, 128, 0), QColor(128, 0, 128), QColor(0, 128, 128),
        QColor(0, 0, 128)
    };

    unordered_map<int, QColor> colorMap;
    int colorIndex = 0;

    // Поиск и подсветка одинаковых элементов
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value = matrix[i][j];

                        // Если значение уже имеет назначенный цвет, используем его
                        if (colorMap.find(value) == colorMap.end()) {
                            if (colorIndex >= colors.size()) {
                                QMessageBox::warning(this, "Ошибка", "Недостаточно цветов для выделения всех одинаковых элементов.");
                                return;
                            }
                            colorMap[value] = colors[colorIndex++];
                        }

                        QColor color = colorMap[value];

                        // Подсветка всех одинаковых элементов
                        for (int p = 0; p < rows; ++p) {
                            for (int q = 0; q < cols; ++q) {
                                if (matrix[p][q] == value) {
                                    tableWidget->item(p, q)->setBackground(QBrush(color));
                                }
                            }
                        }
                    }
                }
            }
