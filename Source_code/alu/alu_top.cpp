#include "alu_top.h"
#include "alu.cpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

/*!----------------------------------------------------------------------------
-- Constructor
-----------------------------------------------------------------------------*/
template <class T >
ALUtop<T>::ALUtop(sc_module_name nm
, const unsigned int   ID                   // target ID
)
  : sc_module(nm)
  , ID                 (ID)               // init target ID
{
   cout << left << setw(30) << "ConstructorCPP - ALU_top:         "
       << left << setw(36) << name()
       << left << setw(14) << " with the ID: "
       << left << setw(5)  << dec << ID
       << endl;

    // Connect ports
  malu = new ALU<T>("ALU");

  malu->data_op1_i(data_op1_s);
  malu->data_op2_i(data_op2_s);
  malu->op_code_i(op_code_s);
  malu->result_o(result_s);
  malu->flag_o(flag_s);
   
}


