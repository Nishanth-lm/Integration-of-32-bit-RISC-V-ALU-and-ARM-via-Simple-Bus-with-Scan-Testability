
#ifndef _scanchainTOP_H_
#define _scanchainTOP_H_

#include "../ProcPack.h"
#include <systemc>
#include "scanchainfunc.h"
#include "stim.h"

template<class T >

class scanchainTop : public sc_module
{
  public:
    sc_signal<bool> tdi;
    sc_clock clk_i;
    /*!------------------------------------------------------------------------
    -- Constructor
    -------------------------------------------------------------------------*/
    //SC_CTOR(ARMTop);
    scanchainTop(sc_module_name nm, const unsigned int ID);
  
    /*!------------------------------------------------------------------------
    -- FIFOs/Signals
    -------------------------------------------------------------------------*/
    /*!------------------------------------------------------------------------
    -- Hierarchy: Public in case of needed traces.
    -------------------------------------------------------------------------*/
    //! Declaration: Master BPI.
    SystemMasterBPI<T>*      mbpi; //! The BPI of the master.
  
  private:
    /*!------------------------------------------------------------------------
    -- FIFOs/Signals
    -------------------------------------------------------------------------*/
    /*!------------------------------------------------------------------------
    -- Events
    -------------------------------------------------------------------------*/
    //! Declaration: The event connects the functional part with the BPI.
    // It acts as the original, all others down the hirarchy are references.
    sc_event masterDataReadEvent_e;
  
    /*!------------------------------------------------------------------------
    -- Constants/Variables/Functions
    -------------------------------------------------------------------------*/
    const unsigned int ID;                   //! Target ID
  
    /*!------------------------------------------------------------------------
    -- Hierarchy: Private, if no traces needed.
    -------------------------------------------------------------------------*/
    //! Declaration: Masters function.
    scanchainFunc<T>*     mscanchain;
    Stim*     mstim; //! The functional part of the master.
};
#endif