#include "common/floatutils.h"
#include "common/secureLR.h"

extern "C" {
double loss_first_computation(e_role role, uint32_t nvals, double input[])
{
    return float_inner_product(role, address, port, get_sec_lvl(secparam), nvals, 64, nthreads, mt_alg, S_BOOL, input);
}

void loss_xtheta_sum_computation(e_role role, uint32_t nvals, double x_theta[], double x_theta_sum[])
{
    float_array_add(role, address, port, get_sec_lvl(secparam), nvals, 64, nthreads, mt_alg, S_BOOL, x_theta, x_theta_sum);
}

double loss_mu_computation(e_role role, uint32_t nvals, double input[])
{
    return float_inner_product(role, address, port, get_sec_lvl(secparam), nvals, 64, nthreads, mt_alg, S_BOOL, input);
}
}