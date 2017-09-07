#pragma once
#include <boost/timer/timer.hpp>
#include "gpu/mblas/matrix_functions.h"
#include "gpu/mblas/matrix_wrapper.h"
#include "gpu/mblas/handles.h"
#include "gpu/dl4mt/cell.h"
#include "cellstate.h"
#include "gpu/dl4mt/lstm.h"
#include "gpu/dl4mt/model.h"

namespace amunmt {
namespace GPU {

template <template<class> class CellType, class InnerWeights>
class Multiplicative: public Cell {
  public:
 Multiplicative(const Weights::MultWeights<InnerWeights>& model)
      : innerCell_(model), w_(model)
    {}
    virtual void GetNextState(CellState& NextState,
                              const CellState& State,
                              const mblas::Matrix& Context) const {
      using namespace mblas;
      // TODO: change this to using some private fields (not modifying State directly)
      // Also the weight matrix naming is probably inconsistent
      Prod(*State.output, *State.output, *w_.Umh_);
      BroadcastVec(_1 + _2, *State.output, *w_.bUmh_);
      Prod(x_mult_, Context, *w_.Wmx_);
      Element(_1 + _2, x_mult_, *w_.bWmx_);
      Element(_1 * _2, *State.output, x_mult_);
      innerCell_.GetNextState(NextState, State, Context);
    }
    virtual CellLength GetStateLength() const {
      return innerCell_.GetStateLength();
    }
  private:
    CellType<InnerWeights> innerCell_;
    const Weights::MultWeights<InnerWeights>& w_;
    mutable mblas::Matrix x_mult_;
};
}
}
