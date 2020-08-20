#include "types.h"

//I think that the current problum is that I am loading class Discriptor Segment as GDT not struct entry

class GDT{

enum gdtSegment {null, unused, code, data};

public:
    struct entry{
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_hi;
    uint8_t type;
    uint8_t limit_hi;
    uint8_t base_vhi;
    }__attribute((packed));

    struct gdtPtr{
    uint16_t limit;
    uint32_t base;
    }__attribute((packed));

int setEntry(uint32_t base, uint32_t limit, uint8_t type, gdtSegment target);
uint32_t Base(gdtSegment targetSegment);
uint32_t Limit(gdtSegment targetSegment);

entry gdt[4];

/*              Segment discriptions
gdt[0] = null
gdt[1] = unused
gdt[2] = code
gdt[3] = data
*/

public:
GDT();
~GDT();

uint32_t CodeSegmentSelector();
uint32_t DataSegmentSelector();
};