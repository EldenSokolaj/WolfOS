#include "types.h"

class port{
    protected:
        uint16_t portNum;
        port(uint16_t portNum);
        ~port();
};

class port8bit : public port {
    public:
        port8bit(uint16_t portNum);
        ~port8bit();
        virtual void write(uint8_t data);
        virtual uint8_t read();
};

class port8bitSlow : public port8bit {
    public:
        port8bitSlow(uint16_t portNum);
        ~port8bitSlow();
        virtual void write(uint8_t data);
};

class port16bit : public port {
    public:
        port16bit(uint16_t portNum);
        ~port16bit();
        virtual void write(uint16_t data);
        virtual uint16_t read();
};

class port32bit : public port {
    public:
        port32bit(uint16_t portNum);
        ~port32bit();
        virtual void write(uint32_t data);
        virtual uint32_t read();
};