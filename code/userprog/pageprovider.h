#ifdef CHANGED

#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"
#include "filesys.h"
#include "translate.h"
#include "list.h"

class PageProvider : dontcopythis
{

public:
    PageProvider();
    ~PageProvider();

    int GetEmptyPage();
    void ReleasePage();
    int NumAvailPage();

private:
    TranslationEntry *pageTable;
    BitMap pagesBitMap;
};

#endif // PAGEPROVIDER_H

#endif //CHANGED