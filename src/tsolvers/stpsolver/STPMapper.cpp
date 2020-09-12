#include <Pterm.h>
#include "STPMapper.h"

STPMapper::STPMapper(const LALogic &l, const STPStore &s)
    : logic(l), store(s)
{}

// assigns a VertexRef to a PTRef variable
void STPMapper::setVert(PTRef var, VertexRef vert) {
    assert( var != PTRef_Undef );
    uint32_t idx = Idx(logic.getPterm(var).getId());
    if (varToVertRef.size() <= idx)
        varToVertRef.growTo(idx + 1, VertRef_Undef);

    varToVertRef[idx] = vert;
}

// adds an EdgeRef to the 'edgesOf' lists of its vertices
void STPMapper::registerEdge(EdgeRef edge) {
    auto &e = store.getEdge(edge);
    if (edgesContainingVert.size() <= std::max(e.from.x, e.to.x))
        edgesContainingVert.growTo(std::max(e.from.x, e.to.x) + 1);
    edgesContainingVert[e.from.x].push(edge);
    edgesContainingVert[e.to.x].push(edge);
}

// assigns an EdgeRef to a PTRef inequality
void STPMapper::mapEdge(PTRef leq, EdgeRef edge) {
    uint32_t idx = Idx(logic.getPterm(leq).getId());
    if (leqToEdgeRef.size() <= idx)
        leqToEdgeRef.growTo(idx + 1, EdgeRef_Undef);
    if (edgeRefToLeq.size() <= edge.x) {
        edgeRefToLeq.growTo(edge.x + 1, PTRef_Undef);
    }
    leqToEdgeRef[idx] = edge;
    edgeRefToLeq[edge.x] = leq;
}

void STPMapper::setAssignment(EdgeRef edge, PtAsgn asgn) {
    if (edgeRefToAsgn.size() <= edge.x)
        edgeRefToAsgn.growTo(edge.x + 1, PtAsgn_Undef);
    edgeRefToAsgn[edge.x] = asgn;
}

void STPMapper::removeAssignment(EdgeRef edge) {
    assert( edgeRefToAsgn.size() > edge.x );
    edgeRefToAsgn[edge.x] = PtAsgn_Undef;
}

PtAsgn STPMapper::getAssignment(EdgeRef edge) const {
    if (edgeRefToAsgn.size() <= edge.x) return PtAsgn_Undef;
    return edgeRefToAsgn[edge.x];
}

// returns the VertexRef corresponding to a PTRef, if it exists
VertexRef STPMapper::getVertRef(PTRef var) const {
    // missing variables in inequality are replaced with 'zero' variable
    if (var == PTRef_Undef) return STPStore::zero();
    uint32_t idx = Idx(logic.getPterm(var).getId());
    return varToVertRef.size() <= idx ? VertRef_Undef : varToVertRef[idx];
}

// returns the EdgeRef corresponding to a PTRef, if it exists
EdgeRef STPMapper::getEdgeRef(PTRef leq) const {
    uint32_t idx = Idx(logic.getPterm(leq).getId());
    return leqToEdgeRef.size() <= idx ? EdgeRef_Undef : leqToEdgeRef[idx];
}

// returns a registered EdgeRef corresponding to these parameters, if it exists
EdgeRef STPMapper::getEdgeRef(VertexRef y, VertexRef x, SafeInt c) const {
    if (y == VertRef_Undef || x == VertRef_Undef) return EdgeRef_Undef;

    // scans through all edges of y to find the one matching our parameters
    // only used in 'declareAtom' to look for negations, so we don't mind the linear time as much
    auto &possible = edgesContainingVert[y.x];
    for (EdgeRef eRef : possible) {
        auto &edge = store.getEdge(eRef);
        if (edge.from == y && edge.to == x && edge.cost == c) return eRef;
    }
    return EdgeRef_Undef;
}

PTRef STPMapper::getPTRef(EdgeRef edge) const {
    return edgeRefToLeq.size() > edge.x ? edgeRefToLeq[edge.x] : PTRef_Undef;
}

void STPMapper::clear() {
    edgesContainingVert.clear();
    varToVertRef.clear();
    leqToEdgeRef.clear();
    edgeRefToLeq.clear();
    edgeRefToAsgn.clear();
}

