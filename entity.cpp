#include "entity.h"

Entity::Entity(const std::string& tpath, int x1,int y1,int w1,int h1, int x2,int y2,int w2,int h2, bool flipable): 
srcrect({x1,y1,w1,h1}),
dstrect({x2,y2,w2,h2}),
angle(0.0),
center(),
flip(NO_FLIP){


}

~Entity(){

}
