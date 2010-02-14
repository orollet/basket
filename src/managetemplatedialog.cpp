
#include "managetemplatedialog.h"



#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <KDE/KLocale>
#include <KDE/KConfig>
#include <KDE/KVBox>

#include <KDE/KDebug>

#include "exporterdialog.h"
#include "basketview.h"
#include "global.h"

#include "templatefactory.h"

#include "template.h"

#include "copytemplatedialog.h"

#include <QListWidgetItem>
#include <QPushButton>
#include <QPixmap>
#include <QDir>

#include <QListWidgetItem>
#include <QStringList>

#include <QPainter>

#include "namedialog.h"



ManageTemplateDialog::ManageTemplateDialog()
        : KDialog()

{

    setObjectName("ManageTemplate");
    setModal(true);
    setCaption(i18n("Manage template"));
    setButtons(Ok | Cancel);
    setDefaultButton(Ok);
    showButtonSeparator(true);

    connect(this, SIGNAL(okClicked()), SLOT(slotOk()));

    QWidget *page = new QWidget(this);
    QVBoxLayout *topLayout = new QVBoxLayout(page);

    m_listHasChanged = false;

    QHBoxLayout *hLayout = new QHBoxLayout ;

    QLabel *lName = new QLabel();
    lName->setText("template name :");

    lName->setMinimumWidth(lName->fontMetrics().maxWidth() * 3);


    topLayout->addLayout(hLayout);


    m_templates = new SingleSelectionKIconView(page);
    m_templates->setSelectionMode(QAbstractItemView::SingleSelection);

    QString templatePath   = Global::templatesFolder();
    QDir mtemplateDir(templatePath);
    QStringList filters;

    filters << "*.xml";
    mtemplateDir.setNameFilters(filters);

    QStringList tempList = mtemplateDir.entryList();


    QListWidgetItem *lastTemplate = 0;
    QPixmap icon(40, 53);



     m_templates->setViewMode(QListView::ListMode);


     for(int i=0; i< tempList.size() ; i++){
        this->addTemplateWidget(tempList.at(i));
    }

    hLayout->addWidget(m_templates);
    QWidget *col2 = new QWidget();
    hLayout->addWidget(col2);


    QVBoxLayout *col2Layout = new QVBoxLayout(col2);


    col2Layout->addWidget(lName);

    QPushButton *delTemplateButton = new QPushButton("Delete", this);
    connect(delTemplateButton,  SIGNAL(clicked()), this, SLOT(deleteTemplate()))   ;
    col2Layout->addWidget(delTemplateButton);

    QPushButton *copyTemplateButton = new QPushButton("Copy", this);
    connect(copyTemplateButton,  SIGNAL(clicked()), this, SLOT(copyTemplate()))   ;
    col2Layout->addWidget(copyTemplateButton);

    page->adjustSize();

    setMainWidget(page);

    this->adjustSize();

}


ManageTemplateDialog::~ManageTemplateDialog(){

}



void ManageTemplateDialog::show(){

    KDialog::show();

}




void ManageTemplateDialog::slotOk(){

 if (m_listHasChanged) emit listChanged();

}

void ManageTemplateDialog::deleteTemplate(){

     if (m_templates->selectedItems().isEmpty()) return;

     // suppress it physically
     QListWidgetItem *item = ((SingleSelectionKIconView*)m_templates)->selectedItem();
     kDebug()<<"delete template " << item->text() <<"\n";
     TemplateFactory::deleteTemplate(item->text());
     //remove it from the list
     m_templates->takeItem(m_templates->currentRow());


}

void ManageTemplateDialog::copyTemplate(){
     kDebug()<<"copy template\n";

    if (m_templates->selectedItems().isEmpty()) return;


    QListWidgetItem *item = ((SingleSelectionKIconView*)m_templates)->selectedItem();

    m_nameDlg = new NameDialog("copyTemplate", "Copying template " +item->text() , "New template name");
    connect(m_nameDlg, SIGNAL(okClicked()),this, SLOT(doCopyTemplate()));
    m_nameDlg->show();

    m_listHasChanged = true;

}


void ManageTemplateDialog::doCopyTemplate(){
     kDebug()<<"copy template\n";
     QListWidgetItem *item = ((SingleSelectionKIconView*)m_templates)->selectedItem();

    TemplateFactory::copyTemplate(item->text(), m_nameDlg->getName());

    //add it to the list

    this->addTemplateWidget(m_nameDlg->getName());

    m_listHasChanged = true;
}


void ManageTemplateDialog::addTemplateWidget(const QString &name){

    Template *tmplate = new Template(name);
    m_templatesMap.insert(name, tmplate );

    QListWidgetItem *lastTemplate = 0;
    QPixmap icon(40, 53);

    QPainter painter(&icon);

    painter.begin(&icon);

    painter.setPen(palette().color(QPalette::Text));
    painter.drawRect(0, 0, icon.width(), icon.height());

    painter.fillRect(0, 0, icon.width(), icon.height(),tmplate->backgroundColor()  );
    QPixmap pixie( Global::backgroundsFolder()+"/previews/"+ tmplate->backgroundImage() );
    painter.drawPixmap(0,0, icon.width(), icon.height(), pixie );

    painter.setPen(palette().color(QPalette::Text));
    painter.drawRect(0, 0, icon.width(), icon.height());


    if( tmplate->columnsCount() >1  ) {
        for (int j=1 ; j<tmplate->columnsCount(); j++ ){
            painter.drawLine(icon.width() * j / tmplate->columnsCount(), 0, icon.width() * j / tmplate->columnsCount(), icon.height());
        }

    }else {
        painter.drawRect(icon.width() / 5, icon.width() / 5, icon.width() / 4, icon.height() / 8);
        painter.drawRect(icon.width() * 2 / 5, icon.width() * 2 / 5, icon.width() / 4, icon.height() / 8);
    }

    painter.end();
    lastTemplate = new QListWidgetItem(icon, name, m_templates);

}
