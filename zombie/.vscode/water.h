#include "item.h"
#include <sstream>
#include <fstream>

class button;

class water: public item{
    private:
        int thirst_quenched;
        button * drink;
    public:
        water(int x, int y, int space, string name, int thirst_quenched);
        bool pressed();
        int get_thirst_quenched();
        void shift(int y) override;
        void change_position(int x, int y) override;
        void draw() override;
        virtual void change_file(ofstream & myFile) override;
        static water * read_file(stringstream & ss);
};