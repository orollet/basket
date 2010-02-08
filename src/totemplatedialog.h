#ifndef TOTEMPLATEDIALOG_H
#define TOTEMPLATEDIALOG_H

#include <KDialog>

#include <QLineEdit>

class QString;

class BasketView;

/**
 @author : Olivier Rollet (o.rollet@gmail.com)
*/

class ToTemplateDialog: public KDialog
{
Q_OBJECT
public:
    ToTemplateDialog(BasketView *basket,  const QString &name);
    ~ToTemplateDialog();
 QString toTemplateName();
   void show();
protected slots:
 //  void  accept();
   void slotOk();
private :
    BasketView *m_basket;
    QLineEdit *m_templateName;


};
#endif // TOTEMPLATEDIALOG_H
