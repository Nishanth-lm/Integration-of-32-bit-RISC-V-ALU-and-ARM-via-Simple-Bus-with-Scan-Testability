
#ifndef _scanchainFUNC_H_
#define _scanchainFUNC_H_

#include "../ProcPack.h"
#include "systemc.h"
#include "tlm.h"
#include <iomanip>

//! T: data type for "data"; 
template<class T >

class scanchainFunc : public sc_module
{
  public:
      /*!------------------------------------------------------------------------
    -- Ports
    -------------------------------------------------------------------------*/

    sc_in<bool> tdi;
    sc_in_clk clk_i;
    //! data_i: is the data in case of a read; read from the payload.
    sc_export<sc_signal_in_if<T> >  data_i;
   
    //! write_o: indicates the read/write direction; 0 for a read, 1 for a write,
    // 2 for ign.; write it to the payload. Connected to the BPI.
    sc_out<unsigned int>            write_o;
  
    //! address_o: is the memory or register address; write it to the payload.
    // Connected to the BPI.
    sc_out<unsigned int>            address_o;
    //! data_o: is the data in case of a write; write it to the payload.
    // Connected to the BPI.
    sc_out<T>                       data_o;
    /*!------------------------------------------------------------------------
    -- FIFOs/Signals
    -------------------------------------------------------------------------*/
    //! sc_export connected signals
    sc_signal<T> dataIn_s;
  
    /*!------------------------------------------------------------------------
    -- Constructor
    -------------------------------------------------------------------------*/
    //SC_CTOR(asSlaveFunc);
    scanchainFunc(sc_module_name nm, sc_event& mFuncDatRdEv);
  
    /*!------------------------------------------------------------------------
    -- Constants/Variables/Functions
    -------------------------------------------------------------------------*/
  
  private:
    /*!------------------------------------------------------------------------
    -- FIFOs/Signals
    -------------------------------------------------------------------------*/
    unsigned int IR; //! Instruction register
  
    /*!------------------------------------------------------------------------
    -- Events
    -------------------------------------------------------------------------*/
    /*! When the information from the BPI comes, that the read data is
     * available, this event will be notified and captured by the thread which
     * requests the data.*/
    sc_event readMemRdy_e;
    //! Event, that indicates that the read data is ready; read here,
    // notified in the BPI. It is a reference from the respective event
    // declared in the ARM top level.
    sc_event& mFuncDatRdEv_e;
  
    /*!------------------------------------------------------------------------
    -- Methods/Threads
    -------------------------------------------------------------------------*/
    // ... for the bus actions
    void getDatThread(void); //! Declaration: Thread for getting the data.
    void scanchainSequenceThread(void); //! Declaration: This is the algorithm.
    void scanchainWr1Print(unsigned int addr, T data);
    void scanchainWrCmd(unsigned int addr, T data); 
    void scanchainWrAndPrint(unsigned int addr, T data);
    T scanchainRdCmd(unsigned int addr); 
    T scanchainRdAndPrint(unsigned int addr);
    void scanchainRd1Print(unsigned int addr, T data);
    void scanchainFuncPrint01(T data);
    
    /*!------------------------------------------------------------------------
    -- Constants/Variables/Functions
    -------------------------------------------------------------------------*/
    //static const unsigned int  m_txn_data_size = BYTESPERMEMLINE;
    // unsigned int currentAddress_v;
};
#endif