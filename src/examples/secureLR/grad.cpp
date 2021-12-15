#include "common.h"
#include "float_utils.h"

extern "C" {

void grad_communicate(e_role role, uint32_t nvals, double input[], double w[])
{
    float_array_add(role, address, port, get_sec_lvl(secparam), nvals, 64, nthreads, mt_alg, S_BOOL, input, w);
}
}