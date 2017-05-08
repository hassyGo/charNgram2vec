#include "SkipGram.hpp"
#include "Utils.hpp"
#include "ActFunc.hpp"
#include <fstream>
#include <iostream>

void SkipGram::init(const int dim, const int windowSize_, const int numNegative_, const std::string& trainFile, const bool train)
{
  std::ifstream ifsTrain(trainFile.c_str());

  this->ngramVector = MatD(dim, this->voc.ngramListCount.size());
  this->scoreVector = MatD::Zero(dim, this->voc.tokenListCount.size());
  this->rndModel.uniform(this->ngramVector, 1.0/dim);

  this->windowSize = windowSize_;
  this->numNegative = numNegative_;

  if (!train){
    return;
  }

  for (std::string line; std::getline(ifsTrain, line); ){
    if (line == ""){
      continue;
    }

    this->trainData.push_back(std::vector<Vocabulary::INDEX>());
    this->parse(line, this->trainData.back());
  }
}

void SkipGram::parse(const std::string& line, std::vector<Vocabulary::INDEX>& sentence){
  std::vector<std::string> tokens;

  sentence.clear();
  Utils::split(line, tokens);

  for (auto it = tokens.begin(); it != tokens.end(); ++it){
    auto it2 = this->voc.tokenIndex.find(*it);

    if (it2 != this->voc.tokenIndex.end()){
      sentence.push_back(it2->second);
    }
    else {
      sentence.push_back(this->voc.unkIndex);
    }
  }
}

void SkipGram::train(const Real learningRate){
  static const int glan = 100;
  static const int prog = this->trainData.size()/glan;
  int count = 0;
  Real lr = learningRate;
  const Real step = lr/this->trainData.size();

  this->rndData.shuffle(this->trainData);

  for (int i = 0; i < (int)this->trainData.size(); ++i){
    this->train(this->trainData[i], lr);
    lr -= step;

    if ((i+1)%prog == 0 && count < glan){
      std::cout << "\r";
      std::cout << "Training the model... " << ++count << "\%" << std::flush;
    }
  }

  std::cout << std::endl;
}

void SkipGram::train(const std::vector<Vocabulary::INDEX>& sentence, const Real learningRate){
  for (int i = 0; i < (int)sentence.size(); ++i){
    const int window = (this->rndData.next() >> 16)%this->windowSize+1;

    //omit the UNK token and employ the sub-sampling technique
    if (sentence[i] == this->voc.unkIndex ||
	this->voc.discardProb[sentence[i]] > this->rndData.zero2one()){
      continue;
    }

    //left side
    for (int j = i-1, count = 0; j >= 0 && count < window; --j){
      //omit the UNK token
      if (sentence[j] == this->voc.unkIndex){
	++count;
	continue;
      }

      ++count;
      this->train(sentence[i], sentence[j], learningRate);
    }

    //right side
    for (int j = i+1, count = 0; j < (int)sentence.size() && count < window; ++j){
      //omit the UNK token
      if (sentence[j] == this->voc.unkIndex){
	++count;
	continue;
      }

      ++count;
      this->train(sentence[i], sentence[j], learningRate);
    }
  }
}

void SkipGram::train(const Vocabulary::INDEX target, const Vocabulary::INDEX context, const Real learningRate){
  static std::unordered_set<Vocabulary::INDEX> ngram;

  this->voc.extractCharNgram(this->voc.tokenListCount[target].first, ngram);
  this->trainWord(ngram, context, learningRate);
}

void SkipGram::trainWord(const std::unordered_set<Vocabulary::INDEX>& ngram, const Vocabulary::INDEX context, const Real learningRate){
  Real deltaPos, deltaNeg;
  Vocabulary::INDEX neg;
  std::unordered_set<Vocabulary::INDEX> negHist;
  static VecD grad(this->ngramVector.rows());
  static VecD target(this->ngramVector.rows());

  target.setZero();
  for (auto it = ngram.begin(); it != ngram.end(); ++it){
    target += this->ngramVector.col(*it);
  }
  target.array() /= ngram.size();

  deltaPos = ActFunc::logistic(target.dot(this->scoreVector.col(context)))-1.0;
  grad = deltaPos*this->scoreVector.col(context);
  this->scoreVector.col(context) -= (learningRate*deltaPos)*target;

  for (int i = 0; i < this->numNegative; ++i){
    do {
      neg = this->voc.noiseDistribution[(this->rndData.next() >> 16)%this->voc.noiseDistribution.size()];
    } while (neg == context || negHist.find(neg) != negHist.end());

    negHist.insert(neg);
    deltaNeg = ActFunc::logistic(target.dot(this->scoreVector.col(neg)));
    grad += deltaNeg*this->scoreVector.col(neg);
    this->scoreVector.col(neg) -= (learningRate*deltaNeg)*target;
  }

  grad.array() /= ngram.size();
  grad.array() *= learningRate;
  for (auto it = ngram.begin(); it != ngram.end(); ++it){
    this->ngramVector.col(*it) -= grad;
  }
}

void SkipGram::save(const std::string& fileName){
  std::ofstream ofs((fileName+".model.bin").c_str(), std::ios::out|std::ios::binary);

  assert(ofs);

  Utils::save(ofs, this->ngramVector);
  Utils::save(ofs, this->scoreVector);
  ofs.close();

  ofs.open((fileName+".charNgram.txt").c_str());
  for (unsigned int i = 0; i < this->ngramVector.cols(); ++i){
    ofs << this->voc.ngramListCount[i].first;
    for (unsigned int j = 0; j < this->ngramVector.rows(); ++j){
      ofs << " " << this->ngramVector.coeff(j, i);
    }
    ofs << std::endl;
  }
}

void SkipGram::load(const std::string& fileName){
  std::ifstream ifs(fileName.c_str(), std::ios::in|std::ios::binary);

  assert(ifs);

  Utils::load(ifs, this->ngramVector);
  Utils::load(ifs, this->scoreVector);
}
