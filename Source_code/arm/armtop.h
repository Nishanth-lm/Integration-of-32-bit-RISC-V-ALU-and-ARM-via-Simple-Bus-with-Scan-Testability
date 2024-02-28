//! \brief The top level of the ARM (h).
/*! A simple ARM model. It contains a BPI and a functional part.
The functional part contains the algorithm, the BPI is the bus peripheral 
interface.
*/
#ifndef _ARMTOP_H_
#define _ARMTOP_H_

#include "../ProcPack.h"
#include <systemc>
#include "armfunc.h"


template<class T >

class ARMTop : public sc_module
{
  public:
    
    /*!------------------------------------------------------------------------
    -- Constructor
    -------------------------------------------------------------------------*/
    //SC_CTOR(ARMTop);
    ARMTop(sc_module_name nm, const unsigned int ID);
  
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
    ARMFunc<T>*     marm; //! The functional part of the master.
};
#endif