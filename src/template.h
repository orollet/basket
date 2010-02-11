#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QString>
#include <QColor>

class Template{


public :
   //constructors
  Template();
  Template(const QString &fileName);
  Template (     const QString &fileName,
                 const QString &icon,
                 const QString &backgroundImage,
                 const QColor  &backgroundColor,
                 const QColor  &textColor,
                 const QString &templateName,
                 const bool mindMap,
                 const bool freeLayout,
                 const int columnsCount);

  ~Template();
//
//private :
  bool loadTemplate(const QString &fileName );

private :
  QString m_fileName ;
  QString m_icon ;
  QString m_backgroundImage ;
  QColor  m_backgroundColor;
  QColor  m_textColor;
  QString m_templateName;
  bool m_mindMap;
  bool m_freeLayout;
  int m_columnsCount;

public :

// Getters

  QString fileName(){
      return m_fileName;
  }

  QString icon(){
      return m_icon ;
  }

  QString backgroundImage(){
      return m_backgroundImage;
  }

  QColor backgroundColor(){
      return m_backgroundColor;
  }

  QColor textColor(){
      return m_textColor;
  }

  QString templateName(){
      return m_templateName;
  }

  bool freeLayout(){
      return m_freeLayout;
  }

  bool disposition(){
    return m_mindMap;
  }

  int columnsCount(){
    return m_columnsCount;
 }

  // Setters

  void setIcon(const QString  &icon ){
       m_icon = icon;
  }

  void setBackgroundImage(const QString &image ){
      m_backgroundImage = image ;
  }

  void setBackgroundColor(const QColor &color ){
      m_backgroundColor = color ;
  }

  void setTextColor(const QColor &color ){
      m_textColor = color ;
  }

  void setTemplateName(const QString &name){
      m_templateName = name;
  }

  void setFreeLayout(const bool freeLayout){
      m_freeLayout = freeLayout;
  }

  void setMindMap(const bool mindmap){
      m_mindMap = mindmap ;
  }


  void setColumnCount(const int columnCount){
      m_columnsCount = columnCount;
  }


};


#endif // TEMPLATE_H
