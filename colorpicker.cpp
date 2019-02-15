#include "colorpicker.h"

ColorPicker::ColorPicker(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    buttonbleu = new ColorButton(bleuHighlighted, bleu, bleuSelectedHighlighted, bleuSelected, WIDTH, HEIGHT, this);
    buttonbleuClair1 = new ColorButton(bleuClair1Highlighted, bleuClair1, bleuClair1SelectedHighlighted, bleuClair1Selected, WIDTH, HEIGHT, this);
    buttonbleuClair2 = new ColorButton(bleuClair2Highlighted, bleuClair2, bleuClair2SelectedHighlighted, bleuClair2Selected, WIDTH, HEIGHT, this);
    buttonbleuClair3 = new ColorButton(bleuClair3Highlighted, bleuClair3, bleuClair3SelectedHighlighted, bleuClair3Selected, WIDTH, HEIGHT, this);
    buttonbleuGris = new ColorButton(bleuGrisHighlighted, bleuGris, bleuGrisSelectedHighlighted, bleuGrisSelected, WIDTH, HEIGHT, this);
    buttongris = new ColorButton(grisHighlighted, gris, grisSelectedHighlighted, grisSelected, WIDTH, HEIGHT, this);
    buttonjaune = new ColorButton(jauneHighlighted, jaune, jauneSelectedHighlighted, jauneSelected, WIDTH, HEIGHT, this);
    buttonjauneFonce = new ColorButton(jauneFonceHighlighted, jauneFonce, jauneFonceSelectedHighlighted, jauneFonceSelected, WIDTH, HEIGHT, this);
    buttonmagenta = new ColorButton(magentaHighlighted, magenta, magentaSelectedHighlighted, magentaSelected, WIDTH, HEIGHT, this);
    buttonmarron = new ColorButton(marronHighlighted, marron, marronSelectedHighlighted, marronSelected, WIDTH, HEIGHT, this);
    buttonnoir = new ColorButton(noirHighlighted, noir, noirSelectedHighlighted, noirSelected, WIDTH, HEIGHT, this);
    buttonorange = new ColorButton(orangeHighlighted, orange, orangeSelectedHighlighted, orangeSelected, WIDTH, HEIGHT, this);
    buttonorangeClair = new ColorButton(orangeClairHighlighted, orangeClair, orangeClairSelectedHighlighted, orangeClairSelected, WIDTH, HEIGHT, this);
    buttonrose = new ColorButton(roseHighlighted, rose, roseSelectedHighlighted, roseSelected, WIDTH, HEIGHT, this);
    buttonrouge = new ColorButton(rougeHighlighted, rouge, rougeSelectedHighlighted, rougeSelected, WIDTH, HEIGHT, this);
    buttonvert = new ColorButton(vertHighlighted, vert, vertSelectedHighlighted, vertSelected, WIDTH, HEIGHT, this);
    buttonvertClair = new ColorButton(vertClairHighlighted, vertClair, vertClairSelectedHighlighted, vertClairSelected, WIDTH, HEIGHT, this);
    buttonvertFonce = new ColorButton(vertFonceHighlighted, vertFonce, vertFonceSelectedHighlighted, vertFonceSelected, WIDTH, HEIGHT, this);
    buttonvertJaune = new ColorButton(vertJauneHighlighted, vertJaune, vertJauneSelectedHighlighted, vertJauneSelected, WIDTH, HEIGHT, this);
    buttonviolet = new ColorButton(violetHighlighted, violet, violetSelectedHighlighted, violetSelected, WIDTH, HEIGHT, this);

    initGridColor();

    connect(buttonbleu, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonbleuClair1, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonbleuClair2, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonbleuClair3, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonbleuGris, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttongris, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonjaune, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonjauneFonce, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonmagenta, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonmarron, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonnoir, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonorange, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonorangeClair, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonrose, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonrouge, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonvert, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonvertClair, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonvertFonce, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonvertJaune, SIGNAL(clicked()), this, SLOT(chooseColor()));
    connect(buttonviolet, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

ColorPicker::~ColorPicker(){
    smartDeleteMrNovelli(buttonbleu);
    smartDeleteMrNovelli(buttonbleuClair1);
    smartDeleteMrNovelli(buttonbleuClair2);
    smartDeleteMrNovelli(buttonbleuClair3);
    smartDeleteMrNovelli(buttonbleuGris);
    smartDeleteMrNovelli(buttongris);
    smartDeleteMrNovelli(buttonjaune);
    smartDeleteMrNovelli(buttonjauneFonce);
    smartDeleteMrNovelli(buttonmagenta);
    smartDeleteMrNovelli(buttonmarron);
    smartDeleteMrNovelli(buttonnoir);
    smartDeleteMrNovelli(buttonorange);
    smartDeleteMrNovelli(buttonorangeClair);
    smartDeleteMrNovelli(buttonrose);
    smartDeleteMrNovelli(buttonrouge);
    smartDeleteMrNovelli(buttonvert);
    smartDeleteMrNovelli(buttonvertClair);
    smartDeleteMrNovelli(buttonvertFonce);
    smartDeleteMrNovelli(buttonvertJaune);
    smartDeleteMrNovelli(buttonviolet);
}

void ColorPicker::initGridColor(){
    gridColor->addWidget(buttonrouge,0,0);
    gridColor->addWidget(buttonrose,0,1);
    gridColor->addWidget(buttonmagenta,0,2);
    gridColor->addWidget(buttonviolet,0,3);
    gridColor->addWidget(buttonbleu,0,4);
    gridColor->addWidget(buttonvert,1,0);
    gridColor->addWidget(buttonvertFonce,1,1);
    gridColor->addWidget(buttonbleuClair1,1,2);
    gridColor->addWidget(buttonbleuClair2,1,3);
    gridColor->addWidget(buttonbleuClair3,1,4);
    gridColor->addWidget(buttonvertClair,2,0);
    gridColor->addWidget(buttonvertJaune,2,1);
    gridColor->addWidget(buttonjaune,2,2);
    gridColor->addWidget(buttonjauneFonce,2,3);
    gridColor->addWidget(buttonorangeClair,2,4);
    gridColor->addWidget(buttonnoir,3,0);
    gridColor->addWidget(buttonbleuGris,3,1);
    gridColor->addWidget(buttongris,3,2);
    gridColor->addWidget(buttonmarron,3,3);
    gridColor->addWidget(buttonorange,3,4);
}

void ColorPicker::deselectAll(){
    for(int i = 0; i < gridColor->rowCount(); i++){
        for(int j = 0; j < gridColor->columnCount(); j++){
            ColorButton* x = dynamic_cast<ColorButton*>(gridColor->itemAtPosition(i, j)->widget());
            x->setSelected(false);
        }
    }
}

void ColorPicker::chooseColor(){
    deselectAll();
    currentColor = dynamic_cast<ColorButton*>(sender());
    currentColor->setSelected(true);
    emit aboutToChoose();
}
