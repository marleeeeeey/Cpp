#include "AllInclude.h"

typedef short Type;

Type getValue(const std::vector<Type> & vars)
{
    Type res = 0;

    for (auto it = vars.begin(); it != vars.end(); ++it)
    {
        Type v = *it;
        Type prevRes = res;
        res = res ^ v;

        std::ostringstream os;
        os
            << std::setfill('0') << std::hex
            << std::setw(4) << prevRes << " ^ "
            << std::setw(4) << v << " = "
            << std::setw(4) << res
            ;

        //AMSG(os.str());
    }

    return res;
}

int main()
{
    AVAR(getValue({ 2, 3, 4, 5, 6, 3, 4, 5, 2 }));
    AVAR(getValue({ 6, 2, 2, 7 }));
    AVAR(getValue({ 6, 2, 2, 7, 1 }));
    AVAR(getValue({ 6, 2, 2, 1 }));



    APAUSE;
}