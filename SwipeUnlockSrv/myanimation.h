#ifndef MYANIMATION_H
#define MYANIMATION_H

#include <QVariantAnimation>


class MyAnimation : public QVariantAnimation
{
    Q_OBJECT
public:
     MyAnimation(){}

     virtual ~MyAnimation(){}

     void updateCurrentValue(const QVariant &value){
         emit valueChanged(value);
     }
};

#endif // MYANIMATION_H
