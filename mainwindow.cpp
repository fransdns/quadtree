#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // No setStyleSheet
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // Set the background color to white
    painter.fillRect(rect(), Qt::white);

    // Draw the vertical line in the middle
    int midX = width() / 2;
    painter.setPen(Qt::black); // Ensure the pen color is set to black
    painter.drawLine(midX, 0, midX, height());

    // Draw the horizontal line in the middle
    int midY = height() / 2;
    painter.drawLine(0, midY, width(), midY);

    // Draw the points where the user clicked
    painter.setPen(Qt::black); // Ensure the pen color is set to black
    painter.setBrush(Qt::black); // Ensure the brush color is set to black
    for (const QPoint &point : points) {
        painter.drawEllipse(point, 5, 5); // Draw a circle at each point
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        points.append(event->pos());
        update(); // This triggers a repaint
    }
}
