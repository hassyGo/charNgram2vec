#pragma once

#include "Matrix.hpp"
#include <string>
#include <vector>
#include <fstream>

namespace Utils{
  inline bool isSpace(const char& c){
    return (c == ' ' || c == '\t');
  }

  inline void split(const std::string& str, std::vector<std::string>& res){
    bool tok = false;
    int beg = 0;

    res.clear();

    for (int i = 0, len = str.length(); i < len; ++i){
      if (!tok && !Utils::isSpace(str[i])){
	beg = i;
	tok = true;
      }

      if (tok && (i == len-1 || Utils::isSpace(str[i]))){
	tok = false;
	res.push_back(isSpace(str[i]) ? str.substr(beg, i-beg) : str.substr(beg, i-beg+1));
      }
    }
  }

  inline void split(const std::string& str, std::vector<std::string>& res, const char sep){
    bool tok = false;
    int beg = 0;

    res.clear();

    for (int i = 0, len = str.length(); i < len; ++i){
      if (!tok && str[i] != sep){
	beg = i;
	tok = true;
      }

      if (tok && (i == len-1 || str[i] == sep)){
	tok = false;
	res.push_back((str[i] == sep) ? str.substr(beg, i-beg) : str.substr(beg, i-beg+1));
      }
    }
  }

  inline void save(std::ofstream& ofs, const MatD& params){
    Real val = 0.0;
    
    for (int i = 0; i < params.cols(); ++i){
      for (int j = 0; j < params.rows(); ++j){
	val = params.coeff(j, i);
	ofs.write((char*)&val, sizeof(Real));
      }
    }
  }
  inline void save(std::ofstream& ofs, const VecD& params){
    Real val = 0.0;
    
    for (int i = 0; i < params.rows(); ++i){
      val = params.coeff(i, 0);
      ofs.write((char*)&val, sizeof(Real));
    }
  }

  inline void load(std::ifstream& ifs, MatD& params){
    Real val = 0.0;
    
    for (int i = 0; i < params.cols(); ++i){
      for (int j = 0; j < params.rows(); ++j){
	ifs.read((char*)&val, sizeof(Real));
	params.coeffRef(j, i) = val;
      }
    }
  }
  inline void load(std::ifstream& ifs, VecD& params){
    Real val = 0.0;
    
    for (int i = 0; i < params.rows(); ++i){
      ifs.read((char*)&val, sizeof(Real));
      params.coeffRef(i, 0) = val;
    }
  }

  inline void procArg(int argc, char** argv, int& embeddingDim, int& windowSize, int& numNegative, Real& learningRate, int& wminFreq, int& cminFreq, std::string& trainFile, std::string& outputFile){
    for (int i = 1; i < argc; i+=2){
      std::string arg = (std::string)argv[i];

      if (arg == "-help"){
	printf("### Options ###\n");
	printf("-edim      the dimensionality of embeddings (default: 100)\n");
	printf("-window    the context window size (default: 1)\n");
	printf("-neg       the number of negative samples for negative sampling learning (default: 15)\n");
	printf("-lr        the initial learning rate (default: 0.025)\n");
	printf("-wminfreq  the threshold to cut rare words (default: 10)\n");
	printf("-cminfreq  the threshold to cut rare char n-grams (default: 10)\n");
	printf("-train     the file name for training (default: ./sample_data/sample.txt)\n");
	printf("-output    the file name for output files (default: ./result)\n");
	exit(1);
      }
      else if (arg == "-edim"){
	assert(i+1 < argc);
	embeddingDim = atoi(argv[i+1]);
	assert(embeddingDim > 0);
      }
      else if (arg == "-window"){
	assert(i+1 < argc);
	windowSize = atoi(argv[i+1]);
	assert(windowSize > 0);
      }
      else if (arg == "-neg"){
	assert(i+1 < argc);
	numNegative = atoi(argv[i+1]);
	assert(numNegative > 0);
      }
      else if (arg == "-lr"){
	assert(i+1 < argc);
	learningRate = atof(argv[i+1]);
	assert(learningRate > 0.0);
      }
      else if (arg == "-wminfreq"){
	assert(i+1 < argc);
	wminFreq = atoi(argv[i+1]);
	assert(wminFreq > 0);
      }
      else if (arg == "-cminfreq"){
	assert(i+1 < argc);
	cminFreq = atoi(argv[i+1]);
	assert(cminFreq > 0);
      }
      else if (arg == "-train"){
	assert(i+1 < argc);
	trainFile = (std::string)argv[i+1];
      }
      else if (arg == "-output"){
	assert(i+1 < argc);
	outputFile = (std::string)argv[i+1];
      }
    }
  }
};
