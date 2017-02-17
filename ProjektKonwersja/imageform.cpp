#include "imageform.h"
#include "ui_imageform.h"

QPixmap scaleToMax(QPixmap p, int max){
    int d = 2;
    if(p.width() < p.height() and p.height()>=max) return p.scaledToHeight(max - d);
    else if(p.width() > p.height() and p.width()>=max) return p.scaledToWidth(max - d);
    else if(p.width() == p.height() and p.height()>=max) return p.scaled(max - d, max - d);
    return p.scaled(p.width(), p.height());
}

ImageForm::ImageForm(const QPixmap &pixmap, const QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageForm),
    scene(this),
    orgMax(pixmap),
    orginal(scaleToMax(pixmap,500))
{
    ui->setupUi(this);
    ui->image->setScene(&scene);
    scene.addPixmap(orginal);
    setWindowTitle(title);
}

ImageForm::~ImageForm()
{
    delete ui;
}
QPixmap ImageForm::getOrginal() const{
    return orgMax;
}
void ImageForm::conversion(const ConversionTool &ct){
    QPixmap temp;
    scene.addPixmap(temp.fromImage(ct(orginal.toImage())));
}
