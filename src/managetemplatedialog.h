#ifndef MANAGETEMPLATEDIALOG_H
#define MANAGETEMPLATEDIALOG_H

#include <KDialog>

#include <QListWidget>
#include "template.h"

#include "namedialog.h"

class SingleSelectionKIconView : public QListWidget
{
    Q_OBJECT
public:
    SingleSelectionKIconView(QWidget *parent = 0);
    QMimeData* dragObject();
    QListWidgetItem* selectedItem() {
        return m_lastSelected;
    }
private slots:
    void slotSelectionChanged(QListWidgetItem *cur);
private:
    QListWidgetItem *m_lastSelected;


};



class ManageTemplateDialog: public KDialog
{
Q_OBJECT
public:
    ManageTemplateDialog();
    ~ManageTemplateDialog();

   void show();

   void addTemplateWidget(const QString &name )  ;

signals:
   void listChanged();

protected slots:
 //  void  accept();
   void slotOk();
   void deleteTemplate();
   void copyTemplate();
   void doCopyTemplate();


private :
QListWidget *m_templates;
  QMap<QString, Template*>  m_templatesMap;
  NameDialog *m_nameDlg;

 bool m_listHasChanged ;

};




#endif // MANAGETEMPLATEDIALOG_H
