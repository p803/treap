# Treap proposal for STL
This project has been implemented as a part of Advanced Programming Libraries course at Silesian University of Technology taught by prof. Sebastian Deorowicz.

## Benchmark

Build
```
make
```

English dictionary
```
$ ./tests/main < assets/dictionary-en.txt
Treap
  insertion time: 36.6395 ms
  find time: 2.27945 ms
  count time: 1.87384 ms
Set
  insertion time: 29.0425 ms
  find time: 1.87064 ms
  count time: 1.49409 ms
Unordered set
  insertion time: 9.70872 ms
  find time: 0.793566 ms
  count time: 0.654359 ms
```

Polish dictionary
```
$ ./tests/main < assets/dictionary-pl.txt
Treap
  insertion time: 1385.5 ms
  find time: 6.75962 ms
  count time: 5.85743 ms
Set
  insertion time: 1058.07 ms
  find time: 4.46603 ms
  count time: 3.98407 ms
Unordered set
  insertion time: 281.969 ms
  find time: 0.9058 ms
  count time: 0.91692 ms
```

## Documentation
[Report [PL]](/docs/Report%20%5BPL%5D.pdf)
