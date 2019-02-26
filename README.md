# Markov Chain

## Parts of the project:
### markov
* generates table of token ids
* generate table of automaton transitions
#### command line invocation
* `markov <file with urls> <context len> <prefix for dict and index files>`

### generator
* generate random sequences

#### command line invocation
* `generator <prefix for dict and index files> <context file>`

#### context file format
* context length
* number of sequences to generate
* repeated:
  * len of sequence to generate
  * [token1, token2, ...]

### File structure of the project :
* bin - binary programs files
* common_code - shared between markov and generator files
* data:
 * test data and "War and Peace" file
 * test data files:
   * hello_test_0{1,2,3}.txt - text files for a small obvious model training
 * configuration files for markov
   * ars.txt - uri for the old narod site
   * bash.txt - uri for jokes site
   * local.uri - take files from localhost provided by python server
* generator - main part of the generator program
* markov - main part of the markov program
* models - trained models of the Markov chain generator

## How to start local python server:
* python2: python -m SimpleHTTPServer
* python3: python -m http.server

## Testing sequence
* start python simple server in the root directory of the project
* compile markov and generator using `qmake && make` command
* ensure that bin dir now contains generator and markov binaries
* create model files: `bin/markov data/hello_test_00.uri 1 models/hello_test_00`
* ensure that models directory now contains hello_test_00.idx and hello_test_00.mtx files
* generate markov sequence `bin/generator models/hello_test_00 data/hello_test_00_start_context`

## Model files format:
### Tokes file format
* records number
* token id

### Table of automaton transitions format:
* context length
* number of contexts
* context_id
  * number of known for this context tokens
    * token_id frequency
