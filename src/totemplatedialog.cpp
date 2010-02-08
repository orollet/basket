#include "totemplatedialog.h"
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <KDE/KLocale>
#include <KDE/KConfig>
#include <KDE/KVBox>

#include "exporterdialog.h"
#include "basketview.h"
#include "global.h"

#include "templatefactory.h"


ToTemplateDialog::ToTemplateDialog(BasketView *basket,  const QString &name)
        : KDialog()
        , m_basket(basket)
{

    setObjectName("toTemplate");
    setModal(true);
    setCaption(i18n("Create new template from basket"));
    setButtons(Ok | Cancel);
    setDefaultButton(Ok);
   showButtonSeparator(true);

    connect(this, SIGNAL(okClicked()), SLOT(slotOk()));

    QWidget *page = new QWidget(this);
    QVBoxLayout *topLayout = new QVBoxLayout(page);



    QHBoxLayout *hLayout = new QHBoxLayout ;

    QLabel *lName = new QLabel();
    lName->setText("template name :");

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


ToTemplateDialog::~ToTemplateDialog(){

}



void ToTemplateDialog::show(){

    KDialog::show();

}




void ToTemplateDialog::slotOk(){

    TemplateFactory::packTemplate(m_templateName->text());

//s     if (Global::mainWindow()) Global::mainWindow()->show();
//

}
