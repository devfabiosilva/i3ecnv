# i3ecnv
Simple IEEE 754 float point to register converter

## Usage

```sh
IEEE 754 converter:
        Type: i3ecnv <double value>
```

### Example 1

```sh
./i3ecnv 1.2
```

```sh
Value DOUBLE = 1.200000 -> 0x3FF3333333333333

Value FLOAT = 1.200000 -> 0x3F99999A
```

### Example 2

```sh
./i3ecnv inf
```

```sh
Value DOUBLE = inf -> 0x7FF0000000000000

Value FLOAT = inf -> 0x7F800000
```

## Compiling

- Compile

```sh
gcc -O2 -o i3ecnv i3ecnv.c -Wall
```

- Remove symbols

```sh
strip i3ecnv
```

- Run application

```sh
./i3ecnv <real number>
```

## License

MIT
