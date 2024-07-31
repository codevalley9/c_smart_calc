#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(scan_numbers()));

    connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(scan_numbers()));


    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(scan_numbers()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(scan_numbers()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scan_numbers()
{
    QPushButton* button = (QPushButton *) sender();
    QString new_label = ui->value->text() + button->text();
    ui->value->setText(new_label);
}

void MainWindow::on_pushButton_point_clicked()
{
    if(!ui->value->text().endsWith('.'))
    ui->value->setText(ui->value->text() + ".");
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->value->clear();
}


void MainWindow::on_pushButton_equal_clicked()
{

    QString exeq_str = ui->value->text();
    QByteArray arr = exeq_str.toLocal8Bit();
    char *expr = arr.data();
    double res = 0;
    double x = ui->value_x->text().toDouble();
    res = parsing(expr, &stack_num, &stack_op, x);
    ui->value->setText(QString::number(res));
}


void MainWindow::on_pushButton_div_clicked()
{
    ui->value->setText(ui->value->text() + "÷");
}


void MainWindow::on_pushButton_X_clicked()
{
    ui->value->setText(ui->value->text() + "x");
}


void MainWindow::on_pushButton_grapf_clicked()
{
    paintGrath();
}

void MainWindow::paintGrath() {
    ui->widget->clearGraphs();
    double xBegin, xEnd, yBegin, yEnd, h, X, Y; //начало, конец промежутка, шаг, временная переменная
    QVector<double> vec_x,vec_y;

    h = 0.1;
    xBegin = ui->spinBox_min_x->value();
    xEnd = ui->spinBox_max_x->value();

    yBegin = ui->spinBox_min_y->value();
    yEnd = ui->spinBox_max_y->value();

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

    for(X = xBegin; X <= xEnd; X += h)
    {
        qDebug() << X;
        QString exeq_str = ui->value->text();
        QByteArray arr = exeq_str.toLocal8Bit();
        char *expr = arr.data();
        Y = parsing(expr, &stack_num, &stack_op,X);
        qDebug() << Y;
        vec_x.push_back(X);
        vec_y.push_back(Y);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(vec_x, vec_y);
    ui->widget->replot();
}
