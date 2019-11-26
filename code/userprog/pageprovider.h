#ifdef CHANGED

#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"

#define ALEATORY_STRATEGY

class PageProvider : dontcopythis
{
public:
    PageProvider();

    ~PageProvider();

    int GetEmptyPage();

    void ReleasePage(int addr);

    int NumAvailPage();

private:
    BitMap pagesBitMap;
};

#endif // PAGEPROVIDER_H

#endif //CHANGED