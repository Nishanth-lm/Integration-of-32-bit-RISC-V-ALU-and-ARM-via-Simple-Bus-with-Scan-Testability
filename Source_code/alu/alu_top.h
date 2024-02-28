#ifndef ALU_TOP_H
#define ALU_TOP_H

#include "systemc.h"
#include "alu.h"

template <class T >
class ALUtop : public sc_module
 {
public:
    // Constructor
    ALUtop(sc_module_name nm, const unsigned int ID);

    // Ports
    sc_in<T> data_op1_s;
    sc_in<T> data_op2_s;
    sc_in<T> op_code_s;
    sc_out<T> result_s;
    sc_out<T> flag_s;

private:
    // Component
     const unsigned int ID; 


    ALU<T>*     malu; 
};

#endif
