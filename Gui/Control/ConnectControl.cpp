#include "ConnectControl.h"
#include "ui_ConnectControl.h"

Connecter::Connecter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Connecter)
{
    ui->setupUi(this);
}

Connecter::~Connecter()
{
    delete ui;
}
