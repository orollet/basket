#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <KDE/KLocale>
#include <KDE/KConfig>
#include <KDE/KVBox>

#include "namedialog.h"



NameDialog::NameDialog(const QString &name, const QString &caption, const QString &labeltext  )
        : KDialog()
{

    setObjectName(name);
    setModal(true);
    setCaption(caption);
    setButtons(Ok | Cancel);
    setDefaultButton(Ok);
   showButtonSeparator(true);

    connect(this, SIGNAL(okClicked()), SLOT(slotOk()));

    QWidget *page = new QWidget(this);
    QVBoxLayout *topLayout = new QVBoxLayout(page);



    QHBoxLayout *hLayout = new QHBoxLayout ;

    QLabel *lName = new QLabel();
    lName->setText(labeltext);

    lName->setMinimumWidth(lName->fontMetrics().maxWidth() * 3);


    //hLayout.addWidget();

    m_templateName= new QLineEdit( );
    m_templateName->setText(name);


    m_templateName->setMinimumWidth(m_templateName->fontMetrics().maxWidth()*7);

    m_templateName->setBaseSize(m_templateName->fontMetrics().maxWidth()*7, m_templateName->fontMetrics().height() +5);


    lName->setBuddy(m_templateName);

    hLayout->addWidget(lName  );
    hLayout->addWidget(m_templateName );

    topLayout->addLayout(hLayout);





    page->adjustSize();

    setMainWidget(page);

    this->adjustSize();

}


NameDialog::~NameDialog(){

}



void NameDialog::show(){

    KDialog::show();

}

QString NameDialog::getName()
{
    return m_templateName->text();
}


void NameDialog::slotOk(){



}
