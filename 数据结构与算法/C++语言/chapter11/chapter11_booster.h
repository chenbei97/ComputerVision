#pragma once
#ifndef chapter11_booster_
#define chapter11_booster_
#include <ostream>
using namespace std;
struct booster
{
    int degradeToLeaf,           // degradation to leaf
        degradeFromParent;       // degradation from parent
    bool boosterHere;            // true iff booster here
    void output(ostream& out) const
    {
        out << boosterHere << "  " << degradeToLeaf <<"  "
            << degradeFromParent << "  ";
    }
};
inline ostream& operator<<(ostream& out, booster x)
{
    x.output(out); return out;
}
#endif // !chapter11_booster_
