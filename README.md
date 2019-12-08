Hydra
![Logo](http://forth-standard.org/images/forth.png)
======
Forth virtual machine.

## Run
1. Clone the repo.
2. Run the command,
```
make clean && make
```
3. Type your program into the p.forth file.
4. Run the command,
```
make run
```

## Usage
Hydra takes in a file and runs the Forth program contained in it.

## Namespaces
* Core
    * Define new words (:)
    * Mathematical Operations (*) (/) (+) (-) (1+) (1-) (MIN) (MAX)
    * Output (.”)
    * Data Space (!) (@)


## Contributors
* [Dan Rauch](https://github.com/danjrauch)

## License 
* MIT

## Version 
* Version 0.0.1

## Examples

```
4 9 * 4 + 8 - 8 / 4 / ." done now"
```

```
: mult 2 3 * ; : add 1 2 + ; add mult
```

```
-4 10 ! 1 2 +
```

```
5 0 ! 0 @

3 1 ! 1 @
```