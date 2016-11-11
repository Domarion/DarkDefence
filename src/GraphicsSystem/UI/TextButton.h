/*
 * TextButton.h
 *
 *  Created on: 18 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <functional>
#include "Label.h"
#include "../../Input/InputHandler.h"



class TextButton: public Label, public InputHandler
{
public:
    TextButton();
    virtual ~TextButton();
    virtual bool onClick(Position point) override;

    virtual void ConnectMethod(std::function<void(std::string)> method);

protected:
    std::function<void(std::string)> connectedMethod;

};

