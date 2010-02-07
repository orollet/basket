
#include <QDir>
#include <QTextStream>
#include <KDE/KLocale>
#include <KDE/KMessageBox>
#include <QDomElement>

#include "templatefactory.h"

#include "basketview.h"
#include "global.h"
#include "xmlwork.h"
#include "bnpview.h"


QString TemplateFactory::packTemplate(const QString &templateName)
{
    // Find a name for a new folder and create it:
 //   QString folderName = newFolderName();
  //  QString fullPath   = Global::basketsFolder() + folderName;

    QString fileName = templateName;
    QString fullPath   = Global::templatesFolder();

    QDir dir;

    if( ! dir.exists(fullPath) ){
        if (!dir.mkdir(fullPath)) {
            KMessageBox::error(/*parent=*/0, i18n("Sorry, but the templates folder creation has failed."), i18n("Template Creation Failed"));
        return "";
     }
    }
    // Pack the template file to the template folder :
    // TODO: REALLY unpack (this hand-creation is temporary, or it could be used in case the template can't be found)
    QFile file(fullPath +fileName+ ".xml");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        BasketView *currentBasket = Global::bnpView->currentBasket();
        int nbColumns =  currentBasket->columnsCount();


        int columnWidth = (currentBasket && nbColumns > 0 ? (currentBasket->visibleWidth() - (nbColumns - 1) * Note::RESIZER_WIDTH) / nbColumns : 0);
        stream << QString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                          "<!DOCTYPE basket>\n"
                          "<basket>\n"
                          " <properties>\n"
                          "<icon>%7</icon>\n"
                          " <appearance backgroundColor=\"%4\" backgroundImage=\"%5\" textColor=\"%6\"/>\n "
                          "  <disposition mindMap=\"%1\" columnCount=\"%2\" free=\"%3\" />\n"
                          " </properties>\n"
                          " <notes>\n").arg((templateName == "mindmap" ? "true" : "false"),
                                            QString::number(nbColumns),
                                            (currentBasket->isFreeLayout() ? "true":"false"),
                                            currentBasket->backgroundColor().name(),
                                            currentBasket->backgroundImageName(),
                                            currentBasket->textColor().name(),
                                            currentBasket->icon()   );
        if (nbColumns > 0)
            for (int i = 0; i < nbColumns; ++i)
                stream << QString("  <group width=\"%1\"></group>\n").arg(columnWidth);
        stream << " </notes>\n"
        "</basket>\n";
        file.close();
        return fileName;
    } else {
        KMessageBox::error(/*parent=*/0, i18n("Sorry, but the template copying for this new basket has failed."), i18n("Basket Creation Failed"));
        return "";
    }
}
