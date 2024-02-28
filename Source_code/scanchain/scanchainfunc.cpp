#include "scanchainfunc.h"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

/*!----------------------------------------------------------------------------
-- Constructor
-----------------------------------------------------------------------------*/

template<class T >
scanchainFunc<T>::scanchainFunc(sc_module_name nm, sc_event& mFuncDatRdEv)
             : sc_module(nm)
             , mFuncDatRdEv_e(mFuncDatRdEv)
      {
        SC_HAS_PROCESS(scanchainFunc); 
        cout << left << setw(30) << "ConstructorCPP - scanchainFunc:   "
             << left << setw(36) << name()
             << endl;
       
       SC_THREAD(getDatThread);
       SC_THREAD(scanchainSequenceThread);
       sensitive << clk_i.pos();
       //! binds the fifo to the export
        data_i.bind(dataIn_s);
     }
     
     
/*!----------------------------------------------------------------------------
-- Methods
-----------------------------------------------------------------------------*/
//! Definition: Gets read data from MasterBPI (and so from the memory).
template<class T >
void scanchainFunc<T>::getDatThread(void)
   {
      while(true)
          {
             // wait on the information, that the read data is available
             wait(mFuncDatRdEv_e);
             // notify, that that the data is available - captured by the algorithm
             readMemRdy_e.notify(SC_ZERO_TIME);
    
             if(MASTERFUNPRINTS)
             scanchainFuncPrint01(dataIn_s.read());

         }
   }

template<class T >
  void scanchainFunc<T>::scanchainSequenceThread(void)
  {       
    
    while(true)
    {
      wait(clk_i.posedge_event());
      {
      // chose the slave ID
         unsigned int slaveID = 0x0;   
      // set the bus inactive
         write_o->write(tlm::TLM_IGNORE_COMMAND);
     
      /*-----------------------------------------------------------------------
      -- Write Section
       ----------------------------------------------------------------------*/
      cout << " " << endl;
      cout << "scanchain_Test" << endl;
      cout << "------------------------------------------------------" << endl;
      cout << "Writes to Register 1-----------................" << endl;
      cout << "------------------------------------------------------" << endl;

      
      slaveID = 0x0;   
      sc_uint<32> reg;
      sc_uint<1> tdo ;
     
for (int i =0; i < 32; i++)
      		{
                         reg= (tdi.read()<< i);
                         scanchainWrAndPrint((slaveID << 28), reg);
                         bitset <32>binaryRepresentation_s1(reg);
                         cout << "Register [" << 1 << "]: " << binaryRepresentation_s1 << endl;
                         tdo = binaryRepresentation_s1[31];
            }     
        cout << "Register [" << 1 << "]: " << " TDO_O : " << tdo << endl;

     
    cout << "Writes to Register 2-----------................" << endl;
    cout << "------------------------------------------------------" << endl;
  
   // Slave ID 1
      slaveID = 0x1;
      for (int i =0; i < 32; i++)
      		{
                         reg= (tdi.read()<< i);
                         scanchainWrAndPrint((slaveID << 28), reg);
                         bitset <32>binaryRepresentation_s1(reg);
                         cout << "Register [" << 2 << "]: " << binaryRepresentation_s1 << endl;
                         tdo = binaryRepresentation_s1[31];
            }  
             cout << "Register [" << 2 << "]: " << " TDO_O :  " << tdo << endl;


    
      cout << "... writes to Register 3------------------------------...." << endl;
      cout << "------------------------------------------------------" << endl;
      
      // Slave ID 2 
      slaveID = 0x2; 
      

       for (int i =0; i < 32; i++)
      		{
                         reg= (tdi.read()<< i);
                         scanchainWrAndPrint((slaveID << 28), reg);
                         bitset <32>binaryRepresentation_s1(reg);
                         cout << "Register [" << 3 << "]: " << binaryRepresentation_s1 << endl;
                         tdo = binaryRepresentation_s1[31];
            }  
             cout << "Register [" << 3 << "]: " << " TDO_O :  " << tdo << endl;
  
      
      // let the ARM sleep for a while
      wait(armSleep);
      wait(5,SC_NS);             
      /*-----------------------------------------------------------------------
      -- Read Section
      ----------------------------------------------------------------------*/


      cout << "------------------------------------------------------" << endl;
      cout << "... writes to Register 4  ...." << endl;
      cout << "------------------------------------------------------" << endl;

      
      slaveID = 0x3; 
         for (int i =0; i < 32; i++)
      		{
                         reg= (tdi.read()<< i);
                         scanchainWrAndPrint((slaveID << 28), reg);
                         bitset <32>binaryRepresentation_s1(reg);
                         cout << "Register [" << 4 << "]: " << binaryRepresentation_s1 << endl;
                         tdo = binaryRepresentation_s1[31];
            }  
             cout << "Register [" << 4 << "]: " << " TDO_O : " << tdo << endl;
  
      
      cout << "... writes to Register 5...------------------------------" << endl;
      cout << "------------------------------------------------------" << endl;
     
      slaveID = 0x4; // chose the slave ID, Register
      
         for (int i =0; i < 32; i++)
      		{
                         reg= (tdi.read()<< i);
                         scanchainWrAndPrint((slaveID << 28), reg);
                         bitset <32>binaryRepresentation_s1(reg);
                         cout << "Register [" << 5 << "]: " << binaryRepresentation_s1 << endl;
                         tdo = binaryRepresentation_s1[31];
            }  
             cout << "Register [" << 5 << "]: " << " TDO_O :  " << tdo << endl;
  
          
      
      wait(100, SC_NS);
      cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
      cout << "xx End of simulation! " << endl;
      cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
      sc_stop();

    }   
  } 
  
}

template<class T >
void scanchainFunc<T>::scanchainWr1Print(unsigned int addr, T data)
{
  cout << left  << setw(11)  << "scanchain "
       << left  << setw(20) << "- writes: "
       << left  << setw(3)  << " @ "
       << right << setw(9)  << sc_time_stamp()
       << left  << setw(10) << ", byteAdr."
       << right << hex << setw(9) << addr
       << left  << setw(7)  << ", data "
       << right << hex << setw(9) << data
       << endl;
}

template<class T >
void scanchainFunc<T>::scanchainWrCmd(unsigned int addr, T data)
{
  //! Writes the generated data to the BPI - to send it to the slave.
  data_o->write(data);
  //! Write the corresponding address.
  address_o->write(addr);
  //! send the WRITE command to the BPI.
  write_o->write(tlm::TLM_WRITE_COMMAND);
  //! Wait for the write delay.
  wait(rwAccess_t + rwWriteDelay_t);
  //! Remove the WRITE command.
  write_o->write(tlm::TLM_IGNORE_COMMAND);
}

template<class T >
void scanchainFunc<T>::scanchainWrAndPrint(unsigned int addr, T data)
{
  if(MAINPRINTS)
    scanchainWr1Print(addr, data);
  scanchainWrCmd(addr, data);
  wait(armOp2Op);
}

template<class T >
T scanchainFunc<T>::scanchainRdCmd(unsigned int addr)
{
  // write the address to the BPI for the data to be read
  address_o->write(addr);
  // send the READ command to the BPI
  write_o->write(tlm::TLM_READ_COMMAND);
  // wait for data from BPI - Bus - Memory
  wait(readMemRdy_e);
  // wait for the read delay
  wait(rwAccess_t + rwReadDelay_t);
  // remove the READ command
  write_o->write(tlm::TLM_IGNORE_COMMAND);
  // return the read data to the algorithm
  return dataIn_s.read();
}

template<class T >
T scanchainFunc<T>::scanchainRdAndPrint(unsigned int addr)
{
  T data;

  data = scanchainRdCmd(addr);
  if(MAINPRINTS)
    scanchainRd1Print(addr, data);
  wait(armOp2Op);
  
  return data;
}

template<class T >
void scanchainFunc<T>::scanchainRd1Print(unsigned int addr, T data)
{
  cout << left  << setw(11) << "scanchain "
       << left  << setw(20) << "- reads: "
       << left  << setw(3)  << " @ "
       << right << setw(9)  << sc_time_stamp()
       << left  << setw(10) << ", byteAdr."
       << right << hex << setw(9) << addr
       << left  << setw(7)  << ", data "
       << right << hex << setw(9) << data << " (" << dec << data << ")"
       << endl;
}



/*-----------------------------------------------------------------------------
-- Not needed things, just printouts
-----------------------------------------------------------------------------*/
template<class T >
void scanchainFunc<T>::scanchainFuncPrint01(T data)
{
  cout << left  << setw(11) << "Master-Func"
       << left  << setw(20) << "- Data read: "
       << left  << setw(3)  << " @ "
       << right << setw(9)  << sc_time_stamp()
       << left  << setw(19) << ""
       << left  << setw(7)  << ", data "
       << right << hex << setw(9) << data
       << endl;
}
