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


    do_test(zero_reg                    , serial2_config , testnum++);
    do_test(zero_array                  , serial2_config , testnum++);
    do_test(set_singl_bits_operator     , serial2_config , testnum++);
    do_test(set_singl_bits_method       , serial2_config , testnum++);
    do_test(clr_singl_bits_operator     , serial2_config , testnum++);
    do_test(clr_singl_bits_method       , serial2_config , testnum++);
    do_test(set_singl_mskd_operator     , serial2_config , testnum++);
    do_test(set_singl_mskd_method       , serial2_config , testnum++);
    do_test(clr_singl_mskd_operator     , serial2_config , testnum++);
    do_test(clr_singl_mskd_method       , serial2_config , testnum++);
    do_test(equ_singl_bits_operator     , serial2_config , testnum++);
    do_test(equ_singl_bits_method       , serial2_config , testnum++);
    do_test(equ_singl_mskd_operator     , serial2_config , testnum++);
    do_test(equ_singl_mskd_method       , serial2_config , testnum++);
    do_test(flp_singl_bits_operator     , serial2_config , testnum++);
    do_test(flp_singl_bits_method       , serial2_config , testnum++);
    do_test(flp_singl_mskd_operator     , serial2_config , testnum++);
    do_test(flp_singl_mskd_method       , serial2_config , testnum++);
    do_test(ins_singl_mskd_operator     , serial2_config , testnum++);
    do_test(ins_singl_mskd_method       , serial2_config , testnum++);
    do_test(set_multi_bits_operator     , serial2_config , testnum++);
    do_test(set_multi_bits_method       , serial2_config , testnum++);
    do_test(ins_multi_mskd_operator     , serial2_config , testnum++);
    do_test(ins_multi_mskd_method       , serial2_config , testnum++);
    do_test(equ_multi_bits_operator     , serial2_config , testnum++);
    do_test(equ_multi_bits_method       , serial2_config , testnum++);
    do_test(equ_multi_mskd_operator     , serial2_config , testnum++);
    do_test(equ_multi_mskd_method       , serial2_config , testnum++);
    do_test(equ_bits_mskd_operator      , serial2_config , testnum++);
    do_test(equ_bits_mskd_method        , serial2_config , testnum++);
    do_test(equ_mskd_bits_operator      , serial2_config , testnum++);
    do_test(equ_mskd_bits_method        , serial2_config , testnum++);
    do_test(equ_bits_var                , serial2_config , testnum++);
    do_test(equ_mskd_var                , serial2_config , testnum++);
    do_test(cmp_equ_zero                , serial2_config , testnum++);
    do_test(cmp_neq_zero                , serial2_config , testnum++);
    do_test(cmp_equ_bits                , serial2_config , testnum++);
    do_test(cmp_neq_bits                , timer1_prescale, testnum++);
    do_test(cmp_equ_multi_bits          , timer1_prescale, testnum++);
    do_test(cmp_neq_multi_bits          , timer1_prescale, testnum++);
    do_test(cmp_equ_mskd                , serial2_config , testnum++);
    do_test(cmp_neq_mskd                , serial2_config , testnum++);
    do_test(cmp_equ_reg                 , serial2_config , testnum++);
    do_test(cmp_neq_reg                 , serial2_config , testnum++);
    do_test(constexpr_bits_array        , serial2_config , testnum++);
    do_test(runtime_bits_array          , gpio1_words_3  , testnum++);
    do_test(call_bits_val_const         , serial2_config , testnum++);
    do_test(call_bits_val_var           , serial2_config , testnum++);
    do_test(call_bits_val_zero          , serial2_config , testnum++);
    do_test(call_bits_ref_const         , serial2_config , testnum++);
    do_test(call_bits_ref_var           , serial2_config , testnum++);
    do_test(call_bits_ref_zero          , serial2_config , testnum++);
    do_test(call_mskd_val_const         , serial2_config , testnum++);
    do_test(call_mskd_val_var           , serial2_config , testnum++);
    do_test(call_mskd_ref_const         , serial2_config , testnum++);
    do_test(call_mskd_ref_var           , serial2_config , testnum++);
    do_test(call_periph_bits            , serial2_config , testnum++);
    do_test(call_periph_bits_val        , serial2_config , testnum++);
    do_test(call_reg_bits_val           , serial2_config , testnum++);
    do_test(call_periph_bits_ref        , serial2_config , testnum++);
    do_test(call_reg_bits_ref           , serial2_config , testnum++);
    do_test(call_periph_mskd            , serial2_config , testnum++);
    do_test(call_periph_mskd_val        , serial2_config , testnum++);
    do_test(call_reg_mskd_val           , serial2_config , testnum++);
    do_test(call_periph_mskd_ref        , serial2_config , testnum++);
    do_test(call_reg_mskd_ref           , serial2_config , testnum++);
    do_test(call_return_bits            , timer1_prescale, testnum++);
    do_test(call_return_mskd            , timer1_prescale, testnum++);
    do_test(call_return_reg             , timer1_prescale, testnum++);
    do_test(call_return_periph          , serial2_config , testnum++);
    do_test(call_pos_val                , gpio1_words_3  , testnum++);
    do_test(call_pos_ref                , gpio1_words_3  , testnum++);
    do_test(call_range_val_port         , serial2_config , testnum++);
    do_test(call_range_ref_port         , serial2_config , testnum++);
    do_test(prescaler_low               , gpio1_words_3  , testnum++);
    do_test(prescaler_high              , gpio1_words_3  , testnum++);
    do_test(reg_mskd_lss                , serial2_config , testnum++);
    do_test(reg_mskd_leq                , serial2_config , testnum++);
    do_test(reg_mskd_gtr                , serial2_config , testnum++);
    do_test(reg_mskd_geq                , serial2_config , testnum++);
    do_test(pos_cmp_eq                  , serial2_config , testnum++);
    do_test(pos_cmp_ne                  , serial2_config , testnum++);
    do_test(bits_extract_eq             , serial2_config , testnum++);
    do_test(bits_extract_eq             , serial2_config , testnum++);
    do_test(mskd_extract_eq             , serial2_config , testnum++);
    do_test(mskd_extract_ne             , serial2_config , testnum++);
    do_test(mskd_extract_lss            , serial2_config , testnum++);
    do_test(mskd_extract_leq            , serial2_config , testnum++);
    do_test(mskd_extract_gtr            , serial2_config , testnum++);
    do_test(mskd_extract_leq            , serial2_config , testnum++);
    do_test(set_bits_global             , serial2_config , testnum++);
    do_test(ins_mskd_global             , serial2_config , testnum++);
    do_test(assign_array_global         , gpio1_words_3  , testnum++);
    do_test(shifted_global              , gpio1_words_3  , testnum++);
    do_test(assign_register_global      , serial2_config , testnum++);
    do_test(call_pos_val_global         , gpio1_words_3  , testnum++);
    do_test(call_pos_ref_global         , gpio1_words_3  , testnum++);
    do_test(call_bits_val_global        , serial2_config , testnum++);
    do_test(call_bits_ref_global        , serial2_config , testnum++);
    do_test(call_mskd_val_global        , serial2_config , testnum++);
    do_test(call_mskd_ref_global        , serial2_config , testnum++);
    do_test(call_shifted_const_val      , gpio1_words_3  , testnum++);
    do_test(call_shifted_var_val        , gpio1_words_3  , testnum++);
    do_test(call_shifted_global_val     , gpio1_words_3  , testnum++);
    do_test(call_shifted_const_ref      , gpio1_words_3  , testnum++);
    do_test(call_shifted_var_ref        , gpio1_words_3  , testnum++);
    do_test(call_shifted_global_ref     , gpio1_words_3  , testnum++);
    do_test(copy_bits_equ               , serial2_config , testnum++);
    do_test(copy_bits_neq               , serial2_config , testnum++);
    do_test(copy_mskd_equ               , serial2_config , testnum++);
    do_test(copy_mskd_neq               , serial2_config , testnum++);
    do_test(copy_mskd_lss               , serial2_config , testnum++);
    do_test(copy_mskd_leq               , serial2_config , testnum++);
    do_test(copy_mskd_gtr               , serial2_config , testnum++);
    do_test(copy_mskd_geq               , serial2_config , testnum++);
    do_test(copy_shifted                , serial2_config , testnum++);
    do_test(call_copy_bits_val          , serial2_config , testnum++);
    do_test(call_copy_bits_ref          , serial2_config , testnum++);
