#include "common.h"

double float_inner_product(e_role role, const std::string& address, uint16_t port, seclvl seclvl,
    uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
    e_sharing sharing, double input[])
{

    // ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads,
    //     mt_alg);

    // uint32_t bitlen = 64;

    std::string circuit_dir = "/home/flyingtom/ABY/bin/circ/";

    ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg, 100000, circuit_dir);

    std::vector<Sharing*>& sharings = party->GetSharings();

    BooleanCircuit* circ = (BooleanCircuit*)sharings[sharing]->GetCircuitBuildRoutine();

    uint64_t avals[nvals];
    uint64_t bvals[nvals];

    if (role == SERVER) {
        for (int i = 0; i < nvals; i++) {
            avals[i] = *(uint64_t*)&input[i];
        }

    } else {
        for (int i = 0; i < nvals; i++) {
            bvals[i] = *(uint64_t*)&input[i];
        }
    }

    share* ain = circ->PutSIMDINGate(nvals, avals, bitlen, SERVER);
    share* bin = circ->PutSIMDINGate(nvals, bvals, bitlen, CLIENT);

    share* sum = circ->PutFPGate(ain, bin, MUL, bitlen, nvals, no_status);

    share* add_out = circ->PutOUTGate(sum, ALL);
    party->ExecCircuit();

    uint32_t out_bitlen_add, out_bitlen_cmp, out_nvals;
    uint64_t *out_vals_add, *out_vals_cmp;

    add_out->get_clear_value_vec(&out_vals_add, &out_bitlen_add, &out_nvals);

    double result = 0;
    for (int i = 0; i < nvals; i++) {
        result += *((double*)&out_vals_add[i]);
    }

    return result;
}