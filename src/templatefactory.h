#ifndef TEMPLATEFACTORY_H
#define TEMPLATEFACTORY_H
class QString;

class TemplateView;

/** Methods to create various baskets (mkdir, init the properties and load it).
  * @author Sébastien Laoût
  */
namespace TemplateFactory
{
/** You should use this method to create a new basket: */
void newTemplate(const QString &icon,
               const QString &name,
               const QString &backgroundImage,
               const QColor  &backgroundColor,
               const QColor  &textColor,
               const QString &templateName
       );
/** Internal tool methods to process the method above: */
//QString newFolderName();
QString packTemplate(const QString &templateName);

void deleteTemplate(const QString &templateName);

void copyTemplate(const QString &sourceTemplate,  const QString &destTemplate );

}

#endif // TEMPLATEFACTORY_H
