#include <IO_API/IO_API.h>
#include <EntityObject.h>
#include <EntityObjectLoader.h>

struct Widget {
    static int mouseX, mouseY;
    static bool leftMousePressed;
    static bool leftMouseClicked;
    static std::vector<Widget*> widgets;
    size_t id;
    int x, y, w, h;
    void(*onClicked)() = 0;

    static Widget* createNew(int _x, int _y, int _w, int _h) {
        Widget* retValue = (Widget*)malloc(sizeof(Widget));
        retValue->x = _x, retValue->y = _y, retValue->w = _w, retValue->y = _y;
        retValue->id = widgets.size();
        widgets.push_back(retValue);
        return retValue;
    }
    static void destruct(Widget* widget) {
        widgets[widget->id] = widgets[widgets.size() - 1];
        widgets[widget->id]->id = widget->id;
        free(widget);
        widgets.pop_back();
    }

    static void update(int _mouseX, int _mouseY, bool _leftMousePressed) {
        mouseX = _mouseX;
        mouseY = _mouseY;
        if (leftMousePressed == false && _leftMousePressed == true) {
            leftMouseClicked = true;
            leftMousePressed = _leftMousePressed;
            return;
        }
        if (leftMousePressed == true) {
            leftMouseClicked = false;
        }
        leftMousePressed = _leftMousePressed;

        for (Widget* w : widgets) {
            if (pointInWidget(w, mouseX, mouseY)) {
                if (leftMouseClicked)
                    if (w->onClicked != 0)
                        w->onClicked();
            }
        }
    }
private:
    static bool pointInWidget(Widget* self, int px, int py) {
        if (px > self->x + self->w || px < self->x ||
            py > self->y + self->h || py < self->y)
            return false;
        return true;
    }
};

int Widget::mouseX = 0;
int Widget::mouseY = 0;
bool Widget::leftMousePressed = false;
bool Widget::leftMouseClicked = false;
std::vector<Widget*> Widget::widgets = std::vector<Widget*>();

Widget* button = Widget::createNew(64, 64, 64, 64);



void appStart() {
    EntityObject player = EntityObjectLoader::createEntityObjectFromFile("data/entities/Reimu.txt");

    ComponentObject* size = player.getComponent("size");
    ComponentObject* texture = player.getComponent("texture");
    ComponentObject* health = player.getComponent("health");
    uint32_t* arr = size->getArrayInt();
    for (uint32_t i = 0; i < size->getArrayIntLen(); i++)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
    std::cout << texture->getString() << std::endl;
    std::cout << health->getInt() << std::endl;
}
void appLoop() {
    int mx, my;
    getMouseCanvasPos(&mx, &my);
    uint8_t leftMouseButton;
    getMouseState(&leftMouseButton, NULL, NULL);
    Widget::update(mx, my, leftMouseButton);
}
void appEnd() {
	
}