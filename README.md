# charNgram2vec
This repository provieds the re-implemented code for pre-training character n-gram embeddings presented in our Joint Many-Task (JMT) paper [1].
Compared with the original single-thread code used in the paper, in the new version, substantial speedup is achieved (Not yet! Sorry).
Some pre-trained character n-gram embeddings are also available at <a href="http://www.logos.t.u-tokyo.ac.jp/~hassy/publications/arxiv2016jmt/">my project page</a>.

This project requires a template library for linear algebra, Eigen (http://eigen.tuxfamily.org/index.php?title=Main_Page). Eigen 3.3.XX is recommended.<br>

## Usage ##
To use Eigen, please modify the line in Makefile as follows:<br>
EIGEN_LOCATION=$$HOME/local/eigen_3.3-beta1 # Modify here to use Eigen

More details will come soon!

## Reference ##
[1] <b>Kazuma Hashimoto</b>, Caiming Xiong, Yoshimasa Tsuruoka, and Richard Socher. 2016. A Joint Many-Task Model: Growing a Neural Network for Multiple NLP Tasks. <a href="https://arxiv.org/abs/1611.01587">arXiv cs.CL 1611.01587<a/>.

    @article{arXiv-2016-HASHIMOTO-jmt,
      Author =  {Hashimoto, Kazuma and Xiong, Caiming and Tsuruoka, Yoshimasa and Socher, Richard},
      Journal = {arXiv},
      Title =   {{A Joint Many-Task Model: Growing a Neural Network for Multiple NLP Tasks}},
      Volume =  {cs.CL 1611.01587},
      Year =    {2016},
      MONTH =   {November},
      URL   =   {http://arxiv.org/abs/1611.01587},
    }

## Licence ##
MIT licence
