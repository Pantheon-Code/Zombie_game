#include "item.h"

class button;

class food : public item{
    private:
        int hunger_restored;
        button * eat;
    public:
        food(int x, int y, int space, string name, int hunger_restored);
        bool pressed();
        int get_hunger_restored();
        void shift(int y) override;
        void change_position(int x, int y) override;
        void draw() override;
        virtual void change_file(ofstream & myFile) override;
        static food * read_file(stringstream & ss);
};