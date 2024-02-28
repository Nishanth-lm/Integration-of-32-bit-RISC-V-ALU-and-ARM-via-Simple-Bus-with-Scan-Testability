#ifndef _PROPACK_H_
#define _PROPACK_H_

#include <string>
#include "systemc.h"


#define TESTMODE              0


#if TESTMODE 

    #define SLAVEBPIPRINTS    0
    #define SLAVEFUNPRINTS    0
    #define MASTERBPIPRINTS   0
    #define MASTERFUNPRINTS   0
    #define BUSPRINTS         0
    #define MAINPRINTS        1
    
#else    
    #define SLAVEBPIPRINTS    0
    #define SLAVEFUNPRINTS    1
    #define MASTERBPIPRINTS   0
    #define MASTERFUNPRINTS   0
    #define BUSPRINTS         0
    #define MAINPRINTS        1
    
#endif

#define ZERO              0
#define CARRYIN           1
#define LESSTHAN          2
#define CARRYOVERFLOW     3
#define NEGATIVE          4
#define DEFAULT           32

#define AND               0
#define OR                1
#define ADD               2
#define SUBTRACT          3
#define COMP_LESSTHAN     4
#define NOR               5

const sc_time armOp2Op(10, SC_NS); // time between instructions
const sc_time armSleep(100, SC_NS);
const sc_time rwAccess_t(1, SC_NS);
const sc_time rwReadDelay_t(1, SC_NS);
const sc_time rwWriteDelay_t(1, SC_NS);

// Data Bus
#define BITWIDTH         32
#define BYTESPERMEMLINE   4

// Address Bus
// 1010_1010_1010_1010_1010_1010_1010_1010
#define BUSWIDTHS        32//8    // #address bits
// 1010_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
#define BUSDECODEBITS     4//2    // #upper chip select decode bits
// xxxx_1010_1010_1010_1010_1010_1010_1010
#define BUSMEMINTBITS    28//6    //=32-4, #memory internal address bits
#define BUSTARGETMASK   0xF//0x3    // mask for the upper chip select decode bits
#define BUSDECODEMASK   0x0FFFFFFF//0x3F   // 7 Nibbles, mask for the memory internal address bits
// END: Address Bus


#define REGIWIDTH         4 // #Bytes for registers in general
#define REG0RESET         0xAABBCCDD
#define REG0ADDRE         0x00000000 // byte address
#define REG0BYTES         4
#define REG1RESET         0x55667788
#define REG1ADDRE         0x00000000 // byte address
#define REG1BYTES         4*2//*3 // up to 3 registers, if the address is higher than 0, the range is needed
#define REG2BYTES         4*3
#define REG3BYTES         4*4
#define REG4BYTES         4*5
#define REGWIDTH          4 

#endif
