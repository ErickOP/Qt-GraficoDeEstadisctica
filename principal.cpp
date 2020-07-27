#include "principal.h"
#include "ui_principal.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    lienzo= QPixmap(400,460);
    lienzo.fill(Qt::white);
    this->dibujar();
}

Principal::~Principal()
{
    delete ui;
}

void Principal::dibujar()
{

    QPainter painter(&lienzo);
    //Crear un pincel para los bordes
    QPen pincel;
    //int n1=ui->inNota1->value();
    int x=0;
    int y=0;

    //Cambiando propiedades del pincel
    pincel.setWidth(2);
    pincel.setJoinStyle(Qt::MiterJoin);
    painter.setPen(pincel);

    //Crear un objeto a la barra Azul
    QColor colorRelleno( 0, 0, 0 );
    //Volver el pincel al "pintor"(borde)
    painter.setPen(pincel);
    //Creando colores para la tercera barra
    QColor cRellenoBarra3( 0, 0, 0 );
    //Establecinedo colores al pincel y al painter
    painter.setPen(pincel);
    //Dibujar Linea de medidas Y
    painter.drawLine(x+20,y+145, 20,450);
    //Dibujar Linea de medidas X
    painter.drawLine(x+20,y+450, 500,450);

    //Cordenada
        x=0;
    int metrica =150;
    for (int i=145;i<450;i+=20) {
        QString numeros= QString::number(metrica);
        metrica-=10;
        painter.drawText(x+30,i,numeros);
        painter.drawLine(x+20,i,x+25,i);
    }
     painter.drawText(90,465,"");
     painter.drawText(205,465,"");
     painter.drawText(325,465,"");
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo= QFileDialog::getSaveFileName(this,"Guardar imagen", QString(),"Imagenes (*.png)");

    if(!nombreArchivo.isEmpty()){
        if(lienzo.save(nombreArchivo))
            QMessageBox::information(this,"Guardar imagen","Archivo gaurdado en: "+ nombreArchivo);
        else
            QMessageBox::warning(this, "Gaurdar imagen", "No se puedo guardar el archivo");
    }
}

void Principal::on_cmdPromedio_clicked()
{
    QPainter painter(&lienzo);
    QPen pincel;
    int n1=ui->inNota1->value();
    int n2=ui->inNota2->value();
    int n3=ui->inNota3->value();
    int x=0;

    pincel.setWidth(5);
    pincel.setJoinStyle(Qt::MiterJoin);
    QColor colorBarra1Fondo(240, 240, 16 );
    painter.setBrush(colorBarra1Fondo);
    painter.setPen(pincel);

    //Dibujar Primera Barra
    painter.drawRect(x+50, 450-n1*2, 100,n1*1.95);
    //Crear un objeto color Azul
    QColor colorRelleno( 14, 96, 250);
    //Volver el pincel al "pintor"(borde)
    painter.setPen(pincel);
    //Establecer color  al Brush(relleno)
    painter.setBrush(colorRelleno);
    //Dibujar Segunda Barra
    painter.drawRect(x+170, 450-n2*2, 100,n2*1.95);
    //Creando colores para la tercera barra
    QColor cRellenoBarra3( 240, 56, 16 );
    //Establecinedo colores al pincel y al painter
    painter.setPen(pincel);
    painter.setBrush(cRellenoBarra3);
    //Dibujar Tercera Barra
    painter.drawRect(x+290,450-n3*2 ,100,n3*1.95);
    update();
}

void Principal::on_actionNuevo_triggered()
{
    lienzo.fill(Qt::white);
    dibujar();
    ui->inNota1->setValue(0);
    ui->inNota2->setValue(0);
    ui->inNota3->setValue(0);
    update();
}

void Principal::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.drawPixmap(40, 40, lienzo);
        event->accept();
}


void Principal::on_actionAcerca_de_triggered()
{
    Acercade *acerca_de = new Acercade(this);
    acerca_de->setModal(true);
    acerca_de->show();
}
