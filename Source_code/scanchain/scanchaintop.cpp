#include "scanchaintop.h"
#include "scanchainfunc.cpp"
#include "stim.cpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

/*!----------------------------------------------------------------------------
-- Constructor
-----------------------------------------------------------------------------*/
template<class T >
scanchainTop<T>::scanchainTop(sc_module_name nm
, const unsigned int   ID                   // target ID
)
  : sc_module(nm)
  , ID                 (ID)               // init target ID
{
  //SC_HAS_PROCESS(asARMTop);
  cout << left << setw(30) << "ConstructorCPP - scanchainTop:    "
       << left << setw(36) << name()
       << left << setw(14) << " with the ID: "
       << left << setw(5)  << dec << ID
       << endl;
       

  mbpi = new SystemMasterBPI<T>("scanchain1-BPI", ID, masterDataReadEvent_e);
  //! Initialization: Masters function.
  mscanchain = new scanchainFunc<T>("scanchain1-Func", masterDataReadEvent_e);

  mstim = new Stim("My_Stim_Module");

    //! Binding of the sc_export's.
  mscanchain->write_o(mbpi->write_s);
  mscanchain->address_o(mbpi->address_s);
  mscanchain->data_o(mbpi->dataWr_s);
  mbpi->data_o(mscanchain->dataIn_s);

  mstim->tdi(tdi);
  mscanchain->tdi(tdi);
  mstim->clk_i(clk_i);
  mscanchain->clk_i(clk_i);
}