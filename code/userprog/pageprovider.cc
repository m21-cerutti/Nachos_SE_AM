#ifdef CHANGED

#include "system.h"
#include "pageprovider.h"
#include "synch.h"

static Semaphore *accessPages;

PageProvider::PageProvider()
    : pagesBitMap(NumPhysPages)
{
    accessPages = new Semaphore("access pageProvider", 1);
}

PageProvider::~PageProvider()
{
    delete accessPages;
}

int PageProvider::GetEmptyPage()
{
    ASSERT(NumAvailPage() != 0);

    accessPages->P();
    
    #ifdef ALEATORY_STRATEGY
    int freePage = rand() % NumPhysPages;
    if(! pagesBitMap.Test(freePage))
    {
        freePage = pagesBitMap.Find();
    }
    #else
    int freePage = pagesBitMap.Find();
    #endif //ALEATORY_STRATEGY

    pagesBitMap.Mark(freePage);

    accessPages->V();

    memset(&(machine->mainMemory[freePage * PageSize]), 0, PageSize);
    return freePage;
}

void PageProvider::ReleasePage(int addr)
{
    accessPages->P();
    pagesBitMap.Clear(addr);
    accessPages->V();
}

int PageProvider::NumAvailPage()
{
    return pagesBitMap.NumClear();
}

#endif //CHANGED