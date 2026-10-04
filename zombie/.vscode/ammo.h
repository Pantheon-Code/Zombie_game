#include "item.h"

class ammo: public item{
    private:
    int amount = 0;
    public:
    ammo(int x, int y, int space, string name, int amount);
    int get_amount();
    void draw() override;
};