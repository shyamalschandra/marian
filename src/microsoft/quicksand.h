#pragma once
#include <memory>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace marian {

template <typename T>
using Ptr = std::shared_ptr<T>;

class Options;

namespace quicksand {

typedef size_t Word;
typedef std::vector<Word> Words;
typedef std::vector<Words> QSBatch;

typedef std::tuple<Words, float> QSSentenceWithProb;
typedef std::vector<QSSentenceWithProb> QSNBest;
typedef std::vector<QSNBest> QSNBestBatch;

Ptr<Options> newOptions();

template <class T>
void set(Ptr<Options> options, const std::string& key, const T& value);

class IBeamSearchDecoder {
protected:
  Ptr<Options> options_;
  std::vector<const void*> ptrs_;
  Word eos_;

public:
  IBeamSearchDecoder(Ptr<Options> options,
                     const std::vector<const void*>& ptrs,
                     Word eos)
      : options_(options), ptrs_(ptrs), eos_(eos) {}

  virtual QSNBestBatch decode(const QSBatch& qsBatch,
                              size_t maxLength,
                              const std::unordered_set<size_t>& shortlist)
      = 0;
};

Ptr<IBeamSearchDecoder> newDecoder(Ptr<Options> options,
                                   const std::vector<const void*>& ptrs,
                                   Word eos);

}  // namespace quicksand
}  // namespace marian
