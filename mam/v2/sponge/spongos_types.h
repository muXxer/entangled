/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * MAM is based on an original implementation & specification by apmi.bsu.by
 * [ITSec Lab]
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __MAM_V2_SPONGE_SPONGOS_TYPES_H__
#define __MAM_V2_SPONGE_SPONGOS_TYPES_H__

#include "mam/v2/defs.h"
#include "mam/v2/sponge/sponge.h"
#include "mam/v2/trits/trits.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mam_spongos_s {
  mam_sponge_t sponge;
  size_t pos;
} mam_spongos_t;

size_t mam_spongos_serialized_size(mam_spongos_t const *const spongos);

void mam_spongos_serialize(mam_spongos_t const *const spongos, trits_t trits);

retcode_t mam_spongos_deserialize(trits_t *const trits,
                                  mam_spongos_t *const spongos);

#ifdef __cplusplus
}
#endif

#endif  // __MAM_V2_SPONGE_SPONGOS_TYPES_H__
