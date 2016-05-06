/*
 * GroupBox.h
 *
 *  Created on: 26 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../CTexture.h"
#include <vector>
using std::vector;
class GroupBox: public CTexture
{
public:
	GroupBox();
	~GroupBox();
    bool addChild(CTexture* const child, bool vertical = false);
    bool removeChild(CTexture* const child);
    virtual void draw() override;
private:

    vector<CTexture*> children;
};

