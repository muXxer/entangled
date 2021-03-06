/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>
#include <unity/unity.h>

#include "common/curl-p/trit.h"
#include "common/sign/v2/iss_curl.h"
#include "common/trinary/trit_tryte.h"

#define TEST_SEED                                                              \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRST" \
  "UVWXYZ9"
#define EXPECT_SUBSEED                                                         \
  "XNW9XBGHM9ZVPSV9BXMFRB9MKODAXKEPPSTGX9PFEDNTVZPJUQGGQ9JCOZRMABQQNQBAURFKVJ" \
  "UZTYUQV"

void test_subseed(trit_t *seed, trit_t *subseed, int64_t i, Curl *curl) {
  tryte_t tryte_seed[] = TEST_SEED;
  trytes_to_trits(tryte_seed, seed, 81);

  iss_curl_subseed(seed, subseed, i, curl);

  trits_to_trytes(subseed, tryte_seed, HASH_LENGTH_TRIT);

  TEST_ASSERT_EQUAL_MEMORY(EXPECT_SUBSEED, tryte_seed, strlen(EXPECT_SUBSEED));
}
#undef EXPECT_SUBSEED
#undef TEST_SEED

#define EXP_KEY                                                                \
  "LOQBAQXKFOSONVEVXHRPCFITJUAVN9INCDMOCRGDZODZVHUT9XXIPEZJY9UOCOUOZZZWWDH9FV" \
  "GVWHGZODFXSGZCRDWJCLOUQMNLW9MIAQRZXSYEKRCUHXIQQLNLHVFUBVNLJIQAZAYB9UDYEPQT" \
  "EMTWULNXJCLZMGGJGCSVOVZDKPKTABUSI9HAL9UNWAIBVDHYUNDERBUSUYJIDGEUS9MHPHVFZT" \
  "TFHVOK9SCMGYAHYBBLAESHTOSVPUKTSFEMJFOCUMTJZIOXHYKIYPORSJMLCW9FEMTFMACBMOXE" \
  "BPXFNHOYNKMQXLRNEXGDMXOBCE9BUAYLKUICSKMWVJSRCBSDSREQ9TNTCNOPNZ9OVQLOXOANXZ" \
  "QRRZLVHKXJAFP9GF9VHVWMLMRYROWOMXPZHXJOPRRWQTLWRGAIXNYLZSPEUWTLSJLTH9BNHPOQ" \
  "JBVOOVVVKKRPWIAYXV9TEIJZBZBZDBXWMQBUJBH9KRBJ9NVXLD9XZDIKUCLHWPTKD9WJTUGDRX" \
  "IEP9ZWPGOFNEVVQKNHBSJSQBCNSPVCHNYDRRUVPJAUXXB9BFOHUUZKELUQUJCU9TCOMMLNMTSV" \
  "PDZEOPOWHNUHYOJXJLLTTOQGHAXGGOPLYABD99KNWKUFKD99QKVELUKGWWSHTFJXS9YZ9OMIEQ" \
  "GBQSEKE9OREOBA9RBLHCCVQBFAY9PVHYBKGIKPX9NQNYOEWXPFKM9S9XWTCWCCDYNAIMCUMVMH" \
  "KKX99N9BYFIGTASCNLERJNEMZEDQ9QEBRAYHAAHSDJQXLDPLEYJHEBXWPYBLKEYYIDXFAFEMSK" \
  "LNDRFFZCCTWHXJXXRVJDOBOBEERWIJKXMLXADKBAIVXUXRERTJYLDVSBLPIEYYMGAEPABHTIZV" \
  "SYPDPXANHDKLYVWHXBDKUKJGIWKBDPCUTNIXMJHYWBWQFRKQADDJOUNGUOLHFFDYDCEMVCCIAY" \
  "UUGXHATTOLEMGBV9DAONHCJSHEKOMOQCWAJBMHLYTMSEHIE9UINKMVHHSUFMSMPNEPPPGKVOHG" \
  "OUDXOVGZYKA9K9MEOZZAORX9DEYWKKLQERNYQMLEGTOL9HTTONHF9ZUKHZLA9GPEZDQDQEO9BL" \
  "VPHNGZDCJEBCMAYHKIPHQDKIFOMQDBSMNXROKPUXODVQTNLGEZYELVXL9PVHKXPPCPEFLSRSTY" \
  "EQGXOPFIOEVOGQBBWWEOUDZ9ICA9DEAGOVXHTCCHGKGGINJRENQ9FWCSBIZYUWMVFOBQBAQEJA" \
  "CQTMXPCALWEDLIAWYVGFRBLMCTSEE9JAFMCEAGSJFCT9OCZYDHLONOJ9DLJPFTVKWKIXLHGQRJ" \
  "PDPIKYREGKOTRJNDLUEQCLKPYRLLEGPPFKAGUGOPMELBAYWNBAWJJGFOXNIZXT9HTNEJRHZBAO" \
  "MKPIVAGOZPQINQFTEVXKZELTE9SDQEGCBGDDOA9JYBAAFMMVUJDIXQAJBRNSRQGDXNINBNDIAY" \
  "OAESVWBGTJZIPRZSWRFWFUDYPNOHGPKTSX9QYGLKPMRPSOHH9TOIXEEXSIMQCNTMXLWWNJEZUF" \
  "LPP9NQFAB9PIUPXZAZDFEWEVWGNLEABZPOSYSSVCEWAPHAQOUMCPHKKXCDEG9NIFBSQU9WSWBB" \
  "QZODS9VPFDHTMBQQQYFRBFAAEZIMMAEMWWAD9YSPJQNEXYTFUZPRE9SDJTK9ZYJN9MJAILPGMN" \
  "AWGNGZHCBRUFFTAXDPW9YDOVWPDPQXDUDFIEPPDQADGKBMIKRBPCSEGRXIKHQOUIEEISPDFXWY" \
  "OYYZJBSFWWHCYFRTALSSJZTJVCFNZDFNWWKONCQKQHTSKXFWZKPQLGEWPZKBTRLEBY9KWSLQFE" \
  "DMKYAOYZFCJWO9INIADGEIGYTWSYXJSJXRNRJZZQUCLROVDUZNKUAOL9NPUTNBLXIDQUMCNAQZ" \
  "PDFFLSYIDSXQTJVWXSBYQ9XUVQYELSTXFBBLJQUTCQSIRELLQNSRKVKFPZSZIZJBH9DZFCWBEB" \
  "ZMQAPJTZFDHSYEFCDLAIYVSOHHMDKNSAFQNCIRGDDOFKVJCNAGRZZFZJTNAZUVT9LWDXSWHVVZ" \
  "KQJRF9RGLUHCMMJXQSDXVDDSBLSIZAWIIYZIQJGMMXXHNJU9FZBXZTKSSGIKGTQHTBCD9MIEXD" \
  "KIDAJKVGQNYDCXWHDKT9GRVGPUVMPFMHGBYNOLJVT"

void test_key(trit_t *s, trit_t *k, size_t l, Curl *c) {
  iss_curl_key(s, k, l, c);
  tryte_t k_t[l];

  trits_to_trytes(k, k_t, l);

  TEST_ASSERT_EQUAL_MEMORY(EXP_KEY, k_t, l / 3 * sizeof(tryte_t));
}
#undef EXP_KEY

#define EXP_ADDY                                                               \
  "ORC9KGWWXUGFNVYPHCJVRGSUOLLTXU9TNAOKNMAWFWLXOUAOUG9BVKEGKGOUHPINJMIZVEYXWZ" \
  "KZFP9ZR"

void test_addy(trit_t *k, size_t l, Curl *c) {
  tryte_t addy_trytes[HASH_LENGTH_TRYTE + 1];
  addy_trytes[HASH_LENGTH_TRYTE] = 0;

  iss_curl_key_digest(k, k, l, c);
  iss_curl_address(k, k, l * 243 / 6561, c);

  trits_to_trytes(k, addy_trytes, l * 243 / 6561);

  TEST_ASSERT_EQUAL_MEMORY(EXP_ADDY, addy_trytes,
                           HASH_LENGTH_TRYTE * sizeof(tryte_t));
}

#define EX_SIG                                                                 \
  "B9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9YB9SB9YB9YB9YB9YB9YB9YB9" \
  "YB9YB9E"
void test_sig(trit_t *k, size_t l, Curl *c) {
  tryte_t addy_trytes[l];
  trit_t hash[HASH_LENGTH_TRIT];

  memset(hash, 0, sizeof(hash));
  memset(addy_trytes, 0, sizeof(hash));

  trytes_to_trits((tryte_t *)EX_SIG, hash, 81);

  TEST_ASSERT_EQUAL_INT(0, iss_curl_signature(k, hash, 0, k, l, c));
  TEST_ASSERT_EQUAL_INT(0, iss_curl_sig_digest(k, hash, 0, k, l, c));
  TEST_ASSERT_EQUAL_INT(0, iss_curl_address(k, k, HASH_LENGTH_TRIT, c));

  trits_to_trytes(k, addy_trytes, HASH_LENGTH_TRIT);

  addy_trytes[HASH_LENGTH_TRYTE] = 0;

  TEST_ASSERT_EQUAL_MEMORY(EXP_ADDY, addy_trytes,
                           HASH_LENGTH_TRYTE * sizeof(tryte_t));
}
#undef EX_SIG
#undef EXP_ADDY

void test_iss() {
  trit_t seed[HASH_LENGTH_TRIT];
  trit_t subseed[HASH_LENGTH_TRIT];
  trit_t key[ISS_KEY_LENGTH];
  int64_t index = 3;
  size_t key_length = ISS_KEY_LENGTH;

  Curl curl;
  curl.type = CURL_P_81;
  init_curl(&curl);

  test_subseed(seed, subseed, index, &curl);
  test_key(subseed, key, key_length, &curl);
  test_addy(key, key_length, &curl);

  test_key(subseed, key, key_length, &curl);
  test_sig(key, key_length, &curl);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_iss);
  // RUN_TEST(test_curl_p_81_works);
  // RUN_TEST(test_other);

  return UNITY_END();
}
