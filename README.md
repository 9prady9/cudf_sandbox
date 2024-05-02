# Requirements

- cuda toolkit (required for calling stream sync)
- cudf
- kvikio

# How to build the program

1. `mkdir build && cd build`
2. `cmake ..`
3. `make`

# How to run the program

From the project root run the following command.

```bash
./build/cudf_gds_check.run <full-path-gds-capable-file>
```

The path is mandatory, the program will not work otherwise.

Post run, you should be able to find the `cufile.log` file in the project root which should have any errors encountered
by this program while trying to write a column of 10 bytes to disk. Upon successful write, you should be able to find a
file of size 10 bytes with the name you provided as the argument at the provided location.
