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
    if (pagesBitMap.Test(freePage))
    {
        DEBUG('p', "Get aleatory empty page %d/%d failed.\n",
              freePage, NumPhysPages);
        freePage = pagesBitMap.Find();
    }
#else
    int freePage = pagesBitMap.Find();
#endif //ALEATORY_STRATEGY

    pagesBitMap.Mark(freePage);
    int addrPhys = freePage * PageSize;
    DEBUG('p', "Get empty page %d/%d, \taddr phys \t0x%x.\n",
          freePage, NumPhysPages, addrPhys);
    accessPages->V();

    memset(&(machine->mainMemory[addrPhys]), 0, PageSize);
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