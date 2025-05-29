#ifndef _I_InteractableWidget_H_
#define _I_InteractableWidget_H_

class I_InteractableWidget
{
public:
    I_InteractableWidget() = default;
    virtual ~I_InteractableWidget() = default;
    
    virtual void onWidgetSelected() = 0;
    virtual void onWidgetUnSelected() = 0;
    virtual void onXPressed() = 0;
    virtual void onYPressed() = 0;
    virtual void onBPressed() = 0;
    virtual void onAPressed() = 0;
};

#endif