(set-logic QF_LIA)
(set-info :status sat)
(declare-fun a () Int)
(declare-fun b () Int)
(declare-fun c () Int)
(assert (distinct a b c))
(check-sat)
(get-model)
(exit)
