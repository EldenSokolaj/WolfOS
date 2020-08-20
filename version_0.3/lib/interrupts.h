#include "types.h"
#include "port.h"
#include "gdt.h"

class interruptManager{

    protected:
    struct gateDescriptor {
        uint16_t handlerLo;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;
        uint8_t access;
        uint16_t handlerHi;
        }__attribute((packed));
    
    static gateDescriptor IDT[256];

    struct IDTpointer {
        uint16_t size;
        uint32_t base;
    }__attribute((packed));

    static void setIDTentry(
        uint8_t interruptNumber,
        uint32_t codeSegmentSelector,
        void (*handler)(),
        uint8_t discriptorAccess,
        uint8_t discriptorType
    );

    port8bitSlow picMasterCommand;
    port8bitSlow picMasterData;
    port8bitSlow picWorkerCommand;
    port8bitSlow picWorkerData;

    public:

    interruptManager(GDT* gdt);
    ~interruptManager();

    static uint32_t handle(uint8_t interruptNum, uint32_t esp); 

    void activate();
    void deactivate();
    
    static void IgnoreInterruptRequest();
    
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();

        static void HandleException0x00();
        static void HandleException0x01();
};