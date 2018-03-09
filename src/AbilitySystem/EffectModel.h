#pragma once

#include <list>
#include <string>
#include <utility>

using std::list;
using std::string;
using std::pair;

class EffectModel
{
public:
    virtual ~EffectModel() = default;
    bool addMiniEffect(pair<string, double> & mini);
    bool removeMiniEffect(pair<string, double> & mini);
    const list<pair<string, double> > & getAffectedAttributes() const;
    string getCaption() const;
    void setCaption(const string &value);

    double getRunningTime() const;
    void setRunningTime(double value);
    void setDuration(double value);
    void setDurationModifier(double value);
    double getDuration() const;

private:
    list< pair<string, double>> affectedAttributes;
    pair<double, double> duration {0, 0};
    double runningTime{0};
    string caption;
};
