(set-logic QF_LIA)
(declare-fun |1| () Int)
(declare-fun |2| () Int)
(assert (= |1| 2))
(assert (= (as |2| Int) 1))
(assert (< 1 |1|))
(check-sat)
