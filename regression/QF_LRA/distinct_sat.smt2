(set-logic QF_LRA)
(set-info :status sat)
(declare-fun a () Real)
(declare-fun b () Real)
(declare-fun c () Real)
(assert (distinct a b c))
(check-sat)
(get-model)
(exit)
