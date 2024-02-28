#include "armtop.h"
#include "armfunc.cpp"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

/*!----------------------------------------------------------------------------
-- Constructor
-----------------------------------------------------------------------------*/
template<class T >
ARMTop<T>::ARMTop(sc_module_name nm
, const unsigned int   ID                   // target ID
)
  : sc_module(nm)
  , ID                 (ID)               // init target ID
{
  //SC_HAS_PROCESS(asARMTop);
  cout << left << setw(30) << "ConstructorCPP - ARMTop:    "
       << left << setw(36) << name()
       << left << setw(14) << " with the ID: "
       << left << setw(5)  << dec << ID
       << endl;
       

  mbpi = new SystemMasterBPI<T>("ARM1-BPI", ID, masterDataReadEvent_e);
  //! Initialization: Masters function.
  marm = new ARMFunc<T>("ARM1-Func", masterDataReadEvent_e);

    //! Binding of the sc_export's.
  marm->write_o(mbpi->write_s);
  marm->address_o(mbpi->address_s);
  marm->data_o(mbpi->dataWr_s);
  mbpi->data_o(marm->dataIn_s);
}