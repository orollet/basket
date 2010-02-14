#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <KDialog>

#include <QLineEdit>

class QString;



/**
 @author : Olivier Rollet (o.rollet@gmail.com)
*/

class NameDialog: public KDialog
{
Q_OBJECT
public:
    NameDialog(const QString &name, const QString &caption, const QString &labeltext   );
    ~NameDialog();
 QString getName();
   void show();


protected slots:
 //  void  accept();
   void slotOk();
private :

    QLineEdit *m_templateName;


};


#endif // NAMEDIALOG_H
