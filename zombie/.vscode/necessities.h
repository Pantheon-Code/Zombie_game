#include "food.h"
#include "water.h"

class health_editor;
class inventory;

class necessities{
    private:
    int x = 630, y = 340;
    health_editor * hunger = nullptr;
    health_editor * thirst = nullptr;
    inventory * inventory1;
    public:
    necessities(inventory * inventory1);
    void update();
    void consume(item * to_consume);
    void draw();
};