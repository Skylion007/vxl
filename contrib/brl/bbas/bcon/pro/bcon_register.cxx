#include "bcon_register.h"
#include "bcon_processes.h"

#include <bprb/bprb_macros.h>
#include <bprb/bprb_batch_process_manager.h>
#include <volm/volm_satellite_resources_sptr.h>


void bcon_register::register_datatype()
{
}

void bcon_register::register_process()
{
  REG_PROCESS_FUNC_CONS(bprb_func_process, bprb_batch_process_manager, bcon_calculate_trafficability_process, "bconTrafficabilityProcess");
}
