// Matthew Gwynne, 16.2.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Investigations/Cryptography/AdvancedEncryptionStandard/plans/SAT2011/KeyDiscovery/064/1_16_4/5_13.hpp
  \brief Investigations into small scale AES key discovery for 5 + 1/3 round AES with a 1x16 plaintext matrix and 4-bit field elements


  \todo Problem specification
  <ul>
   <li> In this file, we collect the investigations into translations of
   5 + 1/3 round small scale AES with one row, sixteen columns, using the 4-bit
   field size. </li>
   <li> The AES encryption scheme we model takes a 64-bit plaintext and
   64-bit key and outputs a 64-bit ciphertext. </li>
   <li> The 4-bit element (b_0,b_1,b_2,b_3) is considered as the polynomial
   b_0 * x^3 + b_1 * x^2 + b_2 * x + b_3. Addition and multiplication
   on these polynomials is defined as usual, modulo the polynomial x^4+x+1.
   </li>
   <li> The encryption scheme applies the following operations:
   <ol>
    <li> Round (iterated five times):
    <ol>
     <li> Addition of round key (n-1). </li>
     <li> Application of SubBytes (Sbox to each 4-bit element) operation. </li>
    </ol>
    </li>
    <li> Addition of round key 5 yielding the ciphertext. </li>
   </ol>
   </li>
   <li> The Sbox is non-linear permutation over the set of 4-bit elements,
   defined as inversion within the 4-bit field composed with an affine
   transformation. </li>
  </ul>


  \todo Using the canonical box translation
  <ul>
   <li> Translating the AES cipher treating Sboxes and field multiplications
   as whole boxes and translating these boxes using the canonical translation.
   </li>
   <li> Generating small scale AES for 5 + 1/3 rounds:
   \verbatim
num_rounds : 5$
num_rows : 1$
num_columns : 16$
exp : 4$
final_round_b : false$
box_tran : aes_ts_box$
seed : 1$
mc_tran : aes_mc_bidirectional$
output_ss_fcl_std(num_rounds, num_columns, num_rows, exp, final_round_b, box_tran, mc_tran)$

shell> cat ssaes_r5_c16_rw1_e4_f0.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
2872 16521 46788 0 46788 2873 1
 length count
1 20
2 12160
3 2736
4 160
9 1360
16 85
   \endverbatim
   </li>
   <li> In this translation, we have:
    <ul>
     <li> Five full rounds (Key Addition, SubBytes, and MixColumns operation).
     </li>
     <li> 85 Sboxes:
      <ul>
       <li> 80 from SubBytes = 16 byte * 5 rounds; </li>
       <li> 5 from key schedule = 1 row * 1 byte * 5 rounds. </li>
      </ul>
     </li>
     <li> 1344 additions:
      <ul>
       <li> 640 additions of arity 1:
        <ul>
         <li> 640 from MixColumns = 1 row * 16 columns * 2 directions
         (forward + inverse) * 4 bits * 5 rounds. </li>
        </ul>
       </li>
       <li> 684 additions of arity 2:
        <ul>
         <li> 320 from key additions = 64 bits * 5 round; </li>
         <li> 64 from final key addition = 64 bits; </li>
         <li> 300 from the key schedule = (64 bits - 4 bits) * 5 round. </li>
        </ul>
       </li>
       <li> 20 additions of arity 3:
        <ul>
         <li> 20 from the key schedule = 4 bits * 5 rounds. </li>
        </ul>
       </li>
      </ul>
     </li>
     <li> 20 bits for the constant in the key schedule = 4 bits * 5 rounds.
     </li>
    </ul>
   </li>
   <li> The number of clauses of each length in the translation, computed by:
   \verbatim
maxima> ncl_list_full_dualts(8,16);
[[2,128],[9,16],[16,1]]
   \endverbatim
   </li>
   <li> This instance has the following number of clauses of length:
    <ul>
     <li> 1 : 20 = key schedule constant * 1; </li>
     <li> 2 : 12160 = 80 S-boxes * 128 + 640 additions (arity 1) * 2; </li>
     <li> 3 : 2736 = 684 additions (arity 2) * 4; </li>
     <li> 4 : 160 = 20 additions (arity 3) * 8; </li>
     <li> 9 : 1360 = 85 S-boxes * 16; </li>
     <li> 16 : 85 = 85 boxes * 1. </li>
    </ul>
   </li>
   <li> Then we can generate a random assignment with the plaintext and
   ciphertext, leaving the key unknown:
   \verbatim
maxima> output_ss_random_pc_pair(seed,num_rounds,num_columns,num_rows,exp,final_round_b);
   \endverbatim
   and the merging the assignment with the translation:
   \verbatim
shell> AppendDimacs-O3-DNDEBUG ssaes_r5_c16_rw1_e4_f0.cnf ssaes_pkpair_r5_c16_rw1_e4_f0_s1.cnf > experiment_r5_k1.cnf
   \endverbatim
   </li>
   <li> minisat-2.2.0 solves it in 25.4s:
   \verbatim
shell> minisat-2.2.0 experiment_r5_k1.cnf
<snip>
restarts              : 404
conflicts             : 151945         (5982 /sec)
decisions             : 184854         (0.00 % random) (7278 /sec)
propagations          : 147381578      (5802424 /sec)
CPU time              : 25.4 s
   \endverbatim
   </li>
  </ul>


  \todo Using the rbase box translation
  <ul>
   <li> Translating the AES cipher treating Sboxes and field multiplications
   as whole boxes and translating these boxes using r_1-base translations.
   </li>
   <li> Generating small scale AES for 5 + 1/3 rounds:
   \verbatim
num_rounds : 5$
num_rows : 1$
num_columns : 16$
exp : 4$
final_round_b : false$
box_tran : aes_rbase_box$
seed : 1$
mc_tran : aes_mc_bidirectional$
output_ss_fcl_std(num_rounds, num_columns, num_rows, exp, final_round_b, box_tran, mc_tran)$

shell> cat ssaes_r5_c16_rw1_e4_f0.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
1512 6491 19588 0 19588 1513 1
 length count
1 20
2 1280
3 3756
4 1435
   \endverbatim
   </li>
   <li> In this translation, we have:
    <ul>
     <li> Five full rounds (Key Addition, SubBytes, and MixColumns operation).
     </li>
     <li> 85 S-boxes:
      <ul>
       <li> 80 from SubBytes = 16 byte * 5 rounds; </li>
       <li> 5 from key schedule = 1 row * 1 byte * 5 rounds. </li>
      </ul>
     </li>
     <li> 1344 additions:
      <ul>
       <li> 640 additions of arity 1:
        <ul>
         <li> 640 from MixColumns = 1 row * 16 columns * 2 directions
         (forward + inverse) * 4 bits * 5 rounds. </li>
        </ul>
       </li>
       <li> 684 additions of arity 2:
        <ul>
         <li> 320 from key additions = 64 bits * 5 round; </li>
         <li> 64 from final key addition = 64 bits; </li>
         <li> 300 from the key schedule = (64 bits - 4 bits) * 5 round. </li>
        </ul>
       </li>
       <li> 20 additions of arity 3:
        <ul>
         <li> 20 from the key schedule = 4 bits * 5 rounds. </li>
        </ul>
       </li>
      </ul>
     </li>
     <li> 20 bits for the constant in the key schedule = 4 bits * 5 rounds.
     </li>
    </ul>
   </li>
   <li> The number of clauses of each length in the translation, computed by:
   \verbatim
maxima> ncl_list_fcs(ev_hm(ss_sbox_rbase_cnfs,4));
[[3,12],[4,15]]
   \endverbatim
   </li>
   <li> This instance has the following number of clauses of length:
    <ul>
     <li> 1 : 20 = key schedule constant * 1; </li>
     <li> 2 : 1280 = 640 additions (arity 1) * 2; </li>
     <li> 3 : 3756 = 85 S-boxes * 12 + 684 additions (arity 2) * 4; </li>
     <li> 4 : 1435 = 85 S-boxes * 15 + 20 additions (arity 3) * 8; </li>
    </ul>
   </li>
   <li> Then we can generate a random assignment with the plaintext and
   ciphertext, leaving the key unknown:
   \verbatim
maxima> output_ss_random_pc_pair(seed,num_rounds,num_columns,num_rows,exp,final_round_b);
   \endverbatim
   and the merging the assignment with the translation:
   \verbatim
shell> AppendDimacs-O3-DNDEBUG ssaes_r5_c16_rw1_e4_f0.cnf ssaes_pkpair_r5_c16_rw1_e4_f0_s1.cnf > experiment_r5_k1.cnf
   \endverbatim
   </li>
   <li> minisat-2.2.0 solves it in 239s:
   \verbatim
shell> minisat-2.2.0 experiment_r5_k1.cnf
<snip>
restarts              : 5115
conflicts             : 2877957        (12075 /sec)
decisions             : 3273542        (0.00 % random) (13735 /sec)
propagations          : 869271128      (3647189 /sec)
CPU time              : 238.34 s
   \endverbatim
   </li>
  </ul>

*/
