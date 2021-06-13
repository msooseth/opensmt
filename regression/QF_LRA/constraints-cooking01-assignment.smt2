(set-logic QF_LRA)
(set-option :produce-models true)
(set-info :source |
TLP-GP automated DTP to SMT-LIB encoding for planning
by F.Maris and P.Regnier, IRIT - Universite Paul Sabatier, Toulouse

|)
(set-info :smt-lib-version 2.0)
(set-info :category "industrial")
(declare-fun spy () Real)
(declare-fun I_0 () Real)
(declare-fun G_6 () Real)
(declare-fun EGGS () Real)
(declare-fun OIL () Real)
(declare-fun LARD () Real)
(declare-fun FIRE () Real)
(declare-fun WATER () Real)
(declare-fun NOODLES () Real)
(declare-fun COOKING () Real)
(declare-fun EATING () Real)
(assert
   (and (!(= spy (+ 1 I_0)) :named spy_n)
        (!(>= G_6 I_0) :named goal)
        (!(>= (- EGGS I_0) 0) :named eggs_after)
        (!(>= (- G_6 EGGS) 2) :named eggs_before)
        (!(>= (- OIL I_0) 0) :named oil_after)
        (!(>= (- G_6 OIL) 10) :named oil_before)
        (!(>= (- LARD I_0) 0) :named lard_after)
        (!(>= (- G_6 LARD) 13) :named lard_before)
        (!(>= (- FIRE I_0) 0) :named fire_before)
        (>= (- G_6 FIRE) 15)
        (>= (- WATER I_0) 0)
        (>= (- G_6 WATER) 10)
        (>= (- NOODLES I_0) 0)
        (>= (- G_6 NOODLES) 14)
        (>= (- COOKING I_0) 0)
        (>= (- G_6 COOKING) 1)
        (>= (- EATING I_0) 0)
        (>= (- G_6 EATING) 5)
        (<= (- EATING LARD) 8)
        (< (- EATING LARD) 8)
        (>= (- EATING LARD) 5)
        (<= (- EATING NOODLES) 17)
        (< (- EATING NOODLES) 17)
        (>= (- EATING NOODLES) 6)
        (>= (- COOKING EGGS) 2)
        (<= (- WATER FIRE) 5)
        (<= (- OIL FIRE) 5)
        (< (- OIL FIRE) 5)
        (>= (- OIL FIRE) 1)
        (>= (- LARD OIL) 2)
        (>= (- COOKING LARD) 5)
        (<= (- WATER FIRE) 5)
        (>= (- WATER FIRE) 1)
        (>= (- NOODLES WATER) 2)
        (>= (- COOKING NOODLES) 6)
        (>= (- EATING COOKING) 1)
        (>= (- G_6 EATING) 6)))
(check-sat)
(get-value (spy I_0 G_6 EGGS OIL LARD FIRE WATER NOODLES COOKING EATING))
(exit)
