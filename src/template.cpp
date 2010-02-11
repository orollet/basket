#ifndef TEMPLATE_CPP
#define TEMPLATE_CPP

#include <QDomElement>


#include "template.h"
#include "xmlwork.h"
#include "global.h"

Template::Template()
        : m_fileName("")
        , m_icon("basket")
        , m_backgroundImage("")
        , m_backgroundColor()
        , m_textColor()
        , m_mindMap(false)
        , m_freeLayout(false)
        , m_columnsCount(1)

{
}


Template::Template(const QString &fileName)
        : m_fileName("")
        , m_icon("basket")
        , m_backgroundImage("")
        , m_backgroundColor()
        , m_textColor()
        , m_mindMap(false)
        , m_freeLayout(false)
        , m_columnsCount(1)

{
    this->loadTemplate(fileName);

}



bool Template::loadTemplate(const QString &fileName ){
    QDomDocument *document  = XMLWork::openFile("basket", Global::templatesFolder()+ fileName);

    if(document->isNull() ){
        return false;
    }

    m_fileName = fileName;

    QDomElement properties  = XMLWork::getElement(document->documentElement(), "properties");

    QDomElement iconElement = XMLWork::getElement(document->documentElement(), "icon");
    if(! iconElement.text().isEmpty()  ){
       m_icon= iconElement.text();
    }

    QDomElement appearanceElement = XMLWork::getElement(properties, "appearance");
    if(! appearanceElement.attribute("backgroundImage").isEmpty()){
       m_backgroundImage =appearanceElement.attribute("backgroundImage") ;
    }

    if(! appearanceElement.attribute("backgroundColor").isEmpty()){
       m_backgroundColor =  QColor( appearanceElement.attribute("backgroundColor"));
    }

    if(! appearanceElement.attribute("textColor").isEmpty()){
      m_textColor = QColor(appearanceElement.attribute("textColor"))  ;
    }

    QDomElement dispositionElement = XMLWork::getElement(properties, "disposition");
    if(! dispositionElement.attribute("mindMap").isEmpty()){
        m_mindMap  =   dispositionElement.attribute("mindMap")=="true"?true :false ;
    }

    if(! dispositionElement.attribute("free").isEmpty()){
        m_freeLayout  =   dispositionElement.attribute("free")=="true"?true :false ;
    }


    if(! dispositionElement.attribute("columnCount").isEmpty()){
       m_columnsCount  =   dispositionElement.attribute("columnCount").toInt();
    }


    return true;
}

#endif // TEMPLATE_CPP
