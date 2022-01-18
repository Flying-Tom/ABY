#include "common/floatutils.h"
#include "common/secureLR.h"

extern "C" {
double loss_first_computation(e_role role, double x)
{
    double input[1], output[1];
    input[0] = x;
    float_array_add(role, address, port, get_sec_lvl(secparam), 1, 64, nthreads, mt_alg, S_BOOL, input, output);
    return output[0];
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