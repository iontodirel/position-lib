
#include "use_in_tu.h"

int main()
{
    position::position_dd pos;
    (void)pos.lat;
    (void)pos.lon;

    position::format(pos, position::position_dd_format);

    return 0;
}
