;; Allegrex VFPU quad-vector arithmetic and moves.
;; Copyright (C) 2026 Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify it under
;; the terms of the GNU General Public License as published by the Free
;; Software Foundation; either version 3, or (at your option) any later
;; version.
;;
;; GCC is distributed in the hope that it will be useful, but WITHOUT
;; ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;; or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
;; License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <https://www.gnu.org/licenses/>.

(define_code_iterator VFPU_BINARY [plus minus mult])
(define_code_attr vfpu_op [(plus "add") (minus "sub") (mult "mul")])
(define_code_attr vfpu_type
  [(plus "simd_fadd") (minus "simd_fadd") (mult "simd_fmul")])

;; Keep the canonical V4SF optabs shared with the existing MSA backend.
(define_expand "<vfpu_op>v4sf3"
  [(set (match_operand:V4SF 0 "register_operand")
	(VFPU_BINARY:V4SF (match_operand:V4SF 1 "register_operand")
		   (match_operand:V4SF 2 "register_operand")))]
  "ISA_HAS_MSA || mips_vfpu_math_p ()"
  "")

(define_insn "*msa_<vfpu_op>v4sf3"
  [(set (match_operand:V4SF 0 "register_operand" "=f")
	(VFPU_BINARY:V4SF (match_operand:V4SF 1 "register_operand" "f")
		   (match_operand:V4SF 2 "register_operand" "f")))]
  "ISA_HAS_MSA"
  "f<vfpu_op>.w\t%w0,%w1,%w2"
  [(set_attr "type" "<vfpu_type>")
   (set_attr "mode" "V4SF")])

;; 'C' is the existing MIPS COP2 register constraint; %P prints Cxyz.
;; The identity prefixes and arithmetic must stay out of delay slots.
(define_insn "*vfpu_<vfpu_op>v4sf3"
  [(set (match_operand:V4SF 0 "register_operand" "=C")
	(VFPU_BINARY:V4SF (match_operand:V4SF 1 "register_operand" "C")
		   (match_operand:V4SF 2 "register_operand" "C")))]
  "mips_vfpu_math_p ()"
  "vpfxs\tx,y,z,w\n\tvpfxt\tx,y,z,w\n\tvpfxd\t,,,\n\tv<vfpu_op>.q\t%P0,%P1,%P2"
  [(set_attr "type" "<vfpu_type>")
   (set_attr "mode" "V4SF")
   (set_attr "insn_count" "4")])

;; The standard move expander already exists for MSA; its V4SF instance
;; is excluded by MSA_MOVE, so this can serve both target implementations.
(define_expand "movv4sf"
  [(set (match_operand:V4SF 0)
	(match_operand:V4SF 1))]
  "ISA_HAS_MSA || TARGET_ALLEGREX_VFPU"
{
  if (mips_legitimize_move (V4SFmode, operands[0], operands[1]))
    DONE;
})

(define_expand "movmisalignv4sf"
  [(set (match_operand:V4SF 0)
	(match_operand:V4SF 1))]
  "ISA_HAS_MSA || TARGET_ALLEGREX_VFPU"
{
  if (mips_legitimize_move (V4SFmode, operands[0], operands[1]))
    DONE;
})

;; The existing MSA V4SF move recognizer is still in mips-msa.md.
;; COP2 is selected only when Allegrex VFPU is enabled.
;; A quad move or transfer to o32 GPRs can require four instructions.
(define_insn "*vfpu_movv4sf"
  [(set (match_operand:V4SF 0 "nonimmediate_operand" "=C,C,m,C,d,d,d,m")
	(match_operand:V4SF 1 "nonimmediate_operand" "C,m,C,d,C,d,m,d"))]
  "TARGET_ALLEGREX_VFPU"
  { return mips_output_vfpu_move (operands[0], operands[1]); }
  [(set (attr "type")
	(cond [(eq_attr "alternative" "1") (const_string "simd_load")
	       (eq_attr "alternative" "2") (const_string "simd_store")
	       (eq_attr "alternative" "5") (const_string "move")
	       (eq_attr "alternative" "6") (const_string "load")
	       (eq_attr "alternative" "7") (const_string "store")]
	      (const_string "simd_move")))
   (set_attr "mode" "V4SF")
   (set_attr "insn_count" "4")])

;; Ordinary o32 arguments and returns still use groups of GPRs.
(define_split
  [(set (match_operand:V4SF 0 "nonimmediate_operand")
	(match_operand:V4SF 1 "nonimmediate_operand"))]
  "TARGET_ALLEGREX_VFPU && reload_completed
   && mips_split_move_insn_p (operands[0], operands[1], insn)"
  [(const_int 0)]
{
  mips_split_move_insn (operands[0], operands[1], curr_insn);
  DONE;
})
