#ifndef _BUTTON_LISTENER_H
#define _BUTTON_LISTENER_H

#include <string>

class ButtonListener {
public:
    virtual void buttonPressed(std::string buttonCode) = 0;
};

#endif