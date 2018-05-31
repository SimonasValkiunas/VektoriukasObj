# VektoriukasObj

# Šalti dalykai:

    Pasirodo, kad typedef yra labai labai naudingas dalykas. Dėkui, už sutaupytą laiką.

        typedef unsigned int   size_type;
        typedef T   value_type;
        typedef T &    reference;
        typedef const T &   const_reference;
        typedef T *  pointer;
        typedef const T * const_pointer;
        typedef T * iterator;
        typedef const T *  const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

# Valdiškas Vektorius:

|Duomenų kiekis|Laikas   |
|--------------|---------|
|10000         |   0.015s| 
|100000        |   0.140s| 
|1000000       |   1.374s| 
|10000000      |   11.26s| 


# Mano Vektorius:

|Duomenų kiekis|Laikas   |
|--------------|---------|
|10000         |       0s| 
|100000        |   0.015s| 
|1000000       |   0.156s| 
|10000000      |   1.468s| 
