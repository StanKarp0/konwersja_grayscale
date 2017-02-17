#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(this)
{
    ui->setupUi(this);
    ui->image->setScene(&scene);
}

MainWindow::~MainWindow(){
    delete ui;
}
QPixmap scaleToMax(QPixmap p, int max){
    int d = 2;
    if(p.width() < p.height() and p.height()>=max)          return p.scaledToHeight(max - d);
    else if(p.width() > p.height() and p.width()>=max)      return p.scaledToWidth(max - d);
    else if(p.width() == p.height() and p.height()>=max)    return p.scaled(max - d, max - d);
    return p.scaled(p.width(), p.height());
}
ConversionTool MainWindow::getConvTool() const {
    ConversionTool cf = ConversionTool(ui->mergeSBar->value()/100.);
    int cRangeIndex = ui->rangeMode->currentIndex();
    double hue = ui->hueSBarR->value(), tol = ui->tolSBar->value()/100.;
    if(!cRangeIndex) {
        int cChanelsIndex = ui->chanelMode->currentIndex();
        double red = ui->redSBar->value()/100., green = ui->greenSBar->value()/100., blue = ui->blueSBar->value()/100.;
        if(cChanelsIndex == 0)          cf.add(GrayscaleGimpConv(red, green, blue));
        else if(cChanelsIndex == 1)     cf.add(GrayscaleNormConv(red,green,blue));

        int cDuotoneIndex = ui->duotoneMode->currentIndex();
        if(cDuotoneIndex == 1)          cf.add(DuotoneConv(ui->hueSBarDt->value()));
        else if(cDuotoneIndex == 2)     cf.add(ReverseDuotoneConv(ui->hueSBarDt->value()));

    } else if(cRangeIndex == 1)         cf.add(RangeConv(hue, tol, GrayscaleGimpConv(1/3.,1/3.,1/3.)));
    else if(cRangeIndex == 2)           cf.add(MonoRangeConv(hue, tol, GrayscaleGimpConv(1/3.,1/3.,1/3.)));

    return cf;
}
void MainWindow::editImage(){
    ConversionTool cf = getConvTool();
    scene.clear();
    ui->image->setScene(&scene);
    scene.addPixmap(QPixmap().fromImage(cf(orginal500)));
}
void MainWindow::setEnableRange(const bool b){
    ui->chanelsWidget->setEnabled(!b);
    ui->duotoneWidget->setEnabled(!b);
    ui->rangeLabel1->setEnabled(b);
    ui->rangeLabel2->setEnabled(b);
    ui->hueSBarR->setEnabled(b);
    ui->hueSBoxR->setEnabled(b);
    ui->tolSBar->setEnabled(b);
    ui->tolSBox->setEnabled(b);
}
void MainWindow::setEnableDuotone(const bool b){
    ui->hueSBoxDt->setEnabled(b);
    ui->hueSBarDt->setEnabled(b);
    ui->duotoneLabel->setEnabled(b);
}

void MainWindow::changeMode(){
    if(ui->rangeMode->currentIndex()) {
        setEnableRange(true);
    } else {
        setEnableRange(false);
        if(ui->duotoneMode->currentIndex()) setEnableDuotone(true);
        else setEnableDuotone(false);
    }
    editImage();
}
void MainWindow::setConf(const QDomDocument &doc) {
    QDomNodeList rList= doc.elementsByTagName("range");
    QDomNodeList gList= doc.elementsByTagName("grayscale");
    QDomNodeList dList= doc.elementsByTagName("duotone");
    ui->mergeSBar->setValue(doc.firstChild().attributes().namedItem("merge").nodeValue().toInt());
    if(!rList.isEmpty()) {
        QDomNamedNodeMap m = rList.at(0).attributes();
        ui->rangeMode->setCurrentIndex(m.namedItem("n").nodeValue().toInt());
        ui->hueSBarR->setValue(m.namedItem("hue").nodeValue().toInt());
        ui->tolSBar->setValue(m.namedItem("tol").nodeValue().toInt());
    } else {
        ui->rangeMode->setCurrentIndex(0);
        if(!gList.isEmpty()) {
            QDomNamedNodeMap m = gList.at(0).attributes();
            ui->chanelMode->setCurrentIndex(m.namedItem("n").nodeValue().toInt());
            ui->redSBar->setValue(m.namedItem("red").nodeValue().toInt());
            ui->greenSBar->setValue(m.namedItem("green").nodeValue().toInt());
            ui->blueSBar->setValue(m.namedItem("blue").nodeValue().toInt());
        }
        if(!dList.isEmpty()) {
            QDomNamedNodeMap m = dList.at(0).attributes();
            ui->duotoneMode->setCurrentIndex(m.namedItem("n").nodeValue().toInt());
            ui->hueSBarDt->setValue(m.namedItem("hue").nodeValue().toInt());
        } else {
            ui->duotoneMode->setCurrentIndex(0);
        }
    }
}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this,
                  tr("Otwórz plik"), "", tr("Pliki graficzne (*.png *.jpg *.bmp)"));

    QPixmap pixmap(filename);
    if(pixmap.isNull()) return;
    QString title(filename);

    setWindowTitle("Konwersja do odcieni szarości - "+title); \
    orginal = pixmap.toImage();
    orginal500 = scaleToMax(pixmap,500).toImage();
    editImage();
}

void MainWindow::saveFile(){
    QString filename = QFileDialog::getSaveFileName(this,
                  tr("Zapisz plik"), "", tr("Plik PNG (*.png);;Plik JPG (*.jpg);;Plik BMP (*.bmp)"));
    ConversionTool cf = getConvTool();
    QImage toSaveImg = cf(orginal);
    QPixmap toSavePixmap = QPixmap().fromImage(toSaveImg);
    toSavePixmap.save(filename);
}



void MainWindow::openConf(){
    QString filename = QFileDialog::getOpenFileName(this,
                  tr("Otwórz konfigurację"), "", tr("Plik XML (*.xml)"));
    int result = 1;
    QDomDocument doc = ConfFile::readConf(filename, result);
    std::cout << (doc.toString()).toStdString() << std::endl;
    if(result!=0) setConf(doc);
}

void MainWindow::saveConf(){
    QString filename = QFileDialog::getSaveFileName(this,
                  tr("Zapisz konfigurację"), "", tr("Plik XML (*.xml)"));
    QDomDocument doc = getConvTool().document();
    std::cout << (doc.toString()).toStdString() << std::endl;
    ConfFile::saveConf(doc,filename);
    setConf(doc);
}
void MainWindow::about(){
    QMessageBox::about(this,"O programie",QString()+"<h4>Konwersja do odcieni szarości</h4>"
                       "<p>Program wykonany w 2017 roku</p>");
}

void MainWindow::aboutQt(){
    QMessageBox::aboutQt(this,"O Qt");
}

void MainWindow::help(){
    QMessageBox::about(this,"Pomoc",QString()+"<h4>Konwersja do odcieni szarości</h4>"
                                              "<p>Program oferuje obsługę odczytu i zapisu trzech typów plików: BMP, PNG oraz JPG</p>"
                                              "<p>Oferowane są następujące funkcje:</p>"
                                              "<p>Wybór typu konwersji - normalną lub wzorowaną na konwersji z programu Gimp</p>"
                                              "<p>Mikser kanałów - wybór proporcji pomiędzy trzema kanałami, wartości procentowe"
                                                                           ", od -200% do 200%</p>"
                                              "<p>Bichromia - możliwość zastosowania w obrazie wybranego odcienia zamiast"
                                                                           "odcienia szarości, suwakiem wybieramy odcień</p>"
                                              "<p>Selekcja barwy - pozostawienie wybranego odcienia na obrazku"
                                                                           "<br>z redukcją odcieni do jednego lub z zachowaniem odcienia</p>"
                                                                           ""
                                              "<p>Mieszanie - wybór proporcji mieszania obrazu przed i po konwersji, % obrazu po konwersji</p>"
                                              "<p>Możliwość zachowania konfiguracji parametrów w pliku XML późniejszego wczytania</p>"
                                             );
}
