#ifndef FLOATUTILS_H
#define FLOATUTILS_H
#include "../../../abycore/aby/abyparty.h"
#include "../../../abycore/circuit/arithmeticcircuits.h"
#include "../../../abycore/circuit/booleancircuits.h"
#include "../../../abycore/circuit/circuit.h"
#include "../../../abycore/sharing/sharing.h"
#include <iostream>

inline static e_mt_gen_alg mt_alg = MT_OT;

inline double float_inner_product(e_role role, const std::string& address, uint16_t port, seclvl seclvl,
    uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
    e_sharing sharing, double input[])
{

    uint64_t avals[nvals + 1];
    uint64_t bvals[nvals + 1];

    avals[0] = bvals[0] = 0;

    for (int i = 0; i < nvals; i++) {
        avals[i + 1] = *(uint64_t*)&input[i];
        bvals[i + 1] = *(uint64_t*)&input[i];
    }

    uint32_t out_bitlen_mul, out_nvals;
    uint64_t* out_vals_mul;

    while (true) {
        ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg, 65536, "ABYLR/ABY/bin/circ/");

        std::vector<Sharing*>& sharings = party->GetSharings();

        BooleanCircuit* circ = (BooleanCircuit*)sharings[sharing]->GetCircuitBuildRoutine();
        share* ain = circ->PutSIMDINGate(nvals + 1, avals, bitlen, SERVER);
        share* bin = circ->PutSIMDINGate(nvals + 1, bvals, bitlen, CLIENT);

        share* product = circ->PutFPGate(ain, bin, MUL, bitlen, nvals + 1, no_status);

        share* mul_out = circ->PutOUTGate(product, ALL);
        party->ExecCircuit();
        mul_out->get_clear_value_vec(&out_vals_mul, &out_bitlen_mul, &out_nvals);

        if (out_vals_mul[0] == 0) {
            double result = 0;
            for (int i = 0; i < nvals; i++) {
                result += *((double*)&out_vals_mul[i + 1]);
            }
            delete party;
            return result;
        } else {
            std::cerr << "recompute " << std::endl;
            delete party;
        }
    }
    return 0;
}

inline void float_array_add(e_role role, const std::string& address, uint16_t port, seclvl seclvl,
    uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
    e_sharing sharing, double input[], double output[])
{

    uint64_t avals[nvals + 1];
    uint64_t bvals[nvals + 1];

    avals[0] = bvals[0] = 0;

    for (int i = 0; i < nvals; i++) {
        avals[i + 1] = *(uint64_t*)&input[i];
        bvals[i + 1] = *(uint64_t*)&input[i];
    }

    uint32_t out_bitlen_add, out_nvals;
    uint64_t* out_vals_add;

    while (true) {
        ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg, 65536, "ABYLR/ABY/bin/circ/");

        std::vector<Sharing*>& sharings = party->GetSharings();

        BooleanCircuit* circ = (BooleanCircuit*)sharings[sharing]->GetCircuitBuildRoutine();

        share* ain = circ->PutSIMDINGate(nvals + 1, avals, bitlen, SERVER);
        share* bin = circ->PutSIMDINGate(nvals + 1, bvals, bitlen, CLIENT);
        share* sum = circ->PutFPGate(ain, bin, ADD, bitlen, nvals + 1, no_status);
        share* add_out = circ->PutOUTGate(sum, ALL);

        party->ExecCircuit();

        add_out->get_clear_value_vec(&out_vals_add, &out_bitlen_add, &out_nvals);
        if (out_vals_add[0] == 0) {
            for (int i = 0; i < nvals; i++) {
                output[i] = *((double*)&out_vals_add[i + 1]);
            }
            delete party;
            break;
        } else {
            std::cerr << "recompute " << std::endl;
            delete party;
        }
    }
}

#endif