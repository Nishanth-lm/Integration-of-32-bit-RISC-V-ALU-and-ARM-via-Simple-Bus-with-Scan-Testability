#include "alu.h"
using namespace sc_core;
using namespace sc_dt;
using namespace std;
/*-----------------------------------------------------------------------------
-- Constructor
-----------------------------------------------------------------------------*/
// Constructor for the ALU module
template<class T >
ALU<T>::ALU(sc_module_name nm)
             : sc_module(nm)
             
      {
        SC_HAS_PROCESS(ALU); // because no SC_CTOR()
        cout << left << setw(30) << "ConstructorCPP - ALU:   "
             << left << setw(36) << name()
             << endl;
             SC_THREAD(getDatThread);
            // SC_THREAD(putDatThread);
      }

template<class T >
void ALU<T>::getDatThread(void)
 { 

while(true)
{
 // Variables for storing intermediate results and flags
  
wait(100,SC_NS);
//cout <<  "In ALU "<<data_op1_i;
 wait(12,SC_NS);
//cout <<  "In ALU"<<data_op2_i;
 wait(12,SC_NS);
//cout << "In ALU" <<op_code_i;
 wait(100, SC_NS);

  int operand_1 = data_op1_i.read();
  int operand_2 = data_op2_i.read();
  int  opcode    = op_code_i.read();
  sc_uint<32> result1;
  int result; 
  int flag =0;
 
cout << "----------In ALUFUNC operand_1:= "<< operand_1<<"-------------------"<<endl;
cout << "----------In ALUFUNC operand_2:= "<< operand_2<<"-------------------"<<endl;
cout << "----------In ALUFUNC opcode...:= "<< opcode<<"-------------------"<<endl;
        
    
    switch (opcode) { 
          case AND: 
        result1 =  operand_1 & operand_2; 
        result = result1.to_int(); 
        flag = DEFAULT;
        break;
        
        
        case OR:
         result1 = operand_1 | operand_2;
         result = result1.to_int(); 
         flag = DEFAULT;
         break;
         
         
        case ADD: 
        result1 =  (operand_1 + operand_2);
        result = result1.to_int(); 
        if ((operand_1 > 0 && operand_2 > 0 && result < 0) || (operand_1 < 0 && operand_2 < 0 && result > 0))
        {
        flag = flag | (1<<CARRYOVERFLOW);
        }
        if (result == 0) {
        flag = flag | (1<< ZERO);
        }
        if (result < 0) {
        flag = flag | (1<<NEGATIVE);
        }
        if ( operand_1 <  operand_2) {
        flag = flag | (1<<LESSTHAN);
        }
        break;
        
        
        case SUBTRACT: 
         result1 = operand_1 - operand_2;
         result = result1.to_int();
        if (operand_1 < result || operand_2 < result)
        {
        flag = flag | (1<<CARRYOVERFLOW);
        }
        if (result == 0) {
        flag = flag | (1<< ZERO);
        }
        if (result < 0) {
        flag = flag | (1<<NEGATIVE);
        }
        if ( operand_1 <  operand_2) {
        flag = flag | (1<<LESSTHAN);
        }
        break;
        
        
        case COMP_LESSTHAN:
        if (operand_1 < operand_2)
        {
        result = 0x01;
        }
        else result = 0x00;
        flag  =  flag | (1<< LESSTHAN);
        break;


        case NOR:
        result = -(operand_1 | operand_2); 
        if (result < 0) {
        flag = flag | (1<<NEGATIVE);
        }
         break;
         
         
        default: 
        result = 0;
        break;
    }
cout << "----------In ALUFUNC result...:= "<< result<<"-------------------"<<endl;
cout << "----------In ALUFUNC flag.....:="<< flag<<"-------------------"<<endl;


wait(20  ,SC_NS);
result_o.write(result);
wait(20,SC_NS);
flag_o.write(flag);
wait(100  ,SC_NS);

}
 
}

