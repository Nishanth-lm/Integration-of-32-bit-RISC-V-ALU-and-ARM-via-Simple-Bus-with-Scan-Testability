#include "RegisterTop_system.h"
#include "RegisterFunc.cpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

/*-----------------------------------------------------------------------------
-- Constructor
-----------------------------------------------------------------------------*/
template<class T>
RegisterTop<T>::RegisterTop(sc_module_name nm
, const unsigned int   ID                     //target ID
, const char           *registerSocket        //socket name
, unsigned int         registerSize           //register size 
, unsigned int         registerWidth          //registerwidth 
, unsigned int         baseAddress            //base address     
, unsigned int         regReset               //reset
, const sc_time        acceptDelay            //accept delay
, const sc_time        readResponseDelay      //read response delay
, const sc_time        writeResponseDelay     //write response delay
) 
//Initializations
: sc_module(nm)
, ID                 (ID)                 
, RegisterSize       (registerSize)         
, RegisterWidth      (registerWidth)        
, BaseAddress        (baseAddress)
, RegReset           (regReset)
, AcceptDelay        (acceptDelay)        
, ReadResponseDelay  (readResponseDelay)  
, WriteResponseDelay (writeResponseDelay) 
{
  //SC_HAS_PROCESS(RegisterTop);
  cout << left  << setw(30) << "ConstructorCPP - RegisterTop:    "
       << left  << setw(36) << name()
       << left  << setw(15) << " with the ID: "
       << right << setw(5)  << dec << ID
       << left  << setw(8)  << ", Size: "
       << right << setw(5)  << dec << RegisterSize
       << left  << setw(15) << " bytes, Width: "
       << right << setw(5)  << dec << RegisterWidth
       << " bytes"
       << left  << setw(16) << ", Reg. Address: "
       << right << setw(12)  << hex << BaseAddress
       << left  << setw(16) << ", Reg. Reset: "
       << right << setw(12)  << hex << RegReset
       << endl;

// Initialization: Slave BPI.
  mbpi = new SystemRegisterBPI<T>("Register-BPI",ID,
			  registerSocket,registerSize,
			  registerWidth,AcceptDelay,ReadResponseDelay,
			  WriteResponseDelay,slaveDataReadEvent_e);
			  
// Initialization: Slave function.
  mfun = new RegisterFunc<T>("Register-Func",
			       RegisterSize,
			       BaseAddress,RegReset,
			       slaveDataReadEvent_e);

// Signal binding of the sc_export's.
// Connect the write, address, and data ports of mbpi and mfun
  mbpi->write_o(mfun->write_s);
  mbpi->address_o(mfun->address_s);
  mbpi->data_o(mfun->dataIn_s);
  mfun->data_o(mbpi->dataRd_s);
  
  
// Connection of the ports.
// Connect GPIO ports of mfun to external GPIO ports
  mfun->gpio_o(gpio_o);
  mfun->gpio_i(gpio_i);
  mfun->gpio_dir_i(gpio_dir_i);
}
