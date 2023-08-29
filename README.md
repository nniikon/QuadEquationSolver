# QuadEquationSolver
**A simple program in C that can solve up to quadratic equations.**
<p align='center'>
    <img src="./media/giphy.gif" alt="drawing" width="200"/>
</p>

# Installation

Use the following commands to download and compile the program.

```
git clone https://github.com/nniikon/QuadEquationSolver.git
cd .\QuadEquationSolver
make
```

Now the only thing left to do is to run KBADRATKA.exe

# Usage 

Now you can start your program!

```
.\KBADRATKA.exe
```

While coefficient input is fairly straightforward, equation input might pose more challenges.

* You can utilize the `^` symbol to represent the exponentiation operation

* You can choose whether to include the `*` multiplication symbol or not.

* You can alse write expressions on both sides of the equal sign

   and they don't necessarily need to be in the conventional order.

**Example input / output:**

```
Enter your equation: x^2 - 5x + 12 = 5x^2 + x - 5

Two real roots were found!
x1 = -2.94374
x2 = 1.44374
```
```
Please enter coefficient a: 5
Please enter coefficient b: 3.5
Please enter coefficient c: -1.5

Two real roots were found!
x1 = 0.3
x2 = -1
```
<p align='left'>
    <img src="./media/userHelp.jpg" alt="drawing" width="500"/>
</p>

# Features

* Various types of inputs can be comprehended:
```
x^2-x-1 =2*x -x + 12x^2 -5* x | correct input. Take your roots!
-x^2- 5* x^2 = 5x-12*x        | correct input. Take your roots!
x - 5 = 3                     | correct input. Take your roots!
5 = 3x - x^2                  | correct input. Take your roots!
12x=y423-                     | invalid input. Try again:
x^2 - 5x = Hello world!       | invalid input. Try again:
x = 0                         | correct input. But why?
```
