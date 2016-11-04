#pragma once
#include "EffectReceiver.h"
#include "../Mob/MobModel.h"

class MobModel;
class MobEffectReceiver: public EffectReceiver
{
public:
    MobEffectReceiver();
    virtual ~MobEffectReceiver() = default;
    void init(std::shared_ptr<MobModel> modelPtr);

protected:
    virtual bool parseMethod(list<pair<string, double> > &attributes, int removeFlag) override;

private:
    std::shared_ptr<MobModel> mobModelPtr;

};
