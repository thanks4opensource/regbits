// regbits: C++ templates for type-safe bit manipulation
// Copyright (C) 2019 Mark R. Rubin
//
// This file is part of regbits.
//
// The regbits program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// The regbits program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License (LICENSE.txt) along with the regbits program.  If not, see
// <https://www.gnu.org/licenses/gpl.html>


    do_test(zero_reg                    , serial2_config ,   0);
    do_test(zero_array                  , serial2_config ,   1);
    do_test(set_singl_bits_operator     , serial2_config ,   2);
    do_test(set_singl_bits_method       , serial2_config ,   3);
    do_test(clr_singl_bits_operator     , serial2_config ,   4);
    do_test(clr_singl_bits_method       , serial2_config ,   5);
    do_test(set_singl_mskd_operator     , serial2_config ,   6);
    do_test(set_singl_mskd_method       , serial2_config ,   7);
    do_test(clr_singl_mskd_operator     , serial2_config ,   8);
    do_test(clr_singl_mskd_method       , serial2_config ,   9);
    do_test(equ_singl_bits_operator     , serial2_config ,  10);
    do_test(equ_singl_bits_method       , serial2_config ,  11);
    do_test(equ_singl_mskd_operator     , serial2_config ,  12);
    do_test(equ_singl_mskd_method       , serial2_config ,  13);
    do_test(flp_singl_bits_operator     , serial2_config ,  14);
    do_test(flp_singl_bits_method       , serial2_config ,  15);
    do_test(flp_singl_mskd_operator     , serial2_config ,  16);
    do_test(flp_singl_mskd_method       , serial2_config ,  17);
    do_test(ins_singl_mskd_operator     , serial2_config ,  18);
    do_test(ins_singl_mskd_method       , serial2_config ,  19);
    do_test(set_multi_bits_operator     , serial2_config ,  20);
    do_test(set_multi_bits_method       , serial2_config ,  21);
    do_test(ins_multi_mskd_operator     , serial2_config ,  22);
    do_test(ins_multi_mskd_method       , serial2_config ,  23);
    do_test(equ_multi_bits_operator     , serial2_config ,  24);
    do_test(equ_multi_bits_method       , serial2_config ,  25);
    do_test(equ_multi_mskd_operator     , serial2_config ,  26);
    do_test(equ_multi_mskd_method       , serial2_config ,  27);
    do_test(equ_bits_mskd_operator      , serial2_config ,  28);
    do_test(equ_bits_mskd_method        , serial2_config ,  29);
    do_test(equ_mskd_bits_operator      , serial2_config ,  30);
    do_test(equ_mskd_bits_method        , serial2_config ,  31);
    do_test(equ_bits_var                , serial2_config ,  32);
    do_test(equ_mskd_var                , serial2_config ,  33);
    do_test(cmp_equ_zero                , serial2_config ,  34);
    do_test(cmp_neq_zero                , serial2_config ,  35);
    do_test(cmp_equ_bits                , serial2_config ,  36);
    do_test(cmp_neq_bits                , serial2_config ,  37);
    do_test(cmp_equ_mskd                , serial2_config ,  38);
    do_test(cmp_neq_mskd                , serial2_config ,  39);
    do_test(cmp_equ_reg                 , serial2_config ,  40);
    do_test(cmp_neq_reg                 , serial2_config ,  41);
    do_test(constexpr_bits_array        , serial2_config ,  42);
    do_test(runtime_bits_array          , gpio1_set      ,  43);
    do_test(call_bits_val_const         , serial2_config ,  44);
    do_test(call_bits_val_var           , serial2_config ,  45);
    do_test(call_bits_ref_const         , serial2_config ,  46);
    do_test(call_bits_ref_var           , serial2_config ,  47);
    do_test(call_mskd_val_const         , serial2_config ,  48);
    do_test(call_mskd_val_var           , serial2_config ,  49);
    do_test(call_mskd_ref_const         , serial2_config ,  50);
    do_test(call_mskd_ref_var           , serial2_config ,  51);
    do_test(call_periph_bits            , serial2_config ,  52);
    do_test(call_periph_bits_val        , serial2_config ,  53);
    do_test(call_reg_bits_val           , serial2_config ,  54);
    do_test(call_periph_bits_ref        , serial2_config ,  55);
    do_test(call_reg_bits_ref           , serial2_config ,  56);
    do_test(call_periph_mskd            , serial2_config ,  57);
    do_test(call_periph_mskd_val        , serial2_config ,  58);
    do_test(call_reg_mskd_val           , serial2_config ,  59);
    do_test(call_periph_mskd_ref        , serial2_config ,  60);
    do_test(call_reg_mskd_ref           , serial2_config ,  61);
    do_test(call_return_bits            , timer1_prescale,  62);
    do_test(call_return_mskd            , timer1_prescale,  63);
    do_test(call_return_reg             , timer1_prescale,  64);
    do_test(call_return_periph          , serial2_config ,  65);
    do_test(call_pos_val                , gpio1_words_3  ,  66);
    do_test(call_pos_ref                , gpio1_words_3  ,  67);
    do_test(call_range_val_port         , serial2_config ,  68);
    do_test(call_range_ref_port         , serial2_config ,  69);
    do_test(prescaler_low               , gpio1_words_3  ,  70);
    do_test(prescaler_high              , gpio1_words_3  ,  71);
    do_test(reg_mskd_lss                , serial2_config ,  72);
    do_test(reg_mskd_leq                , serial2_config ,  73);
    do_test(reg_mskd_gtr                , serial2_config ,  74);
    do_test(reg_mskd_geq                , serial2_config ,  75);
    do_test(pos_cmp_eq                  , serial2_config ,  76);
    do_test(pos_cmp_ne                  , serial2_config ,  77);
    do_test(bits_extract_eq             , serial2_config ,  78);
    do_test(bits_extract_eq             , serial2_config ,  79);
    do_test(mskd_extract_eq             , serial2_config ,  80);
    do_test(mskd_extract_ne             , serial2_config ,  81);
    do_test(mskd_extract_lss            , serial2_config ,  82);
    do_test(mskd_extract_leq            , serial2_config ,  83);
    do_test(mskd_extract_gtr            , serial2_config ,  84);
    do_test(mskd_extract_leq            , serial2_config ,  85);
    do_test(set_bits_global             , serial2_config ,  86);
    do_test(ins_mskd_global             , serial2_config ,  87);
    do_test(assign_array_global         , gpio1_words_3  ,  88);
    do_test(shifted_global              , gpio1_words_3  ,  89);
    do_test(assign_register_global      , serial2_config ,  90);
    do_test(call_pos_val_global         , gpio1_words_3  ,  91);
    do_test(call_pos_ref_global         , gpio1_words_3  ,  92);
    do_test(call_bits_val_global        , serial2_config ,  93);
    do_test(call_bits_ref_global        , serial2_config ,  94);
    do_test(call_mskd_val_global        , serial2_config ,  95);
    do_test(call_mskd_ref_global        , serial2_config ,  96);
    do_test(call_shifted_const_val      , gpio1_words_3  ,  97);
    do_test(call_shifted_var_val        , gpio1_words_3  ,  98);
    do_test(call_shifted_global_val     , gpio1_words_3  ,  99);
    do_test(call_shifted_const_ref      , gpio1_words_3  , 100);
    do_test(call_shifted_var_ref        , gpio1_words_3  , 101);
    do_test(call_shifted_global_ref     , gpio1_words_3  , 102);
    do_test(copy_bits_equ               , serial2_config , 103);
    do_test(copy_bits_neq               , serial2_config , 104);
    do_test(copy_mskd_equ               , serial2_config , 105);
    do_test(copy_mskd_neq               , serial2_config , 106);
    do_test(copy_mskd_lss               , serial2_config , 107);
    do_test(copy_mskd_leq               , serial2_config , 108);
    do_test(copy_mskd_gtr               , serial2_config , 109);
    do_test(copy_mskd_geq               , serial2_config , 110);
    do_test(copy_shifted                , serial2_config , 111);
    do_test(call_copy_bits_val          , serial2_config , 112);
    do_test(call_copy_bits_ref          , serial2_config , 113);
