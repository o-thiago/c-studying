# GUIDELINES

> For portabity we should always specify whether a `char` is signed or unsigned when it is supposed to store numeric
> data (i.e. not an ascii char). This is because when a char is converted to an integer, the implementation of how this
> happens is machine-dependent. So, it may be converted to a negative value when a positive value was expected by the
> programmer.
