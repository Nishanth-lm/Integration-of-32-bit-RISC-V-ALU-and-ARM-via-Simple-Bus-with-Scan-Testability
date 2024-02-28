#ifndef _ALU_H_
#define _ALU_H_

#include "systemc.h"


//! T: data type for "data";
template<class T >
class ALU : public sc_module
 {
 public:
    /*-------------------------------------------------------------------------
    -- Ports
    -------------------------------------------------------------------------*/
    sc_in<T> data_op1_i;
    sc_in<T> data_op2_i;
    sc_in<T> op_code_i;
    sc_out<T> result_o;
    sc_out<T> flag_o;
    /*-------------------------------------------------------------------------
    -- Constructor
    -------------------------------------------------------------------------*/
  ALU(sc_module_name nm);

private:
    /*-------------------------------------------------------------------------
    -- Methods/Threads
    -------------------------------------------------------------------------*/
void getDatThread(void);

};

#endif

