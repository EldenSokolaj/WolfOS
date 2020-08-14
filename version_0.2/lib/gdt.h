#include "types.h"

class GDT{
public:
    class DiscriptorSegment{
        private:
            uint16_t limit_lo;
            uint16_t base_lo;
            uint8_t base_hi;
            uint8_t type;
            uint8_t flags_limit_hi;
            uint8_t base_vhi;
        public:
            DiscriptorSegment(uint32_t base, uint32_t limit, uint8_t type);
            uint32_t Base();
            uint32_t Limit();
    }__attribute__((packed));

DiscriptorSegment nullSegmentSelector;
DiscriptorSegment unusedSegmentSelector;
DiscriptorSegment codeSegmentSelector;
DiscriptorSegment dataSegmentSelector;

public:
GDT();
~GDT();

uint16_t CodeSegmentSelector();
uint16_t DataSegmentSelector();
};
