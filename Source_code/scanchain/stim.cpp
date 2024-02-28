#include "stim.h"
#include "ProcPack.h"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

/*-----------------------------------------------------------------------------
-- Constructor
-----------------------------------------------------------------------------*/
Stim::Stim(sc_module_name nm)
  : sc_module(nm)
  
{
  cout << "ConstructorCPP - Stim: " << name() << endl;
  SC_THREAD(StimThread);
  sensitive << clk_i.pos();
}
void Stim::StimThread(void)
{
    //Test 
    tdi.write(1);
    wait(2100,SC_NS);
    sc_stop();
}