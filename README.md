This project was designed to explore the optimization of an engineering problem.

Here the problem being explored is the simplification of boolean equations.
Specifically the minmization of min terms generated form a truth table result.
Tables with up to 6 variables are supported.

## Results:
### Initial Timing
NOTE: Performance testing conducted with `CPython` on WSL2 / Windows 10, Ryzen 5 3600 (2019)
- 3 variable:
    - `11110000`    &#8594; 0.019s
    - `11111111`    &#8594; 0.021s
    - `10101010`    &#8594; 0.020s
    - `10101110`    &#8594; 0.019s
- 4 variable:
    - `1111111111111111` &#8594; 0.021s
    - `1010111011101011` &#8594; 0.023s
    - `1111110011111000` &#8594; 0.023s
- 5 variable
    - `11111100111110001111110011111000` &#8594; 0.022s
    - `11111100111110001111110011111111` &#8594; 0.023s
    - `00001100111110001111110011111111` &#8594; 0.024s
- 6 variable
    - `0000110011111000111111001111111100001100111110001111110011111111` &#8594; 0.038s
    - `0000110011111000111111001111111100001100001100011111100111111111` &#8594; 0.071s
    - `0000110011111000111111001111111100001100001100011111100111111000` &#8594; 0.056s
