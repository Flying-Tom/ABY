#include "common.h"
#include "float_utils.h"

uint32_t secparam = 128, nthreads = 1;
uint16_t port = 7766;
std::string address = "127.0.0.1";

extern "C" {
double loss_first_computation(e_role role, uint32_t nvals, double input[])
{
    seclvl seclvl = get_sec_lvl(secparam);
    e_mt_gen_alg mt_alg = MT_OT;
    return float_inner_product(role, address, port, seclvl, nvals, 64, nthreads, mt_alg, S_BOOL, input);
    // return 0;
}
}