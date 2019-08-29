#ifndef rendererManager_H
#define rendererManager_H


#include "Irenderer.h"
#include <vector>


class rendererManager {
public:
    //<SINGLETON>
    static IrenderEngine& getActual(){
        static  std::vector<IrenderEngine> renderers;
        return renderers[0];
    }
    //</SINGLETON>

private:
    


    //<SINGLETON>
    rendererManager();
    rendererManager(const rendererManager& orig);
    void operator=(rendererManager const& orig);
    //</SINGLETON>
};
#endif